#include "stdafx.h"
#include "..\Header\LightningTowerIcon.h"


_USING(Client)

HRESULT CLightningTowerIcon::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	m_pTransform->Scaling(45, 45, 0);
	m_pTransform->SetPosition(D3DXVECTOR3(-381, -260, 0));

	m_pSkillInfo = ((CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER"))->GetSkillInfo(CPlayer::SKILL_8);

	m_iIconNum = 7;

	return NOERROR;
}

HRESULT CLightningTowerIcon::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CLightningTowerIcon::AddComponent()
{
	if (FAILED(CSkillIcon::AddComponent()))
		return E_FAIL;

	return NOERROR;
}

CLightningTowerIcon::CLightningTowerIcon(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	: CSkillIcon(_m_pGraphicDev)
{
}

CLightningTowerIcon::CLightningTowerIcon(const CLightningTowerIcon & rhs)
	: CSkillIcon(rhs)
{
}

_int CLightningTowerIcon::Progress(const _float & fTimeDelta)
{
	return _int(CSkillIcon::Progress(fTimeDelta));
}

_int CLightningTowerIcon::LateProgress(const _float & fTimeDelta)
{
	return _int(CSkillIcon::LateProgress(fTimeDelta));
}

HRESULT CLightningTowerIcon::Render()
{
	if (FAILED(CSkillIcon::Render()))
		return E_FAIL;

	return NOERROR;
}

CGameObject * CLightningTowerIcon::Clone(void * pArg)
{
	CLightningTowerIcon*	pInstance = new CLightningTowerIcon(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CLightningTowerIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLightningTowerIcon::Free()
{
	CSkillIcon::Free();
}

CLightningTowerIcon * CLightningTowerIcon::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CLightningTowerIcon*	pInstance = new CLightningTowerIcon(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CLightningTowerIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
