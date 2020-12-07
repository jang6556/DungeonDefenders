#include "stdafx.h"
#include "..\Header\DamageUpIcon.h"


_USING(Client)
HRESULT CDamageUpIcon::Initialize()
{
	

	return NOERROR;
}

HRESULT CDamageUpIcon::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	if (pArg == nullptr)
		return E_FAIL;

	m_vMovePanel = (D3DXVECTOR2*)pArg;

	m_iPassNum = 7;
	m_iTexNum = 1;

	m_vScale = { 64,64 };

	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);
	m_vPosition = { -135,30 };
	m_pTransform->SetPosition(D3DXVECTOR3(m_vPosition.x, m_vPosition.y, 1));

	return NOERROR;
}

HRESULT CDamageUpIcon::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CDamageUpIcon::AddComponent()
{
	if (FAILED(CStatUI::AddComponent()))
		return E_FAIL;

	return NOERROR;
}

CDamageUpIcon::CDamageUpIcon(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CStatUI(_m_pGraphicDev)
{
}

CDamageUpIcon::CDamageUpIcon(const CDamageUpIcon & rhs)
	: CStatUI(rhs)
{
}

_int CDamageUpIcon::Progress(const _float & fTimeDelta)
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
			pPlayer->UpAbility(CPlayer::ABILITY_DAMAGE);
		m_bClickIcon = false;

		if (!CSoundMgr::GetSceneInst()->IsPlayingCheck(CSoundMgr::CLICK))
			CSoundMgr::GetSceneInst()->PlaySound("ButtonClick.ogg", CSoundMgr::CLICK);
	}

	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	return _int(CStatUI::Progress(fTimeDelta));
}

_int CDamageUpIcon::LateProgress(const _float & fTimeDelta)
{
	D3DXVECTOR2 vPosition = m_vPosition + *m_vMovePanel;

	m_pTransform->SetPosition(D3DXVECTOR3(vPosition.x, vPosition.y, 1));

	return _int(CStatUI::LateProgress(fTimeDelta));
}

HRESULT CDamageUpIcon::Render()
{
	return CStatUI::Render();
}

CGameObject * CDamageUpIcon::Clone(void * pArg)
{
	CDamageUpIcon*	pInstance = new CDamageUpIcon(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CDamageUpIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CDamageUpIcon::Free()
{
	CStatUI::Free();
}

CDamageUpIcon * CDamageUpIcon::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CDamageUpIcon*	pInstance = new CDamageUpIcon(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CDamageUpIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
