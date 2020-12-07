#include "stdafx.h"
#include "..\Header\SkillDamageNumPanel.h"
#include "../Header/NumIcon.h"

_USING(Client)

HRESULT CSkillDamageNumPanel::Initialize()
{
	return NOERROR;
}

HRESULT CSkillDamageNumPanel::Initialize(void * pArg)
{
	if (FAILED(Add_UI_Object(pArg)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CSkillDamageNumPanel::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CSkillDamageNumPanel::Add_UI_Object(void * pArg)
{
	D3DXVECTOR2* vMoveVector = (D3DXVECTOR2*)pArg;

	m_vNumIcon.push_back((CNumIcon*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUM_ICON", &DRAGPANEL(D3DXVECTOR2(-34.5f, -126), vMoveVector, D3DXVECTOR3(1.f,0.8f,0.1f)))));
	m_vNumIcon.push_back((CNumIcon*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUM_ICON", &DRAGPANEL(D3DXVECTOR2(-14.5f,  -126), vMoveVector, D3DXVECTOR3(1.f, 0.8f, 0.1f)))));

	return NOERROR;
}

CSkillDamageNumPanel::CSkillDamageNumPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CStatUI(_m_pGraphicDev)
{
}

CSkillDamageNumPanel::CSkillDamageNumPanel(const CSkillDamageNumPanel & rhs)
	: CStatUI(rhs)
{
}

_int CSkillDamageNumPanel::Progress(const _float & fTimeDelta)
{
	for (auto& iter : m_vNumIcon)
		iter->Progress(fTimeDelta);

	return _int();
}

_int CSkillDamageNumPanel::LateProgress(const _float & fTimeDelta)
{
	for (auto& iter : m_vNumIcon)
		iter->LateProgress(fTimeDelta);

	return _int();
}

HRESULT CSkillDamageNumPanel::Render()
{
	CPlayer* pPlayer = (CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
	if (pPlayer == nullptr)
		return E_FAIL;

	int iNum = pPlayer->GetPlayerInfo().iAbility[CPlayer::ABILITY_DAMAGE]*2;

	if (FAILED(m_vNumIcon[0]->SetTextureNum(iNum / 10)))
		return E_FAIL;

	if (FAILED(m_vNumIcon[1]->SetTextureNum(iNum % 10)))
		return E_FAIL;

	for (auto& iter : m_vNumIcon)
		iter->Render();

	return NOERROR;
}

CGameObject * CSkillDamageNumPanel::Clone(void * pArg)
{
	CSkillDamageNumPanel*	pInstance = new CSkillDamageNumPanel(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CSkillDamageNumPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CSkillDamageNumPanel::Free()
{
	for (auto& iter : m_vNumIcon)
		Safe_Release(iter);

	m_vNumIcon.clear();

	CGameObject::Free();
}

CSkillDamageNumPanel * CSkillDamageNumPanel::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CSkillDamageNumPanel*	pInstance = new CSkillDamageNumPanel(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CSkillDamageNumPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
