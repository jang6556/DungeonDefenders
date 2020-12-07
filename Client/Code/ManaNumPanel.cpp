#include "stdafx.h"
#include "..\Header\ManaNumPanel.h"
#include "../Header/NumIcon.h"

_USING(Client)

HRESULT CManaNumPanel::Initialize()
{
	return NOERROR;
}

HRESULT CManaNumPanel::Initialize(void * pArg)
{
	if (FAILED(Add_UI_Object(pArg)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CManaNumPanel::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CManaNumPanel::Add_UI_Object(void * pArg)
{
	D3DXVECTOR2* vMoveVector = (D3DXVECTOR2*)pArg;

	m_vNumIcon.push_back((CNumIcon*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUM_ICON", &DRAGPANEL(D3DXVECTOR2(144, -183), vMoveVector, D3DXVECTOR3(0.f, 0.3f, 1.f)))));
	m_vNumIcon.push_back((CNumIcon*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUM_ICON", &DRAGPANEL(D3DXVECTOR2(164, -183), vMoveVector, D3DXVECTOR3(0.f,0.3f,1.f)))));

	return NOERROR;
}

CManaNumPanel::CManaNumPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CStatUI(_m_pGraphicDev)
{
}

CManaNumPanel::CManaNumPanel(const CManaNumPanel & rhs)
	: CStatUI(rhs)
{
}

_int CManaNumPanel::Progress(const _float & fTimeDelta)
{
	for (auto& iter : m_vNumIcon)
		iter->Progress(fTimeDelta);

	return _int();
}

_int CManaNumPanel::LateProgress(const _float & fTimeDelta)
{
	for (auto& iter : m_vNumIcon)
		iter->LateProgress(fTimeDelta);

	return _int();
}

HRESULT CManaNumPanel::Render()
{
	CPlayer* pPlayer = (CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
	if (pPlayer == nullptr)
		return E_FAIL;
	int iNum = pPlayer->GetPlayerInfo().iAbility[CPlayer::ABILITY_MANA] * 3;

	if (FAILED(m_vNumIcon[0]->SetTextureNum(iNum / 10)))
		return E_FAIL;

	if (FAILED(m_vNumIcon[1]->SetTextureNum(iNum % 10)))
		return E_FAIL;

	for (auto& iter : m_vNumIcon)
		iter->Render();

	return NOERROR;
}

CGameObject * CManaNumPanel::Clone(void * pArg)
{
	CManaNumPanel*	pInstance = new CManaNumPanel(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CManaNumPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CManaNumPanel::Free()
{
	for (auto& iter : m_vNumIcon)
		Safe_Release(iter);

	m_vNumIcon.clear();

	CGameObject::Free();
}

CManaNumPanel * CManaNumPanel::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CManaNumPanel*	pInstance = new CManaNumPanel(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CManaNumPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
