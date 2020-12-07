#include "stdafx.h"
#include "..\Header\LightningTower.h"
#include "../Header/GlowBall.h"
#include "../Header/LightningBolt.h"
_USING(Client)

HRESULT CLightningTower::Initialize()
{
	return NOERROR;
}

HRESULT CLightningTower::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	if (FAILED(CTower::Initialize()))
		return E_FAIL;

	if (FAILED(CTower::SetPosition(pArg)))
		return E_FAIL;

	m_pTransform->Scaling(0.01f, 0.01f, 0.01f);

	m_fCoolTime = 0.3f;
	m_fCurrCoolTime = m_fCoolTime;
	
	m_iMaxHp = 100.f;
	m_iCurrHp = m_iMaxHp;


	m_vecLightningBolt.push_back((CLightningBolt*)CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"LIGHTNING_BOLT", &D3DXVECTOR3(0, 0, 0)));
	m_vecLightningBolt.push_back((CLightningBolt*)CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"LIGHTNING_BOLT", &D3DXVECTOR3(0, 0, 0)));
	
	m_pGlowBall = (CGlowBall*)CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"GLOWBALL", &D3DXVECTOR3(0.f, 0.75f, 0.f));	

	m_fDamage = 0.2f;

	return NOERROR;
}

HRESULT CLightningTower::Initialize_Prototype()
{
	if (FAILED(CGameObject::LoadColliderData(L"Data/MissileTower.dat")))
		return E_FAIL;

	return NOERROR;
}

HRESULT CLightningTower::AddComponent()
{
	if (FAILED(CTower::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"LIGHTNIG_TOWER", (CComponent**)&m_pMeshDynamic)))
		return E_FAIL;

	if (FAILED(SetColliderData()))
		return E_FAIL;

	return NOERROR;
}

HRESULT CLightningTower::AttackChainLightning()
{
	vector<CGameObject*> TargetList;

	for (size_t i = 0; i < m_iTargetNum; ++i)
	{
		CGameObject* pInstance = nullptr;

		if (TargetList.size() == 0)
			FindEnemy(m_pTransform->GetPosition(),&TargetList, &pInstance, 10);
		else
			FindEnemy(dynamic_cast<CTransform*>(TargetList.back()->GetComponent(L"TRANSFORM"))->GetPosition(), &TargetList, &pInstance, 10);

		if (pInstance == nullptr)
			break;

		TargetList.push_back(pInstance);
	}

	m_TowerState = STATE_IDLE;

	for (auto& iter : m_vecLightningBolt)
		iter->OffRender();
	
	int iSize = TargetList.size();
	
	for (int i=0;i<iSize;++i)
	{
		CPlayer* pPlayer = (CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
		if (pPlayer == nullptr)
			return -1;

		int iDamage = (m_fDamage*pPlayer->GetPlayerInfo().iAttack)*pPlayer->GetAbility(CPlayer::ABILITY_DAMAGE);
		iDamage *= -1.f;

		dynamic_cast<CMonster*>(TargetList[i])->SetHp(iDamage);
				
		CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"DAMAGE_FONT", SCENESTATIC, L"DAMAGE", &(D3DXVECTOR4(dynamic_cast<CMonster*>(TargetList[i])->GetPosition().x+rand()%2, dynamic_cast<CMonster*>(TargetList[i])->GetPosition().y+1.5f, dynamic_cast<CMonster*>(TargetList[i])->GetPosition().z + rand() % 2, iDamage)));
		
		if (i <= 0)
		{
			D3DXVECTOR3 vTowerPos = m_pTransform->GetPosition();
			vTowerPos.y += 2.15f;

			

			D3DXVECTOR3 vMonsterPos;
			memcpy(&vMonsterPos, &((CCollider*)TargetList[i]->GetComponent(L"COLLIDER_SPHERE"))->GetWorldMatrix()->m[3][0], sizeof(D3DXVECTOR3));
			
			
			m_vecLightningBolt[i]->SetTarget(POS_TARGET(vTowerPos, vMonsterPos));
		}
		else
		{
			D3DXVECTOR3 vTowerPos;
			memcpy(&vTowerPos, &((CCollider*)TargetList[i-1]->GetComponent(L"COLLIDER_SPHERE"))->GetWorldMatrix()->m[3][0], sizeof(D3DXVECTOR3));
			

			D3DXVECTOR3 vMonsterPos;
			memcpy(&vMonsterPos, &((CCollider*)TargetList[i]->GetComponent(L"COLLIDER_SPHERE"))->GetWorldMatrix()->m[3][0], sizeof(D3DXVECTOR3));
			

			m_vecLightningBolt[i]->SetTarget(POS_TARGET(vTowerPos, vMonsterPos));
		}
		


		m_TowerState = STATE_ATTACK;
	}




	return NOERROR;
}

