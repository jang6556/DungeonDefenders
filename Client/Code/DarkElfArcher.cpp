#include "stdafx.h"
#include "..\Header\DarkElfArcher.h"


_USING(Client)

HRESULT CDarkElfArcher::Initialize(void* pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	m_fScale = 0.1f;

	if (FAILED(CMonster::Initialize(pArg)))
		return E_FAIL;
		
	return NOERROR;
}

HRESULT CDarkElfArcher::Initialize_Prototype()
{
	if (FAILED(CGameObject::LoadColliderData(L"Data/DarkElfArcher.dat")))
		return E_FAIL;

	m_MonsterInfo.m_State = STATE_WALK;
	m_MonsterInfo.m_fMaxHP = 70.f;
	m_MonsterInfo.m_fCurrHP = m_MonsterInfo.m_fMaxHP;
	m_MonsterInfo.m_fDropItemNum = 3.f;
	m_MonsterInfo.m_fSpeed = 2.f;
	m_MonsterInfo.m_iExp = 30.f;
	m_MonsterInfo.m_vBloodColor = { 0.6824f,0.f,0.949f };
	return NOERROR;
}

HRESULT CDarkElfArcher::AddComponent()
{

	if (FAILED(CMonster::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"DARKELFARCHER", (CComponent**)&m_pMeshDynamic)))
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



	return NOERROR;
}

CDarkElfArcher::CDarkElfArcher(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CMonster(_m_pGraphicDev)
{
}

CDarkElfArcher::CDarkElfArcher(const CDarkElfArcher & rhs)
	: CMonster(rhs)
{
	
}

_int CDarkElfArcher::Progress(const _float & fTimeDelta)
{
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
		AttackCheck(60, 13.f);		
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
		m_pMeshDynamic->SetAnimationSet(9);
	}

	if (m_MonsterInfo.m_State == STATE_ATTACK)
	{
		m_pMeshDynamic->SetAnimationSet(11);
	}

	if (m_MonsterInfo.m_State == STATE_HIT)
	{

		m_pMeshDynamic->SetAnimationSet(7);
	}

	if (m_MonsterInfo.m_State == STATE_WALK)
	{
		if (FAILED(CMonster::Move(fTimeDelta)))
			return -1;

		m_pMeshDynamic->SetAnimationSet(1);
	}
	
	CGameObject::ComputeZ(m_pTransform->GetPosition());

	return _int();
}

_int CDarkElfArcher::LateProgress(const _float & fTimeDelta)
{
	m_fTimeDelta = fTimeDelta;

	if (m_MonsterInfo.m_State == STATE_DIE && m_pMeshDynamic->AnimationEnd(0.3f))
	{
		m_fTimeDelta = 0.f;

		m_fScale -= fTimeDelta * 0.05f;
		if (m_fScale <= 0)
			return -1;

		m_pTransform->Scaling(m_fScale, m_fScale, m_fScale);
	}

	if (m_bAttack == false && m_MonsterInfo.m_State == STATE_ATTACK && m_pMeshDynamic->GetTimeTrack() >= 0.6f)
	{
		CGameObjectMgr::GetInstance()->AddObejct(SCENE_MAGNUS, L"DARKELFARROW", SCENE_MAGNUS, L"DARKELFARROW", &POS_TARGET(m_pTransform->GetPosition(),m_vTarget));
		m_bAttack = true;
	}

	if (m_MonsterInfo.m_State == STATE_ATTACK && m_pMeshDynamic->AnimationEnd(0.3f))
	{
		m_MonsterInfo.m_State = STATE_WALK;
		m_pCollider[0]->SetIsCollision(false);
		m_pMeshDynamic->SetAnimationSet(1);
		m_bAttack = false;
	}

	if (m_MonsterInfo.m_State == STATE_HIT && m_pMeshDynamic->AnimationEnd(0.3f))
	{
		m_MonsterInfo.m_State = STATE_WALK;
		m_pCollider[0]->SetIsCollision(false);
		m_pMeshDynamic->SetAnimationSet(1);
	}

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::NONALPHA, this)))
		return -1;

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::DEPTH_SHADOW, this)))
		return -1;

	return _int();
}

HRESULT CDarkElfArcher::Render()
{
	if (FAILED(CMonster::Render()))
		return E_FAIL;

	return NOERROR;
}

CGameObject * CDarkElfArcher::Clone(void * pArg)
{
	CDarkElfArcher*	pInstance = new CDarkElfArcher(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CDarkElfArcher Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CDarkElfArcher::Free()
{		
	CMonster::Free();
}

CDarkElfArcher * CDarkElfArcher::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CDarkElfArcher*	pInstance = new CDarkElfArcher(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CDarkElfArcher Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
