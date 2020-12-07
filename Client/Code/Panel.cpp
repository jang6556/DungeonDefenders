#include "stdafx.h"
#include "..\Header\Panel.h"

_USING(Client)

HRESULT CPanel::Initialize()
{
	if (FAILED(Add_UI_Object()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CPanel::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CPanel::Add_UI_Object()
{
	m_vPanel.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"VERTICALBACKGROUND"));
	m_vPanel.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"VERTICALBACKGROUNDREV"));
	m_vPanel.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"VERTICALHPEFFECT"));
	m_vPanel.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"VERTICALMPEFFECT"));
	m_vPanel.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"VERTICALHP"));
	m_vPanel.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"VERTICALMP"));
	m_vPanel.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"SKILL_ICON_1"));
	m_vPanel.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"SKILL_ICON_2"));
	m_vPanel.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"SKILL_ICON_3"));
	m_vPanel.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"SKILL_ICON_4"));
	m_vPanel.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"SKILL_ICON_5"));
	m_vPanel.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"SKILL_ICON_6"));
	m_vPanel.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"SKILL_ICON_7"));
	m_vPanel.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"SKILL_ICON_8"));
	m_vPanel.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"SKILL_ICON_9"));
	m_vPanel.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"SKILL_ICON_10"));	
	m_vPanel.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"EXP_BAR"));
	m_vPanel.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"BUILD_LOADING_BAR"));
	m_vPanel.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"BUILD_LOADING_CONTENT"));
	m_vPanel.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"PLAYER_INFO"));
	m_vPanel.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"SKILLPANEL"));
	m_vPanel.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_PANEL"));
	m_vPanel.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"TEXT_PANEL"));
	
	return NOERROR;
}

CPanel::CPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{

}

CPanel::CPanel(const CPanel & rhs)
	:CGameObject(rhs)
{

}

_int CPanel::Progress(const _float & fTimeDelta)
{
	for (auto& iter : m_vPanel)
		iter->Progress(fTimeDelta);
	return _int();
}

_int CPanel::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::UI, this)))
		return -1;

	for (auto& iter : m_vPanel)
		iter->LateProgress(fTimeDelta);


	return _int();
}

HRESULT CPanel::Render()
{
	for (auto& iter : m_vPanel)
		iter->Render();

	return NOERROR;
}

CGameObject * CPanel::Clone(void * pArg)
{
	CPanel*	pInstance = new CPanel(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CPanel::Free()
{
	Safe_Release(m_pRenderer);
	for (auto& iter : m_vPanel)
		Safe_Release(iter);

	CGameObject::Free();
}

CPanel * CPanel::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CPanel*	pInstance = new CPanel(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
