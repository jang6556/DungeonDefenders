#include "stdafx.h"
#include "..\Header\PlayerInfo.h"


_USING(Client)

HRESULT CPlayerInfo::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	m_pTransform->Scaling(235.5f, 107.5f, 0);
	m_pTransform->Move(523.f, -306.5f, 0, 1, 1);

	m_iTexNum = 8;
	m_iPassNum = 0;

	return NOERROR;
}

HRESULT CPlayerInfo::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CPlayerInfo::AddComponent()
{
	if (FAILED(CPlayerUI::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADERUI", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"PANEL", (CComponent**)&m_Texture)))
		return E_FAIL;

	return NOERROR;
}

CPlayerInfo::CPlayerInfo(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	: CPlayerUI(_m_pGraphicDev)
{
}

CPlayerInfo::CPlayerInfo(const CPlayerInfo & rhs)
	: CPlayerUI(rhs)
{
}

_int CPlayerInfo::Progress(const _float & fTimeDelta)
{
	
	return _int();
}

_int CPlayerInfo::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CPlayerInfo::Render()
{
	return CPlayerUI::Render();
}

CGameObject * CPlayerInfo::Clone(void * pArg)
{
	CPlayerInfo*	pInstance = new CPlayerInfo(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CPlayerInfo Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CPlayerInfo::Free()
{
	CPlayerUI::Free();
}

CPlayerInfo * CPlayerInfo::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CPlayerInfo*	pInstance = new CPlayerInfo(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CPlayerInfo Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
