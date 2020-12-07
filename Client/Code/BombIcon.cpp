#include "stdafx.h"
#include "..\Header\BombIcon.h"


_USING(Client)

HRESULT CBombIcon::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	m_pTransform->Scaling(45, 45, 0);
	m_pTransform->SetPosition(D3DXVECTOR3(-328, -307, 0));

	m_pSkillInfo = ((CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER"))->GetSkillInfo(CPlayer::SKILL_4);

	m_iIconNum = 3;

	return NOERROR;
}

HRESULT CBombIcon::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CBombIcon::AddComponent()
{
	if (FAILED(CSkillIcon::AddComponent()))
		return E_FAIL;

	return NOERROR;
}

CBombIcon::CBombIcon(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CSkillIcon(_m_pGraphicDev)
{
}

CBombIcon::CBombIcon(const CBombIcon & rhs)
	: CSkillIcon(rhs)
{
}

_int CBombIcon::Progress(const _float & fTimeDelta)
{
	return _int(CSkillIcon::Progress(fTimeDelta));
}

_int CBombIcon::LateProgress(const _float & fTimeDelta)
{
	return _int(CSkillIcon::LateProgress(fTimeDelta));
}

HRESULT CBombIcon::Render()
{
	if (FAILED(CSkillIcon::Render()))
		return E_FAIL;

	return NOERROR;
}

CGameObject * CBombIcon::Clone(void * pArg)
{
	CBombIcon*	pInstance = new CBombIcon(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CBombIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBombIcon::Free()
{
	CSkillIcon::Free();
}

CBombIcon * CBombIcon::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CBombIcon*	pInstance = new CBombIcon(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CBombIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
