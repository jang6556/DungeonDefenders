#include "stdafx.h"
#include "..\Header\HealthUpIcon.h"


_USING(Client)
HRESULT CHealthUpIcon::Initialize()
{	
	return NOERROR;
}

HRESULT CHealthUpIcon::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	if (pArg == nullptr)
		return E_FAIL;

	m_vMovePanel = (D3DXVECTOR2*)pArg;

	m_iPassNum = 7;
	m_iTexNum = 2;

	m_vScale = { 64,64 };

	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	m_vPosition = { -45,30 };
	m_pTransform->SetPosition(D3DXVECTOR3(m_vPosition.x, m_vPosition.y, 1));

	return NOERROR;
}

HRESULT CHealthUpIcon::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CHealthUpIcon::AddComponent()
{
	if (FAILED(CStatUI::AddComponent()))
		return E_FAIL;

	return NOERROR;
}

CHealthUpIcon::CHealthUpIcon(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CStatUI(_m_pGraphicDev)
{
}

CHealthUpIcon::CHealthUpIcon(const CHealthUpIcon & rhs)
	: CStatUI(rhs)
{
}

_int CHealthUpIcon::Progress(const _float & fTimeDelta)
{
	D3DXVECTOR2 vPosition = m_vPosition + *m_vMovePanel;

	if (true == CStatUI::CheckOnIcon(vPosition, m_vScale) && GetAsyncKeyState(VK_LBUTTON))
	{
		m_vScale.x -= fTimeDelta * 50;
		m_vScale.y -= fTimeDelta * 50;

		if (m_vScale.x <= 60)
			m_vScale.x = 60;

		if (m_vScale.y <= 60)
			m_vScale.y = 60;

		m_bClickIcon = true;

	}
	else
	{
		m_vScale.x += fTimeDelta * 50;
		m_vScale.y += fTimeDelta * 50;

		if (m_vScale.x >= 64)
			m_vScale.x = 64;

		if (m_vScale.y >= 64)
			m_vScale.y = 64;
	}

	if (m_bClickIcon == true && !GetAsyncKeyState(VK_LBUTTON))
	{
		CPlayer* pPlayer = (CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
		if (pPlayer != nullptr)
			pPlayer->UpAbility(CPlayer::ABILITY_HEALTH);
		m_bClickIcon = false;

		if (!CSoundMgr::GetSceneInst()->IsPlayingCheck(CSoundMgr::CLICK))
			CSoundMgr::GetSceneInst()->PlaySound("ButtonClick.ogg", CSoundMgr::CLICK);
	}

	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);
	
	return _int(CStatUI::Progress(fTimeDelta));
}

_int CHealthUpIcon::LateProgress(const _float & fTimeDelta)
{
	return _int(CStatUI::LateProgress(fTimeDelta));
}

HRESULT CHealthUpIcon::Render()
{
	D3DXVECTOR2 vPosition = m_vPosition + *m_vMovePanel;

	m_pTransform->SetPosition(D3DXVECTOR3(vPosition.x, vPosition.y, 1));

	return CStatUI::Render();
}

CGameObject * CHealthUpIcon::Clone(void * pArg)
{
	CHealthUpIcon*	pInstance = new CHealthUpIcon(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CHealthUpIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CHealthUpIcon::Free()
{
	CStatUI::Free();
}

CHealthUpIcon * CHealthUpIcon::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CHealthUpIcon*	pInstance = new CHealthUpIcon(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CHealthUpIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
