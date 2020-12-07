#include "stdafx.h"
#include "..\Header\AttackNumPanel.h"
#include "../Header/NumIcon.h"

_USING(Client)
HRESULT CAttackNumPanel::Initialize()
{
	return NOERROR;
}

HRESULT CAttackNumPanel::Initialize(void * pArg)
{
	if (FAILED(Add_UI_Object(pArg)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CAttackNumPanel::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CAttackNumPanel::Add_UI_Object(void * pArg)
{
	D3DXVECTOR2* vMoveVector = (D3DXVECTOR2*)pArg;

	m_vNumIcon.push_back((CNumIcon*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUM_ICON", &DRAGPANEL(D3DXVECTOR2(28, -70), vMoveVector, D3DXVECTOR3(1.f,1.f,1.f)))));
	m_vNumIcon.push_back((CNumIcon*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUM_ICON", &DRAGPANEL(D3DXVECTOR2(48, -70), vMoveVector, D3DXVECTOR3(1.f,1.f,1.f)))));

	return NOERROR;
}

CAttackNumPanel::CAttackNumPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CStatUI(_m_pGraphicDev)
{
}

CAttackNumPanel::CAttackNumPanel(const CAttackNumPanel & rhs)
	: CStatUI(rhs)
{
}

_int CAttackNumPanel::Progress(const _float & fTimeDelta)
{
	for (auto& iter : m_vNumIcon)
		iter->Progress(fTimeDelta);

	return _int();
}

_int CAttackNumPanel::LateProgress(const _float & fTimeDelta)
{
	for (auto& iter : m_vNumIcon)
		iter->LateProgress(fTimeDelta);

	return _int();
}

HRESULT CAttackNumPanel::Render()
{
	CPlayer* pPlayer = (CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
	if (pPlayer == nullptr)
		return E_FAIL;

	if (FAILED(m_vNumIcon[0]->SetTextureNum(pPlayer->GetPlayerInfo().iAttack / 10)))
		return E_FAIL;

	if (FAILED(m_vNumIcon[1]->SetTextureNum(pPlayer->GetPlayerInfo().iAttack % 10)))
		return E_FAIL;

	for (auto& iter : m_vNumIcon)
		iter->Render();

	return NOERROR;
}

CGameObject * CAttackNumPanel::Clone(void * pArg)
{
	CAttackNumPanel*	pInstance = new CAttackNumPanel(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CAttackNumPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CAttackNumPanel::Free()
{
	for (auto& iter : m_vNumIcon)
		Safe_Release(iter);

	m_vNumIcon.clear();

	CGameObject::Free();
}

CAttackNumPanel * CAttackNumPanel::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CAttackNumPanel*	pInstance = new CAttackNumPanel(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CAttackNumPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
