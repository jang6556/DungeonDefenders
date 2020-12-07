#include "stdafx.h"
#include "..\Header\StrikeTower.h"
#include "../Header/GlowBall.h"
#include "../Header/StrikeBeam.h"
_USING(Client
)
HRESULT CStrikeTower::Initialize()
{
	return NOERROR;
}

HRESULT CStrikeTower::Initialize(void * pArg)
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
	m_fRange = 10.f;
	
	m_pGlowBall = (CGlowBall*)CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"GLOWBALL", &D3DXVECTOR3(0.f, 1.f, 0.f));
	m_pStrikeBeam= (CStrikeBeam*)CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"STRIKE_BEAM", &D3DXVECTOR3(0.f, 1.f, 0.f));


	m_iMaxHp = 5100.f;
	m_iCurrHp = m_iMaxHp;

	m_fDamage = 10.f;

	return NOERROR;
}

HRESULT CStrikeTower::Initialize_Prototype()
{
	if (FAILED(CGameObject::LoadColliderData(L"Data/MissileTower.dat")))
		return E_FAIL;

	return NOERROR;
}

HRESULT CStrikeTower::AddComponent()
{
	if (FAILED(CTower::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"STRIKE_TOWER", (CComponent**)&m_pMeshDynamic)))
		return E_FAIL;

	if (FAILED(SetColliderData()))
		return E_FAIL;

	return NOERROR;
}

HRESULT CStrikeTower::FindMonster()
{
	list<CGameObject*>* pMonsterList = CGameObjectMgr::GetInstance()->GetLayer(SCENE_MAGNUS, L"MONSTER");
	if (pMonsterList == nullptr)
		return E_FAIL;

	map<float, CGameObject*> mapList;
	for (auto& iter : *pMonsterList)
	{
		if (dynamic_cast<CMonster*>(iter)->GetMonsterInfo()->m_State == CMonster::STATE_DIE)
			continue;

		list<CComponent*>* pColliderList = iter->FindComponentList(L"COLLIDER_SPHERE");

		for (auto& ColliderIter : *pColliderList)
		{
			D3DXMATRIX matColliderWorld = *dynamic_cast<CCollider*>(ColliderIter)->GetWorldMatrix();
			D3DXVECTOR3 vCollPosition;
			memcpy(&vCollPosition, &matColliderWorld.m[3][0], sizeof(D3DXVECTOR3));

			float fDistance = D3DXVec3Length(&(vCollPosition - m_pTransform->GetPosition()));

			if (fDistance > 0.f && fDistance <= m_fRange)
				mapList.emplace(fDistance, iter);
		}
	}

	if (mapList.size() == 0)
	{
		m_pTargetMonster = nullptr;
		m_TowerState = STATE_IDLE;
		return NOERROR;
	}


	m_pTargetMonster =(CMonster*)mapList.begin()->second;	
	m_pTargetMonster->AddRef();
	m_TowerState = STATE_ATTACK;
	
	return NOERROR;
}

HRESULT CStrikeTower::Roatation(const _float & fTimeDelta)
{
	if (m_pTargetMonster == nullptr)
		return NOERROR;

	D3DXVECTOR3 vDir = m_pTargetMonster->GetPosition() - m_pTransform->GetPosition();
	D3DXVec3Normalize(&vDir, &vDir);

	D3DXVECTOR3 vLook = m_pTransform->GetLook();
	D3DXVECTOR3 vRight = m_pTransform->GetRight();
	D3DXVec3Normalize(&vLook, &vLook);
	D3DXVec3Normalize(&vRight, &vRight);

	float fCos = D3DXVec3Dot(&vDir, &vLook);
	fCos = acos(fCos);

	float fCosRight = D3DXVec3Dot(&vDir, &vRight);

	if (fCosRight >= 0)
		m_pTransform->RotationAxis(D3DXVECTOR3(0, 1, 0), fCos, fTimeDelta);
	else
		m_pTransform->RotationAxis(D3DXVECTOR3(0, 1, 0), -fCos, fTimeDelta);

	return NOERROR;
}

