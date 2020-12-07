#include "stdafx.h"
#include "..\Header\StatPanel.h"
#include "../Header/StatUI.h"


_USING(Client)
HRESULT CStatPanel::Initialize()
{
	if (FAILED(Add_UI_Object()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CStatPanel::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CStatPanel::Add_UI_Object()
{
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"STAT_UI_BACKGROUND",&m_vMovePanel));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"DAMAGE_UP_ICON",&m_vMovePanel));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"HEALTH_UP_ICON",&m_vMovePanel));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"COOL_DOWN_ICON",&m_vMovePanel));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"MANA_DOWN_ICON",&m_vMovePanel));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"PLAYER_INFO_PANEL", &m_vMovePanel));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"EMPTY_PANEL", &DRAGPANEL(D3DXVECTOR2(-135,-25),&m_vMovePanel)));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"EMPTY_PANEL", &DRAGPANEL(D3DXVECTOR2(-45, -25), &m_vMovePanel)));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"EMPTY_PANEL", &DRAGPANEL(D3DXVECTOR2( 45, -25), &m_vMovePanel)));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"EMPTY_PANEL", &DRAGPANEL(D3DXVECTOR2( 135, -25), &m_vMovePanel)));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"POINT_ICON", &DRAGPANEL(D3DXVECTOR2(-60, 95), &m_vMovePanel)));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"ATTACK_PANEL", &DRAGPANEL(D3DXVECTOR2(-65, -70), &m_vMovePanel)));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"SKILL_DAMAGE_PANEL", &DRAGPANEL(D3DXVECTOR2(-128.5f, -126), &m_vMovePanel)));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"HEALTH_PANEL", &DRAGPANEL(D3DXVECTOR2(-126.5f, -183), &m_vMovePanel)));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"COOL_PANEL", &DRAGPANEL(D3DXVECTOR2(63, -128), &m_vMovePanel)));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"MANA_PANEL", &DRAGPANEL(D3DXVECTOR2(60, -181), &m_vMovePanel)));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"LEVEL_PANEL", &DRAGPANEL(D3DXVECTOR2(85, 139), &m_vMovePanel)));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"DOT_ICON", &DRAGPANEL(D3DXVECTOR2(-60, -181.5), &m_vMovePanel,D3DXVECTOR3(1, 0.f, 0))));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"DOT_ICON", &DRAGPANEL(D3DXVECTOR2(117.5f, -125), &m_vMovePanel, D3DXVECTOR3(0.0f, 0.7f, 0.f))));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"DOT_ICON", &DRAGPANEL(D3DXVECTOR2(-60, -125), &m_vMovePanel, D3DXVECTOR3(1.f, 0.8f, 0.1f))));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"DOT_ICON", &DRAGPANEL(D3DXVECTOR2(117.5f, -181.5), &m_vMovePanel, D3DXVECTOR3(0.f, 0.3f, 1.f))));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"DOT_ICON", &DRAGPANEL(D3DXVECTOR2(5, -70), &m_vMovePanel, D3DXVECTOR3(1.f, 1.3f, 1.f))));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"POINT_NUM_PANEL", &m_vMovePanel));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"ATTACK_NUM_PANEL", &m_vMovePanel));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"SKILL_NUM_PANEL", &m_vMovePanel));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"HEALTH_NUM_PANEL", &m_vMovePanel));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"COOL_NUM_PANEL", &m_vMovePanel));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"MANA_NUM_PANEL", &m_vMovePanel));
	m_vStatUI.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"ABILITY_NUM_PANEL", &m_vMovePanel));
	
	return NOERROR;
}

CStatPanel::CStatPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CStatPanel::CStatPanel(const CStatPanel & rhs)
	: CGameObject(rhs)
{
}

_int CStatPanel::Progress(const _float & fTimeDelta)
{
	for (auto& iter : m_vStatUI)
		iter->Progress(fTimeDelta);

	return _int();
}

_int CStatPanel::LateProgress(const _float & fTimeDelta)
{
	for (auto& iter : m_vStatUI)
		iter->LateProgress(fTimeDelta);

	if (m_IsRender == true)
	{
		if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::UI, this)))
			return -1;
	}

	return _int();
}

HRESULT CStatPanel::Render()
{
	for (auto& iter : m_vStatUI)
	{
		if (FAILED(iter->Render()))
			return E_FAIL;
	}

	return NOERROR;
}

CGameObject * CStatPanel::Clone(void * pArg)
{
	CStatPanel*	pInstance = new CStatPanel(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CStatPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

HRESULT CStatPanel::RenderSwitch()
{
	m_IsRender = m_IsRender ? false : true;

	for (auto& iter : m_vStatUI)
	{
		dynamic_cast<CStatUI*>(iter)->RenderSwitch();
	}

	return NOERROR;
}

void CStatPanel::Free()
{
	Safe_Release(m_pRenderer);
	for (auto& iter : m_vStatUI)
		Safe_Release(iter);

	CGameObject::Free();
}

CStatPanel * CStatPanel::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CStatPanel*	pInstance = new CStatPanel(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CStatPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
