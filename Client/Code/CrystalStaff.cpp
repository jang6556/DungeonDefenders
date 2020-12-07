#include "stdafx.h"
#include "..\Header\CrystalStaff.h"


_USING(Client)

HRESULT CCrystalStaff::Initialize()
{
	return NOERROR;
}

HRESULT CCrystalStaff::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXMATRIX matWorld = *(D3DXMATRIX*)pArg;

	m_pTransform->SetWorldMatrix(matWorld);

	if (FAILED(CLightObject::SetPointLight(SCENE_MAGNUS)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CCrystalStaff::Initialize_Prototype()
{
	if (FAILED(CLightObject::LoadLightData(L"Data/Crystal_Staff_Light.dat")))
		return E_FAIL;

	return NOERROR;
}

HRESULT CCrystalStaff::AddComponent()
{
	if (FAILED(CLightObject::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"CRYSTAL_STAFF", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;



	return NOERROR;
}

CCrystalStaff::CCrystalStaff(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CLightObject(_m_pGraphicDev)
{
}

CCrystalStaff::CCrystalStaff(const CCrystalStaff & rhs)
	: CLightObject(rhs)
{
}

_int CCrystalStaff::Progress(const _float & fTimeDelta)
{
	return CLightObject::Progress(fTimeDelta);
}

_int CCrystalStaff::LateProgress(const _float & fTimeDelta)
{
	return CLightObject::LateProgress(fTimeDelta);
}

HRESULT CCrystalStaff::Render()
{
	return CLightObject::Render();
}

CGameObject * CCrystalStaff::Clone(void * pArg)
{
	CCrystalStaff*	pInstance = new CCrystalStaff(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CCrystalStaff Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCrystalStaff::Free()
{
	CLightObject::Free();
}

CCrystalStaff * CCrystalStaff::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CCrystalStaff*	pInstance = new CCrystalStaff(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CCrystalStaff Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
