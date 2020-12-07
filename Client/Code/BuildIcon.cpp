#include "stdafx.h"
#include "..\Header\BuildIcon.h"


_USING(Client)

HRESULT CBuildIcon::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	m_pTransform->Scaling(45, 45, 0);
	m_pTransform->SetPosition(D3DXVECTOR3(-381, -307, 0));

	m_pSkillInfo = ((CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER"))->GetSkillInfo(CPlayer::SKILL_3);

	m_iIconNum = 2;

	return NOERROR;
}

HRESULT CBuildIcon::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CBuildIcon::AddComponent()
{
	if (FAILED(CSkillIcon::AddComponent()))
		return E_FAIL;

	return NOERROR;
}

CBuildIcon::CBuildIcon(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CSkillIcon(_m_pGraphicDev)
{
}

CBuildIcon::CBuildIcon(const CBuildIcon & rhs)
	: CSkillIcon(rhs)
{
}

_int CBuildIcon::Progress(const _float & fTimeDelta)
{
	
	return _int(CSkillIcon::Progress(fTimeDelta));
}

_int CBuildIcon::LateProgress(const _float & fTimeDelta)
{
	return _int(CSkillIcon::LateProgress(fTimeDelta));
}

HRESULT CBuildIcon::Render()
{
	if (FAILED(CSkillIcon::Render()))
		return E_FAIL;

	return NOERROR;
}

CGameObject * CBuildIcon::Clone(void * pArg)
{
	CBuildIcon*	pInstance = new CBuildIcon(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CBuildIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBuildIcon::Free()
{
	CSkillIcon::Free();
}

CBuildIcon * CBuildIcon::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CBuildIcon*	pInstance = new CBuildIcon(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CBuildIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
