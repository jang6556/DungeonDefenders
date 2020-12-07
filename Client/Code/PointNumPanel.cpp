#include "stdafx.h"
#include "..\Header\PointNumPanel.h"
#include "../Header/NumIcon.h"

_USING(Client)
HRESULT CPointNumPanel::Initialize()
{
	return NOERROR;
}

HRESULT CPointNumPanel::Initialize(void * pArg)
{
	if (FAILED(Add_UI_Object(pArg)))
		return E_FAIL;


	return NOERROR;
}

HRESULT CPointNumPanel::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CPointNumPanel::Add_UI_Object(void * pArg)
{
	D3DXVECTOR2* vMoveVector =(D3DXVECTOR2*)pArg;

	m_vNumIcon.push_back((CNumIcon*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUM_ICON",&DRAGPANEL(D3DXVECTOR2(27, 94), vMoveVector, D3DXVECTOR3( 1,0.3f, 0.f)))));
	m_vNumIcon.push_back((CNumIcon*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUM_ICON",&DRAGPANEL(D3DXVECTOR2(47, 94), vMoveVector, D3DXVECTOR3( 1,0.3f, 0.f)))));

	return NOERROR;
}

CPointNumPanel::CPointNumPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	: CStatUI(_m_pGraphicDev)
{
}

CPointNumPanel::CPointNumPanel(const CPointNumPanel & rhs)
	: CStatUI(rhs)
{
}

_int CPointNumPanel::Progress(const _float & fTimeDelta)
{
	for (auto& iter : m_vNumIcon)
		iter->Progress(fTimeDelta);

	return _int();
}

_int CPointNumPanel::LateProgress(const _float & fTimeDelta)
{
	for (auto& iter : m_vNumIcon)
		iter->LateProgress(fTimeDelta);

	return _int();
}

HRESULT CPointNumPanel::Render()
{
	CPlayer* pPlayer = (CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
	if (pPlayer == nullptr)
		return E_FAIL;

	if (FAILED(m_vNumIcon[0]->SetTextureNum(pPlayer->GetPlayerInfo().iAbilityPoint / 10)))
		return E_FAIL;

	if (FAILED(m_vNumIcon[1]->SetTextureNum(pPlayer->GetPlayerInfo().iAbilityPoint % 10)))
		return E_FAIL;	

	for (auto& iter : m_vNumIcon)
		iter->Render();

	return NOERROR;
}

CGameObject * CPointNumPanel::Clone(void * pArg)
{
	CPointNumPanel*	pInstance = new CPointNumPanel(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CPointNumPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CPointNumPanel::Free()
{
	for (auto& iter : m_vNumIcon)
		Safe_Release(iter);

	m_vNumIcon.clear();

	CGameObject::Free();
}

CPointNumPanel * CPointNumPanel::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CPointNumPanel*	pInstance = new CPointNumPanel(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CPointNumPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
