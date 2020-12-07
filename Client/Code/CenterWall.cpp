#include "stdafx.h"
#include "..\Header\CenterWall.h"


_USING(Client)

HRESULT CCenterWall::Initialize()
{
	return NOERROR;
}

HRESULT CCenterWall::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXMATRIX matWorld = *(D3DXMATRIX*)pArg;

	m_pTransform->SetWorldMatrix(matWorld);

	return NOERROR;
}

HRESULT CCenterWall::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CCenterWall::AddComponent()
{
	if (FAILED(CStaticMapObject::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"CENTER_WALL", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	return NOERROR;
}

CCenterWall::CCenterWall(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	: CStaticMapObject(_m_pGraphicDev)
{
}

CCenterWall::CCenterWall(const CCenterWall & rhs)
	: CStaticMapObject(rhs)
{
}

_int CCenterWall::Progress(const _float & fTimeDelta)
{
	return CStaticMapObject::Progress(fTimeDelta);
}

_int CCenterWall::LateProgress(const _float & fTimeDelta)
{
	return CStaticMapObject::LateProgress(fTimeDelta);
}

HRESULT CCenterWall::Render()
{
	return CStaticMapObject::Render();
}

CGameObject * CCenterWall::Clone(void * pArg)
{
	CCenterWall*	pInstance = new CCenterWall(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CCenterWall Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCenterWall::Free()
{
	CStaticMapObject::Free();
}

CCenterWall * CCenterWall::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CCenterWall*	pInstance = new CCenterWall(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CCenterWall Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
