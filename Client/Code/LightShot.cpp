#include "stdafx.h"
#include "..\Header\LightShot.h"


_USING(Client)

HRESULT CLightShot::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	m_pTransform->Scaling(45, 45, 0);
	m_pTransform->SetPosition(D3DXVECTOR3(-434, -307, 0));

	m_pSkillInfo = ((CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER"))->GetSkillInfo(CPlayer::SKILL_2);

	m_iIconNum = 1;
}

HRESULT CLightShot::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CLightShot::AddComponent()
{
	if (FAILED(CSkillIcon::AddComponent()))
		return E_FAIL;

	return NOERROR;
}

CLightShot::CLightShot(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CSkillIcon(_m_pGraphicDev)
{
}

CLightShot::CLightShot(const CLightShot & rhs)
	: CSkillIcon(rhs)
{
}

_int CLightShot::Progress(const _float & fTimeDelta)
{/*if (GetAsyncKeyState('I'))
	{
		m_pTransform->Move(0, 1, 0, 1, 1);
	}

	if (GetAsyncKeyState('K'))
	{
		m_pTransform->Move(0, -1, 0, 1, 1);
	}

	if (GetAsyncKeyState('J'))
	{
		m_pTransform->Move(-1, 0, 0, 1, 1);
	}

	if (GetAsyncKeyState('L'))
	{
		m_pTransform->Move(1, 0, 0, 1, 1);
	}

	cout << m_pTransform->GetPosition().x << " " << m_pTransform->GetPosition().y << endl;*/
	return _int(CSkillIcon::Progress(fTimeDelta));
}

_int CLightShot::LateProgress(const _float & fTimeDelta)
{
	return _int(CSkillIcon::LateProgress(fTimeDelta));
}

HRESULT CLightShot::Render()
{
	if (FAILED(CSkillIcon::Render()))
		return E_FAIL;

	return NOERROR;
}

CGameObject * CLightShot::Clone(void * pArg)
{
	CLightShot*	pInstance = new CLightShot(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CLightShot Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLightShot::Free()
{
	CSkillIcon::Free();
}

CLightShot * CLightShot::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CLightShot*	pInstance = new CLightShot(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CLightShot Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
