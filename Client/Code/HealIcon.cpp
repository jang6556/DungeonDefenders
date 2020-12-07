#include "stdafx.h"
#include "..\Header\HealIcon.h"


_USING(Client)

HRESULT CHealIcon::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	m_pTransform->Scaling(45, 45, 0);
	m_pTransform->SetPosition(D3DXVECTOR3(-276, -260, 0));

	m_pSkillInfo = ((CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER"))->GetSkillInfo(CPlayer::SKILL_10);

	m_iIconNum = 9;

	return NOERROR;
}

HRESULT CHealIcon::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CHealIcon::AddComponent()
{
	if (FAILED(CSkillIcon::AddComponent()))
		return E_FAIL;

	return NOERROR;
}

CHealIcon::CHealIcon(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	: CSkillIcon(_m_pGraphicDev)
{
}

CHealIcon::CHealIcon(const CHealIcon & rhs)
	: CSkillIcon(rhs)
{
}

_int CHealIcon::Progress(const _float & fTimeDelta)
{
	return _int(CSkillIcon::Progress(fTimeDelta));
}

_int CHealIcon::LateProgress(const _float & fTimeDelta)
{
	return _int(CSkillIcon::LateProgress(fTimeDelta));
}

HRESULT CHealIcon::Render()
{
	if (FAILED(CSkillIcon::Render()))
		return E_FAIL;

	return NOERROR;
}

CGameObject * CHealIcon::Clone(void * pArg)
{
	CHealIcon*	pInstance = new CHealIcon(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CHealIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CHealIcon::Free()
{
	CSkillIcon::Free();
}

CHealIcon * CHealIcon::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CHealIcon*	pInstance = new CHealIcon(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CHealIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
