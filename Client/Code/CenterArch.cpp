#include "stdafx.h"
#include "..\Header\CenterArch.h"


_USING(Client)

HRESULT CCenterArch::Initialize()
{
	return NOERROR;
}

HRESULT CCenterArch::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXMATRIX matWorld = *(D3DXMATRIX*)pArg;

	m_pTransform->SetWorldMatrix(matWorld);

	return NOERROR;
}

HRESULT CCenterArch::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CCenterArch::AddComponent()
{
	if (FAILED(CStaticMapObject::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"CENTER_ARCH", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	return NOERROR;
}

CCenterArch::CCenterArch(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	: CStaticMapObject(_m_pGraphicDev)
{
}

CCenterArch::CCenterArch(const CCenterArch & rhs)
	: CStaticMapObject(rhs)
{
}

_int CCenterArch::Progress(const _float & fTimeDelta)
{
	return CStaticMapObject::Progress(fTimeDelta);
}

_int CCenterArch::LateProgress(const _float & fTimeDelta)
{
	return CStaticMapObject::LateProgress(fTimeDelta);
}

HRESULT CCenterArch::Render()
{
	return CStaticMapObject::Render();
}

CGameObject * CCenterArch::Clone(void * pArg)
{
	CCenterArch*	pInstance = new CCenterArch(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CCenterArch Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCenterArch::Free()
{
	CStaticMapObject::Free();
}

CCenterArch * CCenterArch::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CCenterArch*	pInstance = new CCenterArch(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CCenterArch Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
