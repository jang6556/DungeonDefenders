#include "stdafx.h"
#include "..\Header\DoubleRail.h"


_USING(Client)

HRESULT CDoubleRail::Initialize()
{
	return NOERROR;
}

HRESULT CDoubleRail::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXMATRIX matWorld = *(D3DXMATRIX*)pArg;

	m_pTransform->SetWorldMatrix(matWorld);

	m_fRadius = 10.f;

	return NOERROR;
}

HRESULT CDoubleRail::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CDoubleRail::AddComponent()
{
	if (FAILED(CStaticMapObject::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"DOUBLE_RAIL", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	return NOERROR;
}

CDoubleRail::CDoubleRail(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	: CStaticMapObject(_m_pGraphicDev)
{
}

CDoubleRail::CDoubleRail(const CDoubleRail & rhs)
	: CStaticMapObject(rhs)
{
}

_int CDoubleRail::Progress(const _float & fTimeDelta)
{
	return CStaticMapObject::Progress(fTimeDelta);
}

_int CDoubleRail::LateProgress(const _float & fTimeDelta)
{
	return CStaticMapObject::LateProgress(fTimeDelta);
}

HRESULT CDoubleRail::Render()
{
	return CStaticMapObject::Render();
}

CGameObject * CDoubleRail::Clone(void * pArg)
{
	CDoubleRail*	pInstance = new CDoubleRail(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CDoubleRail Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CDoubleRail::Free()
{
	CStaticMapObject::Free();
}

CDoubleRail * CDoubleRail::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CDoubleRail*	pInstance = new CDoubleRail(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CDoubleRail Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
