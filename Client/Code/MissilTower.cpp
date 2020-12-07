#include "stdafx.h"
#include "..\Header\MissilTower.h"
#include "../Header/GlowBall.h"

_USING(Client)

HRESULT CMissilTower::Initialize()
{
	return NOERROR;
}

HRESULT CMissilTower::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	if (FAILED(CTower::Initialize()))
		return E_FAIL;

	if (FAILED(CTower::SetPosition(pArg)))
		return E_FAIL;	

	m_pTransform->Scaling(0.01f, 0.01f, 0.01f);

	m_fCoolTime = 3.f;
	m_fCurrCoolTime = m_fCoolTime;
	

	m_pGlowBall = (CGlowBall*)CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"GLOWBALL", &D3DXVECTOR3(0.f, -0.45f, 0.f));

	m_iMaxHp = 100.f;
	m_iCurrHp = m_iMaxHp;

	return NOERROR;
}

HRESULT CMissilTower::Initialize_Prototype()
{
	if (FAILED(CGameObject::LoadColliderData(L"Data/MissileTower.dat")))
		return E_FAIL;

	return NOERROR;
}

HRESULT CMissilTower::AddComponent()
{
	if (FAILED(CTower::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"MISSILE_TOWER", (CComponent**)&m_pMeshDynamic)))
		return E_FAIL;

	if (FAILED(SetColliderData()))
		return E_FAIL;

	return NOERROR;
}

CMissilTower::CMissilTower(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CTower(_m_pGraphicDev)
{
}

CMissilTower::CMissilTower(const CMissilTower & rhs)
	: CTower(rhs)
{
}

_int CMissilTower::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta = fTimeDelta*(m_TowerState+1);

	m_fCurrCoolTime += fTimeDelta;
	if (m_fCurrCoolTime >= m_fCoolTime)
	{
		if (FAILED(CTower::AttackMonster(18.f)))
			return _int();			
	}	

	if (m_TowerState == STATE_ATTACK)
	{
		CTower::RotationToMonster(fTimeDelta*4.f);
	}
	m_pGlowBall->Progress(fTimeDelta);
	return _int(CTower::Progress(fTimeDelta));
}

_int CMissilTower::LateProgress(const _float & fTimeDelta)
{
	if (m_TowerState == STATE_IDLE)
	{
		m_pMeshDynamic->SetAnimationSet(0);
	}

	if (m_TowerState == STATE_ATTACK)
	{
		m_pMeshDynamic->SetAnimationSet(1);
	}

	if (m_TowerState == STATE_ATTACK && m_pMeshDynamic->AnimationEnd(0.3f))
	{
		m_TowerState = STATE_IDLE;
		m_fCurrCoolTime = 0.f;
		m_bAttackFlag = false;

		m_pMeshDynamic->SetAnimationSet(0);
	}

	if (m_bAttackFlag == false &&m_TowerState == STATE_ATTACK && m_pMeshDynamic->AnimationEnd(0.9f))
	{
		CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"MISSILE_TOWER_BULLET", SCENESTATIC, L"TOWER_BULLET", &CTowerBullet::TOWER_BULLET_INFO(m_pTransform->GetPosition(), m_vTargetPos));
		
		if (!CSoundMgr::GetSceneInst()->IsPlayingCheck(CSoundMgr::MISSILE_TOWER))
			CSoundMgr::GetSceneInst()->PlaySound("MissileTower.mp3", CSoundMgr::MISSILE_TOWER);
		
		m_bAttackFlag = true;
	}
	m_pGlowBall->LateProgress(fTimeDelta);
	return _int(CTower::LateProgress(fTimeDelta));
}

HRESULT CMissilTower::Render()
{
	if (FAILED(CTower::Render()))
		return E_FAIL;

	if (m_pGlowBall != nullptr)
		m_pGlowBall->SetMatrix(m_pTransform, *m_pMeshDynamic->GetBoneMatrix(L"b_Spike4_3"));

	return NOERROR;
}

CGameObject * CMissilTower::Clone(void * pArg)
{
	CMissilTower*	pInstance = new CMissilTower(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CMissilTower Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMissilTower::Free()
{
	Safe_Release(m_pGlowBall);
	CTower::Free();
}

CMissilTower * CMissilTower::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CMissilTower*	pInstance = new CMissilTower(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CMissilTower Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
