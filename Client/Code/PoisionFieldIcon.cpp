#include "stdafx.h"
#include "..\Header\PoisionFieldIcon.h"


_USING(Client)

HRESULT CPoisionFieldIcon::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	m_pTransform->Scaling(45, 45, 0);
	m_pTransform->SetPosition(D3DXVECTOR3(-276, -307, 0));

	m_pSkillInfo = ((CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER"))->GetSkillInfo(CPlayer::SKILL_5);

	m_iIconNum = 4;

	return NOERROR;
}

HRESULT CPoisionFieldIcon::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CPoisionFieldIcon::AddComponent()
{
	if (FAILED(CSkillIcon::AddComponent()))
		return E_FAIL;

	return NOERROR;
}

CPoisionFieldIcon::CPoisionFieldIcon(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CSkillIcon(_m_pGraphicDev)
{
}

CPoisionFieldIcon::CPoisionFieldIcon(const CPoisionFieldIcon & rhs)
	: CSkillIcon(rhs)
{
}

_int CPoisionFieldIcon::Progress(const _float & fTimeDelta)
{
	/*if (GetAsyncKeyState('I'))
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

_int CPoisionFieldIcon::LateProgress(const _float & fTimeDelta)
{
	return _int(CSkillIcon::LateProgress(fTimeDelta));
}

HRESULT CPoisionFieldIcon::Render()
{
	if (FAILED(CSkillIcon::Render()))
		return E_FAIL;

	return NOERROR;
}

CGameObject * CPoisionFieldIcon::Clone(void * pArg)
{
	CPoisionFieldIcon*	pInstance = new CPoisionFieldIcon(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CPoisionFieldIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CPoisionFieldIcon::Free()
{
	CSkillIcon::Free();
}

CPoisionFieldIcon * CPoisionFieldIcon::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CPoisionFieldIcon*	pInstance = new CPoisionFieldIcon(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CPoisionFieldIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
