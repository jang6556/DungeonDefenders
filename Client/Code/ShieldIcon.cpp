#include "stdafx.h"
#include "..\Header\ShieldIcon.h"


_USING(Client)

HRESULT CShieldIcon::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	m_pTransform->Scaling(45, 45, 0);
	m_pTransform->SetPosition(D3DXVECTOR3(-487, -260, 0));

	m_pSkillInfo = ((CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER"))->GetSkillInfo(CPlayer::SKILL_6);

	m_iIconNum = 5;
}

HRESULT CShieldIcon::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CShieldIcon::AddComponent()
{
	if (FAILED(CSkillIcon::AddComponent()))
		return E_FAIL;

	return NOERROR;
}

CShieldIcon::CShieldIcon(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CSkillIcon(_m_pGraphicDev)
{
}

CShieldIcon::CShieldIcon(const CShieldIcon & rhs)
	: CSkillIcon(rhs)
{
}

_int CShieldIcon::Progress(const _float & fTimeDelta)
{
	return _int(CSkillIcon::Progress(fTimeDelta));
}

_int CShieldIcon::LateProgress(const _float & fTimeDelta)
{
	return _int(CSkillIcon::LateProgress(fTimeDelta));
}

HRESULT CShieldIcon::Render()
{
	if (FAILED(CSkillIcon::Render()))
		return E_FAIL;

	return NOERROR;
}

CGameObject * CShieldIcon::Clone(void * pArg)
{
	CShieldIcon*	pInstance = new CShieldIcon(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CShieldIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CShieldIcon::Free()
{
	CSkillIcon::Free();
}

CShieldIcon * CShieldIcon::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CShieldIcon*	pInstance = new CShieldIcon(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CShieldIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
