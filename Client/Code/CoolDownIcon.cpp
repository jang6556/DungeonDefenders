#include "stdafx.h"
#include "..\Header\CoolDownIcon.h"


_USING(Client)

HRESULT CCoolDownIcon::Initialize()
{
	return NOERROR;
}

HRESULT CCoolDownIcon::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	if (pArg == nullptr)
		return E_FAIL;

	m_vMovePanel = (D3DXVECTOR2*)pArg;

	m_iPassNum = 7;
	m_iTexNum = 3;

	m_vScale = { 64,64 };

	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	m_vPosition = { 45,30 };
	m_pTransform->SetPosition(D3DXVECTOR3(m_vPosition.x, m_vPosition.y, 1));

	return NOERROR;
}

HRESULT CCoolDownIcon::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CCoolDownIcon::AddComponent()
{
	if (FAILED(CStatUI::AddComponent()))
		return E_FAIL;

	return NOERROR;
}

CCoolDownIcon::CCoolDownIcon(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CStatUI(_m_pGraphicDev)
{
}

CCoolDownIcon::CCoolDownIcon(const CCoolDownIcon & rhs)
	: CStatUI(rhs)
{
}

_int CCoolDownIcon::Progress(const _float & fTimeDelta)
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
			pPlayer->UpAbility(CPlayer::ABILITY_COOL);

		m_bClickIcon = false;
		

		if (!CSoundMgr::GetSceneInst()->IsPlayingCheck(CSoundMgr::CLICK))
			CSoundMgr::GetSceneInst()->PlaySound("ButtonClick.ogg", CSoundMgr::CLICK);
	}

	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	return _int(CStatUI::Progress(fTimeDelta));
}

_int CCoolDownIcon::LateProgress(const _float & fTimeDelta)
{
	D3DXVECTOR2 vPosition = m_vPosition + *m_vMovePanel;

	m_pTransform->SetPosition(D3DXVECTOR3(vPosition.x, vPosition.y, 1));

	return _int(CStatUI::LateProgress(fTimeDelta));
}

HRESULT CCoolDownIcon::Render()
{
	return CStatUI::Render();
}

CGameObject * CCoolDownIcon::Clone(void * pArg)
{
	CCoolDownIcon*	pInstance = new CCoolDownIcon(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CCoolDownIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCoolDownIcon::Free()
{
	CStatUI::Free();
}

CCoolDownIcon * CCoolDownIcon::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CCoolDownIcon*	pInstance = new CCoolDownIcon(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CCoolDownIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
