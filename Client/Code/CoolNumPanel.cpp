#include "stdafx.h"
#include "..\Header\CoolNumPanel.h"
#include "../Header/NumIcon.h"

_USING(Client)

HRESULT CCoolNumPanel::Initialize()
{
	return NOERROR;
}

HRESULT CCoolNumPanel::Initialize(void * pArg)
{
	if (FAILED(Add_UI_Object(pArg)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CCoolNumPanel::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CCoolNumPanel::Add_UI_Object(void * pArg)
{
	D3DXVECTOR2* vMoveVector = (D3DXVECTOR2*)pArg;

	m_vNumIcon.push_back((CNumIcon*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUM_ICON", &DRAGPANEL(D3DXVECTOR2(144, -126), vMoveVector, D3DXVECTOR3(0.0f,0.7f,0.f)))));
	m_vNumIcon.push_back((CNumIcon*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUM_ICON", &DRAGPANEL(D3DXVECTOR2(164, -126), vMoveVector, D3DXVECTOR3(0.0f,0.7f,0.f)))));


	return NOERROR;
}

CCoolNumPanel::CCoolNumPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CStatUI(_m_pGraphicDev)
{
}

CCoolNumPanel::CCoolNumPanel(const CCoolNumPanel & rhs)
	: CStatUI(rhs)
{
}

_int CCoolNumPanel::Progress(const _float & fTimeDelta)
{
	for (auto& iter : m_vNumIcon)
		iter->Progress(fTimeDelta);

	return _int();
}

_int CCoolNumPanel::LateProgress(const _float & fTimeDelta)
{
	for (auto& iter : m_vNumIcon)
		iter->LateProgress(fTimeDelta);

	return _int();
}

HRESULT CCoolNumPanel::Render()
{
	CPlayer* pPlayer = (CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
	if (pPlayer == nullptr)
		return E_FAIL;

	int iNum = pPlayer->GetPlayerInfo().iAbility[CPlayer::ABILITY_COOL] * 2;

	if (FAILED(m_vNumIcon[0]->SetTextureNum(iNum / 10)))
		return E_FAIL;

	if (FAILED(m_vNumIcon[1]->SetTextureNum(iNum % 10)))
		return E_FAIL;

	for (auto& iter : m_vNumIcon)
		iter->Render();

	return NOERROR;
}

CGameObject * CCoolNumPanel::Clone(void * pArg)
{
	CCoolNumPanel*	pInstance = new CCoolNumPanel(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CCoolNumPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCoolNumPanel::Free()
{
	for (auto& iter : m_vNumIcon)
		Safe_Release(iter);

	m_vNumIcon.clear();

	CGameObject::Free();
}

CCoolNumPanel * CCoolNumPanel::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CCoolNumPanel*	pInstance = new CCoolNumPanel(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CCoolNumPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
