#include "..\Header\HierachyLoader.h"
#define _CRT_SECURE_NO_WARNINGS



_ulong CHierachyLoader::AddRef()
{
	return _ulong(++m_dwRef);
}

_ulong CHierachyLoader::Release()
{
	if (0 == m_dwRef)
	{
		Free();

		delete this;

		return 0;
	}
	else
		return m_dwRef--;
}

HRESULT CHierachyLoader::Initialize(const TCHAR * pFilePath)
{
	m_pFilePath = pFilePath;
	return NOERROR;
}

HRESULT CHierachyLoader::AllocateName(char ** szDestName, const char * szSourName)
{
	_uint iLength = strlen(szSourName);

	*szDestName = new char[iLength + 1];
	ZeroMemory(*szDestName, sizeof(char)*(iLength + 1));
	
	strcpy(*szDestName, szSourName);

	return NOERROR;
}

HRESULT CHierachyLoader::ChangeTextureFileName(TCHAR * pFilePath, TCHAR  szSourName)
{
	_uint iLength = lstrlen(pFilePath);

	for (int i = iLength; i >= 0; --i)
	{
		if (pFilePath[i] == '.')
		{
			pFilePath[i - 1] = szSourName;
			break;
		}
	}
	return NOERROR;
}

CHierachyLoader::CHierachyLoader(LPDIRECT3DDEVICE9 _m_pGraphicDevice)
	:m_pGraphicDevice(_m_pGraphicDevice)
{
	m_pGraphicDevice->AddRef();
}

STDMETHODIMP CHierachyLoader::CreateFrame(LPCSTR Name, LPD3DXFRAME * ppNewFrame)
{
	EXFRAME* pFrame = new EXFRAME;
	ZeroMemory(pFrame, sizeof(EXFRAME));

	if (Name != nullptr)
	{
		if (FAILED(AllocateName(&pFrame->Name, Name)))
			return E_FAIL;
	}

	*ppNewFrame = pFrame;

	return NOERROR;
}

STDMETHODIMP CHierachyLoader::CreateMeshContainer(LPCSTR Name, CONST D3DXMESHDATA * pMeshData, CONST D3DXMATERIAL * pMaterials, CONST D3DXEFFECTINSTANCE * pEffectInstances, DWORD NumMaterials, CONST DWORD * pAdjacency, LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER * ppNewMeshContainer)
{
	LPEXMESHCONTAINER pMeshContainer = new EXMESHCONTAINER;
	ZeroMemory(pMeshContainer, sizeof(EXMESHCONTAINER));

	if (nullptr != Name)
	{
		if (FAILED(AllocateName(&pMeshContainer->Name, Name)))
			return E_FAIL;
	}

	pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;

	LPD3DXMESH pMesh = pMeshData->pMesh;
	pMesh->AddRef();

	pMeshContainer->pAdjacency = new unsigned long[pMesh->GetNumFaces() * 3];
	memcpy(pMeshContainer->pAdjacency, pAdjacency, sizeof(unsigned long) * pMesh->GetNumFaces() * 3);

	unsigned long dwFVF = pMesh->GetFVF();

	if (dwFVF & D3DFVF_NORMAL)
	{
		if (FAILED(pMesh->CloneMeshFVF(pMesh->GetOptions(), dwFVF, m_pGraphicDevice, &pMeshContainer->MeshData.pMesh)))
			return E_FAIL;
	}
	else
	{
		if (FAILED(pMesh->CloneMeshFVF(pMesh->GetOptions(), dwFVF | D3DFVF_NORMAL, m_pGraphicDevice, &pMeshContainer->MeshData.pMesh)))
			return E_FAIL;

		if (FAILED(D3DXComputeNormals(pMeshContainer->MeshData.pMesh, pMeshContainer->pAdjacency)))
			return E_FAIL;
	}
	pMesh->Release();

	pMeshContainer->NumMaterials = (NumMaterials == 0) ? 1 : NumMaterials;
	pMeshContainer->pMaterials = new D3DXMATERIAL[pMeshContainer->NumMaterials];
	ZeroMemory(pMeshContainer->pMaterials, sizeof(D3DXMATERIAL)*pMeshContainer->NumMaterials);
	
	if (NumMaterials != 0)
	{
		memcpy(pMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL)*pMeshContainer->NumMaterials);

		pMeshContainer->pMeshTexture = new MESHTEXTURE[pMeshContainer->NumMaterials];
		ZeroMemory(pMeshContainer->pMeshTexture, sizeof(MESHTEXTURE) * pMeshContainer->NumMaterials);

		for (size_t i = 0; i < pMeshContainer->NumMaterials; ++i)
		{
			TCHAR		szFullPath[MAX_PATH] = L"";
			TCHAR		szFileName[MAX_PATH] = L"";

			lstrcpy(szFullPath, m_pFilePath);

			MultiByteToWideChar(CP_ACP, 0, pMeshContainer->pMaterials[i].pTextureFilename, strlen(pMeshContainer->pMaterials[i].pTextureFilename)
				, szFileName, MAX_PATH);

			lstrcat(szFullPath, szFileName);

			if (FAILED(D3DXCreateTextureFromFile(m_pGraphicDevice, szFullPath, &pMeshContainer->pMeshTexture[i].pTexture[MESHTEXTURE::MESH_DIFFUSE])))
				return E_FAIL;

			ChangeTextureFileName(szFullPath, 'N');
			D3DXCreateTextureFromFile(m_pGraphicDevice, szFullPath, &pMeshContainer->pMeshTexture[i].pTexture[MESHTEXTURE::MESH_NORMAL]);

			ChangeTextureFileName(szFullPath, 'S');
			D3DXCreateTextureFromFile(m_pGraphicDevice, szFullPath, &pMeshContainer->pMeshTexture[i].pTexture[MESHTEXTURE::MESH_SPECULAR]);

		}		
	}

	pMeshContainer->pSkinInfo = pSkinInfo;
	pMeshContainer->pSkinInfo->AddRef();

	pMeshContainer->dwFrameNum = pMeshContainer->pSkinInfo->GetNumBones();

	pMeshContainer->pRenderMatrix = new D3DXMATRIX[pMeshContainer->dwFrameNum];
	ZeroMemory(pMeshContainer->pRenderMatrix, sizeof(D3DXMATRIX) * pMeshContainer->dwFrameNum);

	pMeshContainer->pOffsetMatrix = new D3DXMATRIX[pMeshContainer->dwFrameNum];
	ZeroMemory(pMeshContainer->pOffsetMatrix, sizeof(D3DXMATRIX) * pMeshContainer->dwFrameNum);

	pMeshContainer->ppCombinedMatrix = new  D3DXMATRIX*[pMeshContainer->dwFrameNum];
	ZeroMemory(pMeshContainer->ppCombinedMatrix, sizeof(D3DXMATRIX*) * pMeshContainer->dwFrameNum);

	for (size_t i = 0; i < pMeshContainer->dwFrameNum; ++i)
		pMeshContainer->pOffsetMatrix[i] = *pMeshContainer->pSkinInfo->GetBoneOffsetMatrix(i);

	if (FAILED(pMeshContainer->MeshData.pMesh->CloneMeshFVF(pMeshContainer->MeshData.pMesh->GetOptions(), pMeshContainer->MeshData.pMesh->GetFVF(), m_pGraphicDevice, &pMeshContainer->pOriginalMesh)))
		return E_FAIL;

	*ppNewMeshContainer = pMeshContainer;
		 
	return NOERROR;
}

