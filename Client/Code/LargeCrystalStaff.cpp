#include "stdafx.h"
#include "..\Header\LargeCrystalStaff.h"


_USING(Client)

HRESULT CLargeCrystalStaff::Initialize()
{
	return NOERROR;
}

HRESULT CLargeCrystalStaff::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXMATRIX matWorld = *(D3DXMATRIX*)pArg;

	m_pTransform->SetWorldMatrix(matWorld);

	if (FAILED(CLightObject::SetPointLight(SCENE_MAGNUS)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CLargeCrystalStaff::Initialize_Prototype()
{
	if (FAILED(CLightObject::LoadLightData(L"Data/LargeCrystalStaff.dat")))
		return E_FAIL;

	return NOERROR;
}

HRESULT CLargeCrystalStaff::AddComponent()
{
	if (FAILED(CLightObject::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"LARGE_CRYSTAL", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;



	return NOERROR;
}

CLargeCrystalStaff::CLargeCrystalStaff(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CLightObject(_m_pGraphicDev)
{
}

CLargeCrystalStaff::CLargeCrystalStaff(const CLargeCrystalStaff & rhs)
	: CLightObject(rhs)
{
}

_int CLargeCrystalStaff::Progress(const _float & fTimeDelta)
{
	return CLightObject::Progress(fTimeDelta);
}

_int CLargeCrystalStaff::LateProgress(const _float & fTimeDelta)
{
	return CLightObject::LateProgress(fTimeDelta);
}

HRESULT CLargeCrystalStaff::Render()
{
	return CLightObject::Render();
}

CGameObject * CLargeCrystalStaff::Clone(void * pArg)
{
	CLargeCrystalStaff*	pInstance = new CLargeCrystalStaff(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CLargeCrystalStaff Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLargeCrystalStaff::Free()
{
	CLightObject::Free();
}

CLargeCrystalStaff * CLargeCrystalStaff::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CLargeCrystalStaff*	pInstance = new CLargeCrystalStaff(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CLargeCrystalStaff Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