CStrikeTower::CStrikeTower(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CTower(_m_pGraphicDev)
{
}

CStrikeTower::CStrikeTower(const CStrikeTower & rhs)
	: CTower(rhs)
{
}

_int CStrikeTower::Progress(const _float & fTimeDelta)
{
	if (m_TowerState == STATE_IDLE)
	{
		m_fCurrCoolTime += fTimeDelta;
		if (m_fCurrCoolTime >= m_fCoolTime)
		{
			if (FAILED(FindMonster()))
				return _int();
		}
	}

	if (m_TowerState == STATE_ATTACK)
	{
		if (FAILED(Roatation(fTimeDelta*2.f)))
			return -1;
	}

	if (m_TowerState == STATE_IDLE)
	{
		m_pMeshDynamic->SetAnimationSet(0);
	}

	if (m_TowerState == STATE_ATTACK)
	{
		if (!CSoundMgr::GetSceneInst()->IsPlayingCheck(CSoundMgr::STRIKE_TOWER_CHARGE) && !CSoundMgr::GetSceneInst()->IsPlayingCheck(CSoundMgr::STRIKE_TOWER))
			CSoundMgr::GetSceneInst()->PlaySound("StrikeCharge.mp3", CSoundMgr::STRIKE_TOWER_CHARGE);

		m_pMeshDynamic->SetAnimationSet(1);
	}

	m_pGlowBall->Progress(fTimeDelta);
	m_pStrikeBeam->Progress(fTimeDelta);
	return _int(CTower::Progress(fTimeDelta));
}

_int CStrikeTower::LateProgress(const _float & fTimeDelta)
{
	if (m_bAttackFlag == false && m_TowerState == STATE_ATTACK && m_pMeshDynamic->AnimationEnd(0.9f))
	{
		CPlayer* pPlayer = (CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
		if (pPlayer == nullptr)
			return -1;

		int iDamage = (m_fDamage*pPlayer->GetPlayerInfo().iAttack)*pPlayer->GetAbility(CPlayer::ABILITY_DAMAGE);
		iDamage *= -1.f;

		dynamic_cast<CMonster*>(m_pTargetMonster)->SetHp(iDamage);
		CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"DAMAGE_FONT", SCENESTATIC, L"DAMAGE", &(D3DXVECTOR4(dynamic_cast<CMonster*>(m_pTargetMonster)->GetPosition().x, dynamic_cast<CMonster*>(m_pTargetMonster)->GetPosition().y, dynamic_cast<CMonster*>(m_pTargetMonster)->GetPosition().z, iDamage)));
		
		D3DXVECTOR3 vTowerPos = m_pTransform->GetPosition();
		vTowerPos.y += 2.15f;

		D3DXVECTOR3 vMonsterPos;
		memcpy(&vMonsterPos, &((CCollider*)m_pTargetMonster->GetComponent(L"COLLIDER_SPHERE"))->GetWorldMatrix()->m[3][0], sizeof(D3DXVECTOR3));
		CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"YELLOW_EXPLOSION", SCENESTATIC, L"EFFECT", &vMonsterPos);

		CSoundMgr::GetSceneInst()->StopSound(CSoundMgr::STRIKE_TOWER_CHARGE);
		if (!CSoundMgr::GetSceneInst()->IsPlayingCheck(CSoundMgr::STRIKE_TOWER))
			CSoundMgr::GetSceneInst()->PlaySound("StrikeShot.wav", CSoundMgr::STRIKE_TOWER);

		m_pStrikeBeam->SetTarget(POS_TARGET(vTowerPos, vMonsterPos));
		
		m_bAttackFlag = true;
		Safe_Release(m_pTargetMonster);
	}

	if (m_bAttackFlag == true && m_TowerState == STATE_ATTACK && m_pMeshDynamic->AnimationEnd(0.3f))
	{
		m_TowerState = STATE_IDLE;
		m_fCurrCoolTime = 0.f;		
		m_bAttackFlag = false;
	}


	m_fTimeDelta = fTimeDelta;

	m_pGlowBall->LateProgress(fTimeDelta);
	m_pStrikeBeam->LateProgress(fTimeDelta);
	return _int(CTower::LateProgress(fTimeDelta));
}

HRESULT CStrikeTower::Render()
{
	if (FAILED(CTower::Render()))
		return E_FAIL; 

	if (m_pGlowBall != nullptr)
		m_pGlowBall->SetMatrix(m_pTransform, *m_pMeshDynamic->GetBoneMatrix(L"b_Tail1"));
		

	return NOERROR;
}

CGameObject * CStrikeTower::Clone(void * pArg)
{
	CStrikeTower*	pInstance = new CStrikeTower(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CStrikeTower Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CStrikeTower::Free()
{
	Safe_Release(m_pGlowBall);
	Safe_Release(m_pStrikeBeam);
	CTower::Free();
}

CStrikeTower * CStrikeTower::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CStrikeTower*	pInstance = new CStrikeTower(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CStrikeTower Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