STDMETHODIMP CHierachyLoader::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	Safe_Delete_Arr(pFrameToFree->Name);

	if (pFrameToFree->pMeshContainer != nullptr)
		DestroyMeshContainer(pFrameToFree->pMeshContainer);

	if (pFrameToFree->pFrameSibling != nullptr)
		DestroyFrame(pFrameToFree->pFrameSibling);

	if (pFrameToFree->pFrameFirstChild != nullptr)
		DestroyFrame(pFrameToFree->pFrameFirstChild);

	Safe_Delete(pFrameToFree);
	
	return NOERROR;
}

STDMETHODIMP CHierachyLoader::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	LPEXMESHCONTAINER pMeshContainer = (LPEXMESHCONTAINER)pMeshContainerToFree;

	Safe_Delete_Arr(pMeshContainer->Name);

	pMeshContainer->MeshData.pMesh->Release();
	Safe_Delete_Arr(pMeshContainer->pMaterials);
	Safe_Delete_Arr(pMeshContainer->pAdjacency);
	Safe_Release(pMeshContainer->pSkinInfo); 
	Safe_Release(pMeshContainer->pOriginalMesh); 

	for (size_t i = 0; i < pMeshContainer->NumMaterials; ++i)
	{
		for (int j = 0; j < MESHTEXTURE::MESH_END; ++j)
			Safe_Release(pMeshContainer->pMeshTexture[i].pTexture[j]);
	}

	Safe_Delete_Arr(pMeshContainer->pMeshTexture);
	Safe_Delete_Arr(pMeshContainer->pOffsetMatrix);
	Safe_Delete_Arr(pMeshContainer->pRenderMatrix);
	Safe_Delete_Arr(pMeshContainer->ppCombinedMatrix);

	Safe_Delete(pMeshContainerToFree);

	return NOERROR;
}

CHierachyLoader * CHierachyLoader::Create(LPDIRECT3DDEVICE9 _m_pGraphicDevice, const TCHAR * pFilePath)
{
	CHierachyLoader* pInstance = new CHierachyLoader(_m_pGraphicDevice);

	if (FAILED(pInstance->Initialize(pFilePath)))
	{
		_MSGBOX("CHierachyLoader Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CHierachyLoader::Free()
{
	Safe_Release(m_pGraphicDevice);
}
