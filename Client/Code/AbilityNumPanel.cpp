#include "stdafx.h"
#include "..\Header\AbilityNumPanel.h"
#include "../Header/NumIcon.h"

_USING(Client)

HRESULT CAbilityNumPanel::Initialize()
{
	return NOERROR;
}

HRESULT CAbilityNumPanel::Initialize(void * pArg)
{
	if (FAILED(Add_UI_Object(pArg)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CAbilityNumPanel::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CAbilityNumPanel::Add_UI_Object(void * pArg)
{
	D3DXVECTOR2* vMoveVector = (D3DXVECTOR2*)pArg;

	m_vNumIcon.push_back((CNumIcon*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUM_ICON", &DRAGPANEL(D3DXVECTOR2(-142.f, -25.5f), vMoveVector, D3DXVECTOR3(0.9f, 0.9f, 0.9f)))));
	m_vNumIcon.push_back((CNumIcon*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUM_ICON", &DRAGPANEL(D3DXVECTOR2(-128.f, -25.5f), vMoveVector, D3DXVECTOR3(0.9f, 0.9f, 0.9f)))));

	m_vNumIcon.push_back((CNumIcon*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUM_ICON", &DRAGPANEL(D3DXVECTOR2(-51.f, -25.5f), vMoveVector, D3DXVECTOR3(0.9f, 0.9f, 0.9f)))));
	m_vNumIcon.push_back((CNumIcon*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUM_ICON", &DRAGPANEL(D3DXVECTOR2(-37.f, -25.5f), vMoveVector, D3DXVECTOR3(0.9f, 0.9f, 0.9f)))));

	m_vNumIcon.push_back((CNumIcon*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUM_ICON", &DRAGPANEL(D3DXVECTOR2(39, -25.5f), vMoveVector, D3DXVECTOR3(0.9f, 0.9f, 0.9f)))));
	m_vNumIcon.push_back((CNumIcon*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUM_ICON", &DRAGPANEL(D3DXVECTOR2(53, -25.5f), vMoveVector, D3DXVECTOR3(0.9f, 0.9f, 0.9f)))));
	
	m_vNumIcon.push_back((CNumIcon*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUM_ICON", &DRAGPANEL(D3DXVECTOR2(128, -25.5f), vMoveVector, D3DXVECTOR3(0.9f, 0.9f, 0.9f)))));
	m_vNumIcon.push_back((CNumIcon*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUM_ICON", &DRAGPANEL(D3DXVECTOR2(143, -25.5f), vMoveVector, D3DXVECTOR3(0.9f, 0.9f, 0.9f)))));
		
	m_vNumIcon.push_back((CNumIcon*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUM_ICON", &DRAGPANEL(D3DXVECTOR2(135, 137), vMoveVector, D3DXVECTOR3(1,1.f,0)))));
	
	for (auto& iter : m_vNumIcon)
		iter->SetScale(28.f);

	return NOERROR;
}

CAbilityNumPanel::CAbilityNumPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	: CStatUI(_m_pGraphicDev)
{
}

CAbilityNumPanel::CAbilityNumPanel(const CAbilityNumPanel & rhs)
	: CStatUI(rhs)
{
}

_int CAbilityNumPanel::Progress(const _float & fTimeDelta)
{
	for (auto& iter : m_vNumIcon)
		iter->Progress(fTimeDelta);

	return _int();
}

_int CAbilityNumPanel::LateProgress(const _float & fTimeDelta)
{
	for (auto& iter : m_vNumIcon)
		iter->LateProgress(fTimeDelta);

	return _int();
}

HRESULT CAbilityNumPanel::Render()
{
	CPlayer* pPlayer = (CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
	if (pPlayer == nullptr)
		return E_FAIL;

	if (FAILED(m_vNumIcon[0]->SetTextureNum(pPlayer->GetPlayerInfo().iAbility[CPlayer::ABILITY_DAMAGE] / 10)))
		return E_FAIL;

	if (FAILED(m_vNumIcon[1]->SetTextureNum(pPlayer->GetPlayerInfo().iAbility[CPlayer::ABILITY_DAMAGE] % 10)))
		return E_FAIL;

	if (FAILED(m_vNumIcon[2]->SetTextureNum(pPlayer->GetPlayerInfo().iAbility[CPlayer::ABILITY_HEALTH] / 10)))
		return E_FAIL;

	if (FAILED(m_vNumIcon[3]->SetTextureNum(pPlayer->GetPlayerInfo().iAbility[CPlayer::ABILITY_HEALTH] % 10)))
		return E_FAIL;

	if (FAILED(m_vNumIcon[4]->SetTextureNum(pPlayer->GetPlayerInfo().iAbility[CPlayer::ABILITY_COOL] / 10)))
		return E_FAIL;

	if (FAILED(m_vNumIcon[5]->SetTextureNum(pPlayer->GetPlayerInfo().iAbility[CPlayer::ABILITY_COOL] % 10)))
		return E_FAIL;

	if (FAILED(m_vNumIcon[6]->SetTextureNum(pPlayer->GetPlayerInfo().iAbility[CPlayer::ABILITY_MANA] / 10)))
		return E_FAIL;

	if (FAILED(m_vNumIcon[7]->SetTextureNum(pPlayer->GetPlayerInfo().iAbility[CPlayer::ABILITY_MANA] % 10)))
		return E_FAIL;

	if (FAILED(m_vNumIcon[8]->SetTextureNum(pPlayer->GetPlayerInfo().iLevel % 10)))
		return E_FAIL;

	for (auto& iter : m_vNumIcon)
		iter->Render();

	return NOERROR;
}

CGameObject * CAbilityNumPanel::Clone(void * pArg)
{
	CAbilityNumPanel*	pInstance = new CAbilityNumPanel(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CAbilityNumPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CAbilityNumPanel::Free()
{
	for (auto& iter : m_vNumIcon)
		Safe_Release(iter);

	m_vNumIcon.clear();

	CGameObject::Free();
}

CAbilityNumPanel * CAbilityNumPanel::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CAbilityNumPanel*	pInstance = new CAbilityNumPanel(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CAbilityNumPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
