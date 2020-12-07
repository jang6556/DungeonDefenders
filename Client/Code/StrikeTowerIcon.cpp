#include "stdafx.h"
#include "..\Header\StrikeTowerIcon.h"


_USING(Client)
HRESULT CStrikeTowerIcon::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	m_pTransform->Scaling(45, 45, 0);
	m_pTransform->SetPosition(D3DXVECTOR3(-328, -260, 0));

	m_pSkillInfo = ((CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER"))->GetSkillInfo(CPlayer::SKILL_9);

	m_iIconNum = 8;

	return NOERROR;
}

HRESULT CStrikeTowerIcon::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CStrikeTowerIcon::AddComponent()
{
	if (FAILED(CSkillIcon::AddComponent()))
		return E_FAIL;

	return NOERROR;
}

CStrikeTowerIcon::CStrikeTowerIcon(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CSkillIcon(_m_pGraphicDev)
{
}

CStrikeTowerIcon::CStrikeTowerIcon(const CStrikeTowerIcon & rhs)
	: CSkillIcon(rhs)
{
}

_int CStrikeTowerIcon::Progress(const _float & fTimeDelta)
{
	return _int(CSkillIcon::Progress(fTimeDelta));
}

_int CStrikeTowerIcon::LateProgress(const _float & fTimeDelta)
{
	return _int(CSkillIcon::LateProgress(fTimeDelta));
}

HRESULT CStrikeTowerIcon::Render()
{
	if (FAILED(CSkillIcon::Render()))
		return E_FAIL;

	return NOERROR;
}

CGameObject * CStrikeTowerIcon::Clone(void * pArg)
{
	CStrikeTowerIcon*	pInstance = new CStrikeTowerIcon(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CStrikeTowerIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CStrikeTowerIcon::Free()
{
	CSkillIcon::Free();
}

CStrikeTowerIcon * CStrikeTowerIcon::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CStrikeTowerIcon*	pInstance = new CStrikeTowerIcon(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CStrikeTowerIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