bool CLightningTower::FindEnemy(D3DXVECTOR3 _vPosition, vector<CGameObject*>* _TargetList, CGameObject** pOut, float _fRange)
{

	list<CGameObject*>* pMonsterList = CGameObjectMgr::GetInstance()->GetLayer(SCENE_MAGNUS, L"MONSTER");
	if (pMonsterList == nullptr)
		return false;

	map<float, CGameObject*> mapList;
	for (auto& iter : *pMonsterList)
	{
		if (dynamic_cast<CMonster*>(iter)->GetMonsterInfo()->m_State == CMonster::STATE_DIE)
			continue;

		list<CComponent*>* pColliderList = iter->FindComponentList(L"COLLIDER_SPHERE");
		
		for (auto& ColliderIter : *pColliderList)
		{
			D3DXMATRIX matColliderWorld= *dynamic_cast<CCollider*>(ColliderIter)->GetWorldMatrix();
			D3DXVECTOR3 vCollPosition;
			memcpy(&vCollPosition, &matColliderWorld.m[3][0], sizeof(D3DXVECTOR3));

			float fDistance = D3DXVec3Length(&(vCollPosition - _vPosition));

			if(fDistance > 0.f && fDistance<=_fRange)
				mapList.emplace(fDistance, iter);
		}		
	}

	if (mapList.size() == 0)
	{
		*pOut = nullptr;
		return false;
	}

	for (auto& iter = mapList.begin(); iter!= mapList.end();++iter)
	{
		bool bFlag = false;
		
		for (auto& check : *_TargetList)
		{
			if ((*iter).second == check)
			{
				bFlag = true;
				break;
			}
		}

		if (bFlag == false)
		{
			*pOut = (*iter).second;
			break;
		}
	}


	
	return true;
}

CLightningTower::CLightningTower(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CTower(_m_pGraphicDev)
{
}

CLightningTower::CLightningTower(const CLightningTower & rhs)
	: CTower(rhs)
{
}

_int CLightningTower::Progress(const _float & fTimeDelta)
{
	
	m_fCurrCoolTime += fTimeDelta;
	if (m_fCurrCoolTime >= m_fCoolTime)
	{
		if (FAILED(AttackChainLightning()))
			return _int();

		m_fCurrCoolTime = 0.f;
	}
	m_pGlowBall->Progress(fTimeDelta);

	for (auto& iter : m_vecLightningBolt)
		iter->Progress(fTimeDelta);

	return _int(CTower::Progress(fTimeDelta));
}

_int CLightningTower::LateProgress(const _float & fTimeDelta)
{
	if (m_TowerState == STATE_IDLE)
	{
		m_pMeshDynamic->SetAnimationSet(0);
	}

	if (m_TowerState == STATE_ATTACK)
	{
		m_fEffectCoolTime += fTimeDelta;
		if (m_fEffectCoolTime >= 0.25f)
		{
			D3DXVECTOR3 vEffectPosition = m_pTransform->GetPosition();
			vEffectPosition.y += 2.15f;

			CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"LIGHTNING_EFFECT_SPHERE", SCENESTATIC, L"EFFECT", &vEffectPosition);
			CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"LIGHTNING_EFFECT_BOLT", SCENESTATIC, L"EFFECT", &vEffectPosition);
			m_fEffectCoolTime = 0.f;
		}

		if (!CSoundMgr::GetSceneInst()->IsPlayingCheck(CSoundMgr::LIGHTNING_TOWER))
			CSoundMgr::GetSceneInst()->PlaySound("LightnigTower.wav", CSoundMgr::LIGHTNING_TOWER);
		m_pMeshDynamic->SetAnimationSet(1);
	}

	m_fTimeDelta = fTimeDelta / (float)(1 + m_TowerState);

	m_pGlowBall->LateProgress(fTimeDelta);

	for (auto& iter : m_vecLightningBolt)
		iter->LateProgress(fTimeDelta);

	return _int(CTower::LateProgress(fTimeDelta));
}

HRESULT CLightningTower::Render()
{
	if (FAILED(CTower::Render()))
		return E_FAIL;

	if(m_pGlowBall!=nullptr)
		m_pGlowBall->SetMatrix(m_pTransform, *m_pMeshDynamic->GetBoneMatrix(L"b_Tail1"));


	return NOERROR;
}

CGameObject * CLightningTower::Clone(void * pArg)
{
	CLightningTower*	pInstance = new CLightningTower(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CLightningTower Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLightningTower::Free()
{
	Safe_Release(m_pGlowBall);
	for (auto& iter : m_vecLightningBolt)
		Safe_Release(iter);

	m_vecLightningBolt.clear();
	CTower::Free();
}

CLightningTower * CLightningTower::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CLightningTower*	pInstance = new CLightningTower(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CLightningTower Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
