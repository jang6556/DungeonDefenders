#include "stdafx.h"
#include "..\Header\TextPanel.h"
#include "../Header/TextUI.h"

_USING(Client)

HRESULT CTextPanel::Initialize()
{
	if (FAILED(Add_UI_Object()))
		return E_FAIL;
	return NOERROR;
}

HRESULT CTextPanel::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CTextPanel::Add_UI_Object()
{

	/////////////페이즈 가변
	m_vTextIcon.push_back((CTextUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"TEXT_UI", &DRAGPANEL(D3DXVECTOR2(555.5f, 257.5f), nullptr, D3DXVECTOR3(1.f, 1.f, 1.f)))));
	m_vTextIcon.back()->SetTextureNum(1);
	m_vTextIcon.back()->SetScale(90.f, 22.5f);

	/////웨이브
	m_vTextIcon.push_back((CTextUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"TEXT_UI", &DRAGPANEL(D3DXVECTOR2(554.f, 327.5f), nullptr, D3DXVECTOR3(1.f, 1.f, 1.f)))));
	m_vTextIcon.back()->SetTextureNum(5);
	m_vTextIcon.back()->SetScale(81.f, 40.5f); 

	/////킬수
	m_vTextIcon.push_back((CTextUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"TEXT_UI", &DRAGPANEL(D3DXVECTOR2(554.f, 206.f), nullptr, D3DXVECTOR3(1.f, 1.f, 1.f)))));
	m_vTextIcon.back()->SetTextureNum(2);
	m_vTextIcon.back()->SetScale(192.f, 24.f); 

	m_vTextIcon.push_back((CTextUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"TEXT_UI", &DRAGPANEL(D3DXVECTOR2(509, -283.f), nullptr, D3DXVECTOR3(1.f, 0.5f, 0.25f)))));
	m_vTextIcon.back()->SetTextureNum(3);
	m_vTextIcon.back()->SetScale(86, 30.f); 
	m_vTextIcon.back()->SetShaderNum(8);

	m_vTextIcon.push_back((CTextUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"TEXT_UI", &DRAGPANEL(D3DXVECTOR2(525.f, -330.f), nullptr, D3DXVECTOR3(1.f, 1.f, 1.f)))));
	m_vTextIcon.back()->SetTextureNum(4);
	m_vTextIcon.back()->SetScale(134.f, 30.f); 


	return NOERROR;
}

CTextPanel::CTextPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CTextPanel::CTextPanel(const CTextPanel & rhs)
	: CGameObject(rhs)
{
}

_int CTextPanel::Progress(const _float & fTimeDelta)
{
	for (auto& iter : m_vTextIcon)
		iter->Progress(fTimeDelta);
	return _int();
}

_int CTextPanel::LateProgress(const _float & fTimeDelta)
{
	for (auto& iter : m_vTextIcon)
		iter->LateProgress(fTimeDelta);
	return _int();
}

HRESULT CTextPanel::Render()
{
	CMonsterController* pMonsterController = (CMonsterController*)CGameObjectMgr::GetInstance()->FindGameObject(CManageMent::GetInstance()->GetCurrSceneID(), L"CONTROLLER");
	if (pMonsterController == nullptr)
		return E_FAIL;

	if (pMonsterController->GetWaveInfo().w == 1)
		m_vTextIcon.front()->SetTextureNum(1);
	else
		m_vTextIcon.front()->SetTextureNum(0);

	for (auto& iter : m_vTextIcon)
		iter->Render();

	return NOERROR;
}

CGameObject * CTextPanel::Clone(void * pArg)
{
	CTextPanel*	pInstance = new CTextPanel(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CTextPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTextPanel::Free()
{
	for (auto& iter : m_vTextIcon)
		Safe_Release(iter);

	m_vTextIcon.clear();
	CGameObject::Free();
}

CTextPanel * CTextPanel::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CTextPanel*	pInstance = new CTextPanel(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CTextPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
