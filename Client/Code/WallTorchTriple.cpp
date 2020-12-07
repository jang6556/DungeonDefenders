#include "stdafx.h"
#include "..\Header\WallTorchTriple.h"


_USING(Client)
HRESULT CWallTorchTriple::Initialize()
{
	return NOERROR;
}

HRESULT CWallTorchTriple::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXMATRIX matWorld = *(D3DXMATRIX*)pArg;

	m_pTransform->SetWorldMatrix(matWorld);

	if (FAILED(CLightObject::SetPointLight(SCENE_MAGNUS)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CWallTorchTriple::Initialize_Prototype()
{
	if (FAILED(CLightObject::LoadLightData(L"Data/WallTorch_Triple_Light.dat")))
		return E_FAIL;
	return NOERROR;
}

HRESULT CWallTorchTriple::AddComponent()
{
	if (FAILED(CLightObject::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"WALLTORCH_TRIPLE", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	return NOERROR;
}

CWallTorchTriple::CWallTorchTriple(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CLightObject(_m_pGraphicDev)
{
}

CWallTorchTriple::CWallTorchTriple(const CWallTorchTriple & rhs)
	: CLightObject(rhs)
{
}

_int CWallTorchTriple::Progress(const _float & fTimeDelta)
{
	return CLightObject::Progress(fTimeDelta);
}

_int CWallTorchTriple::LateProgress(const _float & fTimeDelta)
{
	return CLightObject::LateProgress(fTimeDelta);
}

HRESULT CWallTorchTriple::Render()
{
	return CLightObject::Render();
}

CGameObject * CWallTorchTriple::Clone(void * pArg)
{
	CWallTorchTriple*	pInstance = new CWallTorchTriple(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CWallTorchTriple Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CWallTorchTriple::Free()
{
	CLightObject::Free();
}

CWallTorchTriple * CWallTorchTriple::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CWallTorchTriple*	pInstance = new CWallTorchTriple(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CWallTorchTriple Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
