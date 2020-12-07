#include "stdafx.h"
#include "..\Header\ShotGun.h"


_USING(Client)

HRESULT CShotGun::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	m_pTransform->Scaling(45, 45, 0);
	m_pTransform->SetPosition(D3DXVECTOR3(-487, -307, 0));

	m_pSkillInfo =((CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER"))->GetSkillInfo(CPlayer::SKILL_1);

	m_iIconNum = 0;
}

HRESULT CShotGun::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CShotGun::AddComponent()
{
	if (FAILED(CSkillIcon::AddComponent()))
		return E_FAIL;

	return NOERROR;
}

CShotGun::CShotGun(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CSkillIcon(_m_pGraphicDev)
{
}

CShotGun::CShotGun(const CShotGun & rhs)
	: CSkillIcon(rhs)
{
}

_int CShotGun::Progress(const _float & fTimeDelta)
{
	

	return _int(CSkillIcon::Progress(fTimeDelta));
}

_int CShotGun::LateProgress(const _float & fTimeDelta)
{


	return _int(CSkillIcon::LateProgress(fTimeDelta));
}

HRESULT CShotGun::Render()
{
	if (FAILED(CSkillIcon::Render()))
		return E_FAIL;

	return NOERROR;
}

CGameObject * CShotGun::Clone(void * pArg)
{
	CShotGun*	pInstance = new CShotGun(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CShotGun Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CShotGun::Free()
{
	CSkillIcon::Free();
}

CShotGun * CShotGun::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CShotGun*	pInstance = new CShotGun(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CShotGun Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
