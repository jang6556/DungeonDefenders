#include "..\Header\MeshStatic.h"





HRESULT CMeshStatic::Initialize(TCHAR * szFilePath, TCHAR* szFileName)
{
	LPD3DXMESH pMesh = nullptr;

	TCHAR szFullPath[MAX_PATH] = L"";

	lstrcpy(szFullPath, szFilePath);
	lstrcat(szFullPath, szFileName);


	if (FAILED(D3DXLoadMeshFromX(szFullPath, D3DXMESH_MANAGED, m_pGraphicDev, &m_pAdsjacency, &m_pMaterials, nullptr, &m_iSubSetNum, &pMesh)))
		return E_FAIL;

	m_pMeshTexture = new MESHTEXTURE[m_iSubSetNum];
	ZeroMemory(m_pMeshTexture, sizeof(MESHTEXTURE)*m_iSubSetNum);

	m_pSubsetMaterial = new D3DXMATERIAL[m_iSubSetNum];
	memcpy(m_pSubsetMaterial, m_pMaterials->GetBufferPointer(), sizeof(D3DXMATERIAL)*m_iSubSetNum);

	pMesh->CloneMeshFVF(pMesh->GetOptions(), pMesh->GetFVF(), m_pGraphicDev, &m_pMesh);

	Safe_Release(pMesh);
	
	for (int i = 0; i < m_iSubSetNum; ++i)
	{
		lstrcpy(szFullPath, szFilePath);

		TCHAR szFileName[MAX_PATH] = L"";	

		MultiByteToWideChar(CP_ACP, 0, m_pSubsetMaterial[i].pTextureFilename, strlen(m_pSubsetMaterial[i].pTextureFilename)
			, szFileName, MAX_PATH);

		

		lstrcat(szFullPath, szFileName);

		if (FAILED(D3DXCreateTextureFromFile(m_pGraphicDev, szFullPath, &m_pMeshTexture[i].pTexture[MESHTEXTURE::MESH_DIFFUSE])))
			return E_FAIL;

		ChangeFileName(szFullPath, L'N');
		D3DXCreateTextureFromFile(m_pGraphicDev, szFullPath, &m_pMeshTexture[i].pTexture[MESHTEXTURE::MESH_NORMAL]);

		ChangeFileName(szFullPath, L'S');
		D3DXCreateTextureFromFile(m_pGraphicDev, szFullPath, &m_pMeshTexture[i].pTexture[MESHTEXTURE::MESH_SPECULAR]);
	}

	return NOERROR;
}

HRESULT CMeshStatic::ChangeFileName(TCHAR * szFileName, TCHAR szText)
{
	int iLength = lstrlen(szFileName);

	for (int i = iLength; i >= 0; --i)
	{
		if (szFileName[i] == L'.')
		{
			szFileName[i - 1] = szText;
		}
	}
	return NOERROR;
}

CMeshStatic::CMeshStatic(LPDIRECT3DDEVICE9 _m_pGraphicDevice)
	:CComponent(_m_pGraphicDevice)
{

}

CMeshStatic::CMeshStatic(const CMeshStatic & rhs)
	:CComponent(rhs), 
	m_pMesh(rhs.m_pMesh),
	m_pMaterials(rhs.m_pMaterials),
	m_pAdsjacency(rhs.m_pAdsjacency),
	m_iSubSetNum(rhs.m_iSubSetNum),
	m_pMeshTexture(rhs.m_pMeshTexture),
	m_pSubsetMaterial(rhs.m_pSubsetMaterial)

{
	m_pMesh->AddRef();
	m_pMaterials->AddRef();
	m_pAdsjacency->AddRef();

	for (int i = 0; i < m_iSubSetNum; ++i)
	{
		if (m_pMeshTexture[i].pTexture[MESHTEXTURE::MESH_DIFFUSE] != nullptr)
			m_pMeshTexture[i].pTexture[MESHTEXTURE::MESH_DIFFUSE]->AddRef();

		if (m_pMeshTexture[i].pTexture[MESHTEXTURE::MESH_NORMAL] != nullptr)
			m_pMeshTexture[i].pTexture[MESHTEXTURE::MESH_NORMAL]->AddRef();

		if (m_pMeshTexture[i].pTexture[MESHTEXTURE::MESH_SPECULAR] != nullptr)
			m_pMeshTexture[i].pTexture[MESHTEXTURE::MESH_SPECULAR]->AddRef();	
	}
}

HRESULT CMeshStatic::SetShaderMeshTex(LPD3DXEFFECT pEffect, const long & SubsetNum, const char * ShaderTexName, MESHTEXTURE::MESHTEXTYPE eType)
{
	if (pEffect == nullptr ||
		m_pMeshTexture == nullptr)
		return E_FAIL;

	pEffect->SetTexture(ShaderTexName, m_pMeshTexture[SubsetNum].pTexture[eType]);

	return NOERROR;
}

HRESULT CMeshStatic::Render(int iSubsetNum)
{
	if (m_pMesh == nullptr)
		return E_FAIL;

	m_pMesh->DrawSubset(iSubsetNum);
	return NOERROR;
}

CMeshStatic * CMeshStatic::Create(LPDIRECT3DDEVICE9 _m_pGraphicDevice, TCHAR * szFilePath, TCHAR* szFileName)
{
	CMeshStatic* pInstance = new CMeshStatic(_m_pGraphicDevice);

	if (FAILED(pInstance->Initialize(szFilePath, szFileName)))
	{
		_MSGBOX("CMeshStatic Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent * CMeshStatic::Clone()
{
	return new CMeshStatic(*this);
}

void CMeshStatic::Free()
{
	for (int i = 0; i < m_iSubSetNum; ++i)
	{		
		Safe_Release(m_pMeshTexture[i].pTexture[MESHTEXTURE::MESH_DIFFUSE]);		
		Safe_Release(m_pMeshTexture[i].pTexture[MESHTEXTURE::MESH_NORMAL]);		
		Safe_Release(m_pMeshTexture[i].pTexture[MESHTEXTURE::MESH_SPECULAR]);
	}

	if (m_IsClone == false)
	{
		Safe_Delete_Arr(m_pMeshTexture);
		Safe_Delete_Arr(m_pSubsetMaterial);
	}

	
	Safe_Release(m_pMaterials);
	Safe_Release(m_pAdsjacency);
	Safe_Release(m_pMesh);

	CComponent::Free();
}
