#include "stdafx.h"
#include "..\Header\BridgeWall.h"


_USING(Client)

HRESULT CBridgeWall::Initialize()
{
	return NOERROR;
}

HRESULT CBridgeWall::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXMATRIX matWorld = *(D3DXMATRIX*)pArg;

	m_pTransform->SetWorldMatrix(matWorld);

	m_fRadius = 100.f;
	return NOERROR;
}

HRESULT CBridgeWall::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CBridgeWall::AddComponent()
{
	if (FAILED(CStaticMapObject::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"BRIDGE_WALL", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	return NOERROR;
}

CBridgeWall::CBridgeWall(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	: CStaticMapObject(_m_pGraphicDev)
{
}

CBridgeWall::CBridgeWall(const CBridgeWall & rhs)
	: CStaticMapObject(rhs)
{
}

_int CBridgeWall::Progress(const _float & fTimeDelta)
{
	return CStaticMapObject::Progress(fTimeDelta);
}

_int CBridgeWall::LateProgress(const _float & fTimeDelta)
{
	return CStaticMapObject::LateProgress(fTimeDelta);
}

HRESULT CBridgeWall::Render()
{
	return CStaticMapObject::Render();
}

CGameObject * CBridgeWall::Clone(void * pArg)
{
	CBridgeWall*	pInstance = new CBridgeWall(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CBridgeWall Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBridgeWall::Free()
{
	CStaticMapObject::Free();
}

CBridgeWall * CBridgeWall::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CBridgeWall*	pInstance = new CBridgeWall(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CBridgeWall Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
