#include "stdafx.h"
#include "..\Header\RailSet.h"

_USING(Client)

HRESULT CRailSet::Initialize()
{
	return NOERROR;
}

HRESULT CRailSet::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXMATRIX matWorld = *(D3DXMATRIX*)pArg;

	m_pTransform->SetWorldMatrix(matWorld);

	m_fRadius = 10.f;

	return NOERROR;
}

HRESULT CRailSet::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CRailSet::AddComponent()
{
	if (FAILED(CStaticMapObject::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SET_RAIL", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	return NOERROR;
}

CRailSet::CRailSet(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	: CStaticMapObject(_m_pGraphicDev)
{
}

CRailSet::CRailSet(const CRailSet & rhs)
	: CStaticMapObject(rhs)
{
}

_int CRailSet::Progress(const _float & fTimeDelta)
{
	return CStaticMapObject::Progress(fTimeDelta);
}

_int CRailSet::LateProgress(const _float & fTimeDelta)
{
	return CStaticMapObject::LateProgress(fTimeDelta);
}

HRESULT CRailSet::Render()
{
	return CStaticMapObject::Render();
}

CGameObject * CRailSet::Clone(void * pArg)
{
	CRailSet*	pInstance = new CRailSet(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CRailSet Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CRailSet::Free()
{
	CStaticMapObject::Free();
}

CRailSet * CRailSet::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CRailSet*	pInstance = new CRailSet(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CRailSet Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
