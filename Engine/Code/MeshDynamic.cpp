#include "..\Header\MeshDynamic.h"
#include "HierachyLoader.h"
#include "AnimaitionCtrl.h"

HRESULT CMeshDynamic::Initialize(const TCHAR * szFilePath, const TCHAR * szFileName)
{
	TCHAR		szFullPath[MAX_PATH] = L"";
	TCHAR		szPath[MAX_PATH] = L"";

	
	lstrcpy(szFullPath, szFilePath);
	lstrcat(szFullPath, szFileName);

	m_pLoader = CHierachyLoader::Create(m_pGraphicDev, szFilePath);
	if (m_pLoader == nullptr)
		return E_FAIL;

	LPD3DXANIMATIONCONTROLLER			pAniCtrl = nullptr;
	if (FAILED(D3DXLoadMeshHierarchyFromX(szFullPath, D3DXMESH_MANAGED, m_pGraphicDev, m_pLoader, nullptr, &m_pRootFrame, &pAniCtrl)))
		return E_FAIL;

	m_pAniCtrl = CAnimaitionCtrl::Create(pAniCtrl);
	if (m_pAniCtrl == nullptr)
		return E_FAIL;

	D3DXMatrixIdentity(&m_matPivot);

	m_matPivot.m[0][0] = -1;
	m_matPivot.m[2][2] = -1;
	
	if (FAILED(UpdateCombinedMatrix(m_pRootFrame, &m_matPivot)))
		return E_FAIL;

	if (FAILED(SetUpCombinedMatrixPointer(m_pRootFrame)))
		return E_FAIL;

	
	return NOERROR;
}

HRESULT CMeshDynamic::UpdateCombinedMatrix(D3DXFRAME * pFrame, const D3DXMATRIX * matParents)
{
	EXFRAME*		pFrameEx = (EXFRAME*)pFrame;

	pFrameEx->CombinedMatrix = pFrame->TransformationMatrix * (*matParents);

	if (pFrameEx->pFrameFirstChild != nullptr)
		UpdateCombinedMatrix(pFrameEx->pFrameFirstChild, &pFrameEx->CombinedMatrix);


	if (pFrameEx->pFrameSibling != nullptr)
		UpdateCombinedMatrix(pFrameEx->pFrameSibling, matParents);

	return NOERROR;
}

HRESULT CMeshDynamic::SetUpCombinedMatrixPointer(D3DXFRAME * pFrame)
{
	if (pFrame->pMeshContainer != nullptr)
	{
		LPEXMESHCONTAINER  pMeshContainer = (LPEXMESHCONTAINER)pFrame->pMeshContainer;

		m_MeshContainer.push_back(pMeshContainer);

		for (size_t i = 0; i < pMeshContainer->dwFrameNum; ++i)
		{
			EXFRAME*		pFrameEx = (EXFRAME*)D3DXFrameFind(m_pRootFrame, pMeshContainer->pSkinInfo->GetBoneName(i));

			pMeshContainer->ppCombinedMatrix[i] = &pFrameEx->CombinedMatrix;
		}

	}

	if (pFrame->pFrameSibling != nullptr)
		SetUpCombinedMatrixPointer(pFrame->pFrameSibling);


	if (pFrame->pFrameFirstChild != nullptr)
		SetUpCombinedMatrixPointer(pFrame->pFrameFirstChild);

	return NOERROR;
}

CMeshDynamic::CMeshDynamic(LPDIRECT3DDEVICE9 _m_pGraphicDevice)
	:CComponent(_m_pGraphicDevice)

{
}

CMeshDynamic::CMeshDynamic(const CMeshDynamic & rhs)
	:CComponent(rhs),
	m_pLoader(rhs.m_pLoader),
	m_pRootFrame(rhs.m_pRootFrame),
	m_MeshContainer(rhs.m_MeshContainer),
	m_matPivot(rhs.m_matPivot),
	m_pAniCtrl(CAnimaitionCtrl::Create(*rhs.m_pAniCtrl))
{
	m_pLoader->AddRef();
}

