#include "stdafx.h"
#include "..\Header\MissileTowerIcon.h"


_USING(Client)
HRESULT CMissileTowerIcon::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	m_pTransform->Scaling(45, 45, 0);
	m_pTransform->SetPosition(D3DXVECTOR3(-434, -260, 0));

	m_pSkillInfo = ((CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER"))->GetSkillInfo(CPlayer::SKILL_7);

	m_iIconNum = 6;

	return NOERROR;
}

HRESULT CMissileTowerIcon::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CMissileTowerIcon::AddComponent()
{
	if (FAILED(CSkillIcon::AddComponent()))
		return E_FAIL;

	return NOERROR;
}

CMissileTowerIcon::CMissileTowerIcon(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	: CSkillIcon(_m_pGraphicDev)
{
}

CMissileTowerIcon::CMissileTowerIcon(const CMissileTowerIcon & rhs)
	: CSkillIcon(rhs)
{
}

_int CMissileTowerIcon::Progress(const _float & fTimeDelta)
{
	return _int(CSkillIcon::Progress(fTimeDelta));
}

_int CMissileTowerIcon::LateProgress(const _float & fTimeDelta)
{
	return _int(CSkillIcon::LateProgress(fTimeDelta));
}

HRESULT CMissileTowerIcon::Render()
{
	if (FAILED(CSkillIcon::Render()))
		return E_FAIL;

	return NOERROR;
}

CGameObject * CMissileTowerIcon::Clone(void * pArg)
{
	CMissileTowerIcon*	pInstance = new CMissileTowerIcon(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CMissileTowerIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMissileTowerIcon::Free()
{
	CSkillIcon::Free();
}

CMissileTowerIcon * CMissileTowerIcon::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CMissileTowerIcon*	pInstance = new CMissileTowerIcon(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CMissileTowerIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
