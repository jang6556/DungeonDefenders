#include "stdafx.h"
#include "..\Header\Goblin.h"


_USING(Client)

HRESULT CGoblin::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	m_fScale = 0.08f;

	if (FAILED(CMonster::Initialize(pArg)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CGoblin::Initialize_Prototype()
{
	if (FAILED(CGameObject::LoadColliderData(L"Data/Goblin.dat")))
		return E_FAIL;

	m_MonsterInfo.m_State = STATE_WALK;
	m_MonsterInfo.m_fMaxHP = 150.f;
	m_MonsterInfo.m_fCurrHP = m_MonsterInfo.m_fMaxHP;
	m_MonsterInfo.m_fDropItemNum = 3.f;
	m_MonsterInfo.m_fSpeed = 2.f;
	m_MonsterInfo.m_iDamge = 3.f;
	m_MonsterInfo.m_iExp = 30.f;
	m_MonsterInfo.m_vBloodColor = { 0,0.7f,0.f };

	return NOERROR;
}

HRESULT CGoblin::AddComponent()
{
	if (FAILED(CMonster::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"GOBLIN", (CComponent**)&m_pMeshDynamic)))
		return E_FAIL;

	for (int i = 0; i < m_ColliderData.size(); ++i)
	{
		CCollider* pInstance = nullptr;

		switch (m_ColliderData[i]->iColliderType)
		{
		case CCollider::AABB:
			if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"COLLIDER_AABB", (CComponent**)&pInstance)))
				return E_FAIL;
			break;
		case CCollider::OBB:
			if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"COLLIDER_OBB", (CComponent**)&pInstance)))
				return E_FAIL;
			break;
		case CCollider::SPHERE:
			if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"COLLIDER_SPHERE", (CComponent**)&pInstance)))
				return E_FAIL;
			break;
		}		

		if (m_pMeshDynamic != nullptr)
			pInstance->SetBoneMatrix(m_pTransform->GetWorldMatrix(), &m_ColliderData[i]->matWorld, m_pMeshDynamic->GetBoneMatrix(m_ColliderData[i]->szBoneName));

		if (pInstance != nullptr)
			m_pCollider.push_back(pInstance);
	}

	return NOERROR;
}


CGoblin::CGoblin(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CMonster(_m_pGraphicDev)
{
}

CGoblin::CGoblin(const CGoblin & rhs)
	: CMonster(rhs)
{
	
}

_int CGoblin::Progress(const _float & fTimeDelta)
{
	m_fAttackCool += fTimeDelta;
	if (m_MonsterInfo.m_State == STATE_WALK && m_fAttackCool >= 1.f)
	{
		AttackCheck(80,2.5f);
		m_fAttackCool = 0.f;
	}

	if (m_MonsterInfo.m_fCurrHP <= 0)
	{
		if (CMonster::DropItem() == -1)
			return -1;

		if (CMonster::Dead() == -1)
			return -1;

		m_MonsterInfo.m_State = STATE_DIE;
		m_pCollider[0]->SetIsCollision(true);		
	}

	if (m_MonsterInfo.m_State == STATE_WALK)
	{		
		if (FAILED(CMonster::Move(fTimeDelta)))
			return -1;		
	}

	if (m_MonsterInfo.m_State == STATE_IDLE)
	{
		if (FAILED(CMonster::RotateToTarget(fTimeDelta)))
			return -1;
	}

	if (m_MonsterInfo.m_State == STATE_IDLE)
	{
		m_pMeshDynamic->SetAnimationSet(0);
	}

	if (m_MonsterInfo.m_State == STATE_DIE)
	{
		m_pMeshDynamic->SetAnimationSet(6);
	}

	if (m_MonsterInfo.m_State == STATE_ATTACK)
	{
		

		m_pMeshDynamic->SetAnimationSet(9);
	}

	if (m_MonsterInfo.m_State == STATE_HIT)
	{
		m_pMeshDynamic->SetAnimationSet(4);
	}

	if (m_MonsterInfo.m_State == STATE_WALK)
	{
		m_pMeshDynamic->SetAnimationSet(1);
	}

	m_fTimeDelta = fTimeDelta;

	CGameObject::ComputeZ(m_pTransform->GetPosition());

	return _int();
}

_int CGoblin::LateProgress(const _float & fTimeDelta)
{	
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::NONALPHA, this)))
		return -1;		

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::DEPTH_SHADOW, this)))
		return -1;

	if (m_MonsterInfo.m_State == STATE_DIE && m_pMeshDynamic->AnimationEnd(0.3f))
	{
		m_fTimeDelta = 0.f;

		m_fScale -= fTimeDelta * 0.05f;
		if (m_fScale <= 0)
		{
			return -1;
		}

		m_pTransform->Scaling(m_fScale, m_fScale, m_fScale);
	}
	
	if (m_MonsterInfo.m_State == STATE_ATTACK && m_pMeshDynamic->AnimationEnd(0.3f))
	{
		m_MonsterInfo.m_State = STATE_WALK;
		m_HitList.clear();
		m_pMeshDynamic->SetAnimationSet(1);
	}

	if (m_MonsterInfo.m_State == STATE_ATTACK&& m_pMeshDynamic->AnimationEnd(1.0f))
	{
		CMonster::CheckCollision_MeleeWeapon(m_pCollider[COLLIDER_WEAPON0]);
	}

	
	if (m_MonsterInfo.m_State == STATE_HIT && m_pMeshDynamic->AnimationEnd(0.2f))
	{
		m_MonsterInfo.m_State = STATE_WALK;
		m_pCollider[0]->SetIsCollision(false);
		m_pMeshDynamic->SetAnimationSet(1);
	}	

	return _int();
}

HRESULT CGoblin::Render()
{
	if (FAILED(CMonster::Render()))
		return E_FAIL;

	return NOERROR;
}

CGameObject * CGoblin::Clone(void * pArg)
{
	CGoblin*	pInstance = new CGoblin(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CGoblin Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CGoblin::Free()
{
	CMonster::Free();
}

CGoblin * CGoblin::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CGoblin*	pInstance = new CGoblin(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CGoblin Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