HRESULT CMeshDynamic::SetShaderMeshTex(LPD3DXEFFECT pEffect, int iContainerNum, const long & SubsetNum, const char * ShaderTexName, MESHTEXTURE::MESHTEXTYPE eType)
{
	pEffect->SetTexture(ShaderTexName, m_MeshContainer[iContainerNum]->pMeshTexture[SubsetNum].pTexture[eType]);

	return NOERROR;
}

HRESULT CMeshDynamic::Render(int iContainerNum, int iSubsetNum)
{
	m_MeshContainer[iContainerNum]->MeshData.pMesh->DrawSubset(iSubsetNum);

	return NOERROR;
}

HRESULT CMeshDynamic::UpdateSkinnedMesh(int iContainerNum)
{
	if (m_MeshContainer.size() <= iContainerNum)
		return E_FAIL;

	LPEXMESHCONTAINER  pMeshContainer = (LPEXMESHCONTAINER)m_MeshContainer[iContainerNum];

	for (size_t i = 0; i<pMeshContainer->dwFrameNum; ++i)
		pMeshContainer->pRenderMatrix[i] = pMeshContainer->pOffsetMatrix[i] * (*pMeshContainer->ppCombinedMatrix[i]);

	void* pSour = nullptr, *pDest = nullptr;

	pMeshContainer->pOriginalMesh->LockVertexBuffer(0, &pSour);
	pMeshContainer->MeshData.pMesh->LockVertexBuffer(0, &pDest);

	pMeshContainer->pSkinInfo->UpdateSkinnedMesh(pMeshContainer->pRenderMatrix, nullptr, pSour, pDest);

	pMeshContainer->pOriginalMesh->UnlockVertexBuffer();
	pMeshContainer->MeshData.pMesh->UnlockVertexBuffer();

	return NOERROR;
}

HRESULT CMeshDynamic::SetAnimationSet(int iIndex)
{
	if (m_pAniCtrl == nullptr)
		return E_FAIL;

	m_pAniCtrl->SetAnimation(iIndex);
	return NOERROR;
}

HRESULT CMeshDynamic::PlayAnimation(const float & fTimeDelta)
{
	if (m_pAniCtrl == nullptr)
		return E_FAIL;

	m_pAniCtrl->PlayAnimation(fTimeDelta);

	UpdateCombinedMatrix(m_pRootFrame, &m_matPivot);

	return NOERROR;
}

bool CMeshDynamic::AnimationEnd(float fOffset)
{
	if (m_pAniCtrl == nullptr)
		return false;

	return m_pAniCtrl->AnimationEnd(fOffset);
}

double CMeshDynamic::GetTimeTrack()
{
	return m_pAniCtrl->GetTimeTrack();
}

D3DXMATRIX * CMeshDynamic::GetBoneMatrix(TCHAR * szBoneName)
{
	char ctemp[MAX_PATH];
	WideCharToMultiByte(CP_ACP, 0, szBoneName, MAX_PATH, ctemp, MAX_PATH, NULL, NULL);
	UpdateCombinedMatrix(m_pRootFrame, &m_matPivot);
	EXFRAME*		pFrameEx = (EXFRAME*)D3DXFrameFind(m_pRootFrame, ctemp);
	
	return &pFrameEx->CombinedMatrix;
}

CMeshDynamic * CMeshDynamic::Create(LPDIRECT3DDEVICE9 _m_pGraphicDevice, const TCHAR * szFilePath, const TCHAR * szFileName)
{
	CMeshDynamic* pInstance = new CMeshDynamic(_m_pGraphicDevice);

	if (FAILED(pInstance->Initialize(szFilePath, szFileName)))
	{
		_MSGBOX("CMeshDynamic Created Failed");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CMeshDynamic::Clone()
{
	return new CMeshDynamic(*this);
}

void CMeshDynamic::Free()
{
	if (m_IsClone == false)
	{
		m_pLoader->DestroyFrame(m_pRootFrame);
	}

	Safe_Release(m_pLoader);
	Safe_Release(m_pAniCtrl);
	m_MeshContainer.clear();
	CComponent::Free();
}
