#include "stdafx.h"
#include "..\Header\LongRail.h"


_USING(Client)

HRESULT CLongRail::Initialize()
{
	return NOERROR;
}

HRESULT CLongRail::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXMATRIX matWorld = *(D3DXMATRIX*)pArg;

	m_pTransform->SetWorldMatrix(matWorld);

	m_fRadius = 10.f;

	return NOERROR;
}

HRESULT CLongRail::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CLongRail::AddComponent()
{
	if (FAILED(CStaticMapObject::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"LONG_RAIL", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	return NOERROR;
}

CLongRail::CLongRail(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	: CStaticMapObject(_m_pGraphicDev)
{
}

CLongRail::CLongRail(const CLongRail & rhs)
	: CStaticMapObject(rhs)
{
}

_int CLongRail::Progress(const _float & fTimeDelta)
{
	return CStaticMapObject::Progress(fTimeDelta);
}

_int CLongRail::LateProgress(const _float & fTimeDelta)
{
	return CStaticMapObject::LateProgress(fTimeDelta);
}

HRESULT CLongRail::Render()
{
	return CStaticMapObject::Render();
}

CGameObject * CLongRail::Clone(void * pArg)
{
	CLongRail*	pInstance = new CLongRail(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CLongRail Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLongRail::Free()
{
	CStaticMapObject::Free();
}

CLongRail * CLongRail::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CLongRail*	pInstance = new CLongRail(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CLongRail Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
