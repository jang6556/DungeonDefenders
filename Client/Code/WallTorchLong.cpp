#include "stdafx.h"
#include "..\Header\WallTorchLong.h"


_USING(Client)

HRESULT CWallTorchLong::Initialize()
{
	return NOERROR;
}

HRESULT CWallTorchLong::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXMATRIX matWorld = *(D3DXMATRIX*)pArg;

	m_pTransform->SetWorldMatrix(matWorld);

	if (FAILED(CLightObject::SetPointLight(SCENE_MAGNUS)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CWallTorchLong::Initialize_Prototype()
{
	if (FAILED(CLightObject::LoadLightData(L"Data/WallTorch_Long_Light.dat")))
		return E_FAIL;
	return NOERROR;
}

HRESULT CWallTorchLong::AddComponent()
{
	if (FAILED(CLightObject::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"WALLTORCH_LONG", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	return NOERROR;
}

CWallTorchLong::CWallTorchLong(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CLightObject(_m_pGraphicDev)
{
}

CWallTorchLong::CWallTorchLong(const CWallTorchLong & rhs)
	: CLightObject(rhs)
{
}

_int CWallTorchLong::Progress(const _float & fTimeDelta)
{
	return CLightObject::Progress(fTimeDelta);
}

_int CWallTorchLong::LateProgress(const _float & fTimeDelta)
{
	return CLightObject::LateProgress(fTimeDelta);
}

HRESULT CWallTorchLong::Render()
{
	return CLightObject::Render();
}

CGameObject * CWallTorchLong::Clone(void * pArg)
{
	CWallTorchLong*	pInstance = new CWallTorchLong(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CWallTorchLong Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CWallTorchLong::Free()
{
	CLightObject::Free();
}

CWallTorchLong * CWallTorchLong::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CWallTorchLong*	pInstance = new CWallTorchLong(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CWallTorchLong Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
