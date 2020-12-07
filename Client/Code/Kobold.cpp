#include "stdafx.h"
#include "..\Header\Kobold.h"


_USING(Client)
HRESULT CKobold::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	m_fScale = 0.8f;

	if (FAILED(CMonster::Initialize(pArg)))
		return E_FAIL;
}

HRESULT CKobold::Initialize_Prototype()
{
	if (FAILED(CGameObject::LoadColliderData(L"Data/Kobold.dat")))
		return E_FAIL;

	m_MonsterInfo.m_State = STATE_WALK;
	m_MonsterInfo.m_fMaxHP = 30.f;
	m_MonsterInfo.m_fCurrHP = m_MonsterInfo.m_fMaxHP;
	m_MonsterInfo.m_fDropItemNum = 3.f;
	m_MonsterInfo.m_fSpeed = 2.f;
	m_MonsterInfo.m_iDamge = 500.f;
	m_MonsterInfo.m_iExp = 40.f;
	m_MonsterInfo.m_vBloodColor = { 1,0.3f,0 };
	return NOERROR;
}

HRESULT CKobold::AddComponent()
{
	if (FAILED(CMonster::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"KOBOLD", (CComponent**)&m_pMeshDynamic)))
		return E_FAIL;

	for (int i = 0; i < m_ColliderData.size(); ++i)
	{
		CCollider* pInstance = nullptr;

		if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"COLLIDER_SPHERE", (CComponent**)&pInstance)))
			return E_FAIL;

		if (m_pMeshDynamic != nullptr)
			pInstance->SetBoneMatrix(m_pTransform->GetWorldMatrix(), &m_ColliderData[i]->matWorld, m_pMeshDynamic->GetBoneMatrix(m_ColliderData[i]->szBoneName));

		if (pInstance != nullptr)
			m_pCollider.push_back(pInstance);
	}
}



CKobold::CKobold(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	: CMonster(_m_pGraphicDev)
{
}

CKobold::CKobold(const CKobold & rhs)
	: CMonster(rhs)
{
	
}

_int CKobold::Progress(const _float & fTimeDelta)
{
	if (m_MonsterInfo.m_State == STATE_WALK)
	{
		AttackCheck(30, 13.f,false);
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

	if (m_MonsterInfo.m_State == STATE_IDLE)
	{
		if (FAILED(CMonster::RotateToTarget(fTimeDelta)))
			return -1;
	}

	if (m_MonsterInfo.m_State == STATE_WALK)
	{
		if (FAILED(CMonster::Move(fTimeDelta)))
			return -1;
	}

	if (m_MonsterInfo.m_State == STATE_RUN)
	{
		if (FAILED(CMonster::RunToTarget(fTimeDelta*4.f)))
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
		m_pMeshDynamic->SetAnimationSet(10);
	}

	if (m_MonsterInfo.m_State == STATE_HIT)
	{

		m_pMeshDynamic->SetAnimationSet(5);
	}

	if (m_MonsterInfo.m_State == STATE_WALK)
	{
		m_pMeshDynamic->SetAnimationSet(1);
	}

	if (m_MonsterInfo.m_State == STATE_RUN)
	{
		m_pMeshDynamic->SetAnimationSet(8);
	}


	m_fTimeDelta = fTimeDelta;

	CGameObject::ComputeZ(m_pTransform->GetPosition());

	return _int();
}

_int CKobold::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::NONALPHA, this)))
		return -1;

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::DEPTH_SHADOW, this)))
		return -1;

	if (m_MonsterInfo.m_State == STATE_DIE && m_pMeshDynamic->AnimationEnd(0.3f))
	{
		m_fTimeDelta = 0.f;

		m_fScale -= fTimeDelta * 0.5f;
		if (m_fScale <= 0)
		{
			return -1;
		}
		m_pTransform->Scaling(m_fScale, m_fScale, m_fScale);
	}

	

	if (m_MonsterInfo.m_State == STATE_HIT && m_pMeshDynamic->AnimationEnd(0.2f))
	{
		m_MonsterInfo.m_State = STATE_WALK;
		m_pCollider[0]->SetIsCollision(false);
		m_pMeshDynamic->SetAnimationSet(8);
	}

	if (m_MonsterInfo.m_State == STATE_ATTACK && m_pMeshDynamic->AnimationEnd(0.2f))
	{
		m_MonsterInfo.m_State = STATE_RUN;
		m_pCollider[0]->SetIsCollision(false);
		m_pMeshDynamic->SetAnimationSet(8);
	}

	if (m_MonsterInfo.m_State == STATE_RUN)
	{
		if (CMonster::ComputeTargetDistance() <= 1.f)
		{
			if (CMonster::CheckExplosion(m_pCollider[0]) == true)
			{
				if (FAILED(Dead()))
					return -1;
				CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"BOMB_EFFECT", SCENESTATIC, L"EFFECT", &*(D3DXVECTOR3*)&m_pCollider[COLLIDER_BODY]->GetWorldMatrix()->m[3][0]);

				

				return -1;
			}
		}
	}

	return _int();
}

HRESULT CKobold::Render()
{
	if (FAILED(CMonster::Render()))
		return E_FAIL;

	return NOERROR;
}

CGameObject * CKobold::Clone(void * pArg)
{
	CKobold*	pInstance = new CKobold(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CKobold Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CKobold::Free()
{
	CMonster::Free();
}

CKobold * CKobold::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CKobold*	pInstance = new CKobold(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CKobold Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
