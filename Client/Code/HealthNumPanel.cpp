#include "stdafx.h"
#include "..\Header\HealthNumPanel.h"
#include "../Header/NumIcon.h"

_USING(Client)

HRESULT CHealthNumPanel::Initialize()
{
	return NOERROR;
}

HRESULT CHealthNumPanel::Initialize(void * pArg)
{
	if (FAILED(Add_UI_Object(pArg)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CHealthNumPanel::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CHealthNumPanel::Add_UI_Object(void * pArg)
{
	D3DXVECTOR2* vMoveVector = (D3DXVECTOR2*)pArg;

	m_vNumIcon.push_back((CNumIcon*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUM_ICON", &DRAGPANEL(D3DXVECTOR2(-34.5f, -183), vMoveVector, D3DXVECTOR3(1,0.f,0)))));
	m_vNumIcon.push_back((CNumIcon*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUM_ICON", &DRAGPANEL(D3DXVECTOR2(-14.5f,  -183), vMoveVector, D3DXVECTOR3(1,0.f,0)))));

	return NOERROR;
}

CHealthNumPanel::CHealthNumPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CStatUI(_m_pGraphicDev)
{
}

CHealthNumPanel::CHealthNumPanel(const CHealthNumPanel & rhs)
	: CStatUI(rhs)
{
}

_int CHealthNumPanel::Progress(const _float & fTimeDelta)
{
	for (auto& iter : m_vNumIcon)
		iter->Progress(fTimeDelta);

	return _int();
}

_int CHealthNumPanel::LateProgress(const _float & fTimeDelta)
{
	for (auto& iter : m_vNumIcon)
		iter->LateProgress(fTimeDelta);

	return _int();
}

HRESULT CHealthNumPanel::Render()
{
	CPlayer* pPlayer = (CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
	if (pPlayer == nullptr)
		return E_FAIL;

	int iNum = pPlayer->GetPlayerInfo().iAbility[CPlayer::ABILITY_HEALTH] * 2;

	if (FAILED(m_vNumIcon[0]->SetTextureNum(iNum / 10)))
		return E_FAIL;

	if (FAILED(m_vNumIcon[1]->SetTextureNum(iNum % 10)))
		return E_FAIL;

	for (auto& iter : m_vNumIcon)
		iter->Render();

	return NOERROR;
}

CGameObject * CHealthNumPanel::Clone(void * pArg)
{
	CHealthNumPanel*	pInstance = new CHealthNumPanel(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CHealthNumPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CHealthNumPanel::Free()
{
	for (auto& iter : m_vNumIcon)
		Safe_Release(iter);

	m_vNumIcon.clear();

	CGameObject::Free();
}

CHealthNumPanel * CHealthNumPanel::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CHealthNumPanel*	pInstance = new CHealthNumPanel(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CHealthNumPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
