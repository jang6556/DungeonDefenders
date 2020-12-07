#include "stdafx.h"
#include "..\Header\Monster.h"
#include "../Header/MonsterHpBar.h"

_USING(Client)


HRESULT CMonster::Initialize(void * pArg)
{
	m_pTransform->Scaling(m_fScale, m_fScale, m_fScale);
	D3DXVECTOR3 vPostion = *(D3DXVECTOR3*)pArg;
	m_pTransform->SetPosition(vPostion);

	D3DXVECTOR3 vDir = -m_pTransform->GetPosition();
	D3DXVec3Normalize(&vDir, &vDir);

	D3DXVECTOR3 vLook = m_pTransform->GetLook();
	D3DXVECTOR3 vRight = m_pTransform->GetRight();
	D3DXVec3Normalize(&vLook, &vLook);
	D3DXVec3Normalize(&vRight, &vRight);

	float fCos = D3DXVec3Dot(&vDir, &vLook);
	fCos = acos(fCos);

	float fCosRight = D3DXVec3Dot(&vDir, &vRight);


	if (fCosRight >= 0)
		m_pTransform->RotationAxis(m_pTransform->GetUp(), fCos, 1.f);
	else
		m_pTransform->RotationAxis(m_pTransform->GetUp(), -fCos, 1.f);


	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"MONSTER_HP_BAR", SCENESTATIC, L"MONSTER_UI", this)))
		return E_FAIL;

	m_pMonsterHpBar = (CMonsterHpBar*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"MONSTER_UI", -1);

	return NOERROR;
}

HRESULT CMonster::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CMonster::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADER", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"NAVIMESH", (CComponent**)&m_pNaviMesh)))
		return E_FAIL;
	

	return NOERROR;
}

HRESULT CMonster::AttackCheck(float fDegree, float fRange, bool bTargetPlayer)
{
	if (m_MonsterInfo.m_State == STATE_HIT || m_MonsterInfo.m_State == STATE_DIE)
		return NOERROR;

	CGameObject* pCrystal = CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"CRYSTAL");
	if (pCrystal == nullptr)
		return E_FAIL;

	list<CComponent*>* pCrystalCollider = pCrystal->FindComponentList(L"COLLIDER_SPHERE");

	for (auto& iter : *pCrystalCollider)
	{
		D3DXMATRIX pCollider = *dynamic_cast<CCollider*>(iter)->GetWorldMatrix();
		D3DXVECTOR3 vPosition;
		memcpy(&vPosition, &pCollider.m[3][0], sizeof(D3DXVECTOR3));

		if (D3DXVec3Length(&(vPosition - m_pTransform->GetPosition())) <= fRange+1.f)
		{
			m_MonsterInfo.m_State = STATE_IDLE;
			m_vTarget = vPosition;
			return NOERROR;
		}
	}	
	bool bFlag = false;

	list<CGameObject*>*	pBuildObjectList = CGameObjectMgr::GetInstance()->GetLayer(SCENESTATIC, L"BUILD_OBJECT");
	if (pBuildObjectList != nullptr)
	{
		float fLength = FLT_MAX;

		for (auto& iter : *pBuildObjectList)
		{
			list<CComponent*>* pTowerCollider = iter->FindComponentList(L"COLLIDER_SPHERE");

			for (auto& iterCollider : *pTowerCollider)
			{
				D3DXMATRIX pCollider = *dynamic_cast<CCollider*>(iterCollider)->GetWorldMatrix();
				D3DXVECTOR3 vPosition;
				memcpy(&vPosition, &pCollider.m[3][0], sizeof(D3DXVECTOR3));

				float fCurrLength = D3DXVec3Length(&(vPosition - m_pTransform->GetPosition()));

				if (fLength < fCurrLength)
					continue;

				if (fCurrLength > fRange)
					continue;

				D3DXVECTOR3 vDir = vPosition - m_pTransform->GetPosition();
				D3DXVec3Normalize(&vDir, &vDir);

				D3DXVECTOR3 vLook;

				vLook = m_pTransform->GetLook();				
				D3DXVec3Normalize(&vLook, &vLook);

				float fCos_Look = acos(D3DXVec3Dot(&vLook, &vDir));

				if (fCos_Look < D3DXToRadian(fDegree))
					continue;

				if (fLength > fCurrLength)
				{
					fLength = fCurrLength;
					m_MonsterInfo.m_State = STATE_IDLE;
					m_vTarget = vPosition;
					bFlag = true;
				}
			}			
		}
	}

	if (bTargetPlayer == false)
		return NOERROR;

	if (bFlag == false)
	{
		CGameObject* pPlayer = CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
		if (pPlayer == nullptr)
			return E_FAIL;

		list<CComponent*>* pPlayerCollider = pPlayer->FindComponentList(L"COLLIDER_SPHERE");

		for (auto& iter : *pPlayerCollider)
		{
			D3DXMATRIX pCollider = *dynamic_cast<CCollider*>(iter)->GetWorldMatrix();
			D3DXVECTOR3 vPosition;
			memcpy(&vPosition, &pCollider.m[3][0], sizeof(D3DXVECTOR3));

			if (D3DXVec3Length(&(vPosition - m_pTransform->GetPosition())) <= fRange)
			{
				m_MonsterInfo.m_State = STATE_IDLE;
				m_vTarget = vPosition;
				return NOERROR;
			}
		}			
	}

	return NOERROR;
}

HRESULT CMonster::RotateToTarget(const _float & fTimeDelta)
{

	D3DXVECTOR3 vTargetPos = m_vTarget;
	D3DXVECTOR3 vMonsterPos = m_pTransform->GetPosition();

	vTargetPos.y = 0;
	vMonsterPos.y = 0;

	D3DXVECTOR3 vDir = vTargetPos - vMonsterPos;
	D3DXVec3Normalize(&vDir, &vDir);

	D3DXVECTOR3 vLook = m_pTransform->GetLook();
	D3DXVECTOR3 vRight = m_pTransform->GetRight();
	D3DXVec3Normalize(&vLook, &vLook);
	D3DXVec3Normalize(&vRight, &vRight);

	float fCos = D3DXVec3Dot(&vDir, &vLook);
	if (fCos > 0.9f)
	{
		m_MonsterInfo.m_State = STATE_ATTACK;
	}

	fCos = acos(fCos);

	float fCosRight = D3DXVec3Dot(&vDir, &vRight);


	if (fCosRight >= 0)
		m_pTransform->RotationAxis(m_pTransform->GetUp(), fCos, fTimeDelta*6.f);
	else
		m_pTransform->RotationAxis(m_pTransform->GetUp(), -fCos, fTimeDelta*6.f);

	return NOERROR;
}
 
HRESULT CMonster::RunToTarget(const _float & fTimeDelta)
{
	if (m_MonsterInfo.m_State != STATE_RUN)
		return NOERROR;

	D3DXVECTOR3 vTargetPos = m_vTarget;
	vTargetPos.y = 0.f;
	float fHeight = m_pNaviMesh->GetHeight(vTargetPos);
	vTargetPos.y = fHeight;

	D3DXVECTOR3 vDir = vTargetPos - m_pTransform->GetPosition();
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


	m_pTransform->Move(vDir.x, vDir.y, vDir.z, m_MonsterInfo.m_fSpeed, fTimeDelta);

	return NOERROR;
}

float CMonster::ComputeTargetDistance()
{
	D3DXVECTOR3 vColliderPos;
	D3DXMATRIX matCollider =*m_pCollider[COLLIDER_BODY]->GetWorldMatrix();

	memcpy(&vColliderPos, &matCollider.m[3][0], sizeof(D3DXVECTOR3));



	return D3DXVec3Length(&(m_vTarget-vColliderPos));
}

HRESULT CMonster::Move(const float fTimeDelta)
{
	if (m_MonsterInfo.m_State != STATE_WALK)
		return NOERROR;

	D3DXVECTOR3 vDir = m_pNaviMesh->GetPosition(m_Path.front()) - m_pTransform->GetPosition();
	float fLength = D3DXVec3Length(&vDir);
	if (fLength <= 0.1f && m_Path.size() != 1)
		m_Path.pop_front();

	D3DXVec3Normalize(&vDir, &vDir);

	m_pTransform->Move(vDir.x, vDir.y, vDir.z, m_MonsterInfo.m_fSpeed, fTimeDelta);

	D3DXVECTOR3 vLook = m_pTransform->GetLook();
	D3DXVECTOR3 vRight = m_pTransform->GetRight();
	D3DXVec3Normalize(&vLook, &vLook);
	D3DXVec3Normalize(&vRight, &vRight);

	float fCos = D3DXVec3Dot(&vDir, &vLook);
	fCos = acos(fCos);

	float fCosRight = D3DXVec3Dot(&vDir, &vRight);

	if (fCosRight >= 0)
		m_pTransform->RotationAxis(m_pTransform->GetUp(), fCos, fTimeDelta*6.f);
	else
		m_pTransform->RotationAxis(m_pTransform->GetUp(), -fCos, fTimeDelta*6.f);

	return NOERROR;
}

HRESULT CMonster::Dead()
{
	if (m_MonsterInfo.m_State != STATE_DIE)
	{
		CMonsterController* pInstance = (CMonsterController*)CGameObjectMgr::GetInstance()->FindGameObject(SCENE_MAGNUS, L"CONTROLLER");
		if (pInstance == nullptr)
			return E_FAIL;

		if (FAILED(pInstance->KillMonsterNum()))
			return E_FAIL;

		CPlayer* pPlayer = (CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
		if (pPlayer == nullptr)
			return E_FAIL;

		if (FAILED(pPlayer->AddExp(m_MonsterInfo.m_iExp)))
			return E_FAIL;

		
	}

	return NOERROR;
}

_int CMonster::DropItem()
{
	if (m_MonsterInfo.m_State != STATE_DIE)
	{
		for (int i = 0; i < m_MonsterInfo.m_fDropItemNum; ++i)
			if (FAILED(CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"MANA_TOKEN", SCENESTATIC, L"ITEM", &(m_pTransform->GetPosition() + D3DXVECTOR3(0, 1, 0)))))
				return -1;
	}

	return 0;
}

bool CMonster::CheckCollision_MeleeWeapon(CCollider * pCollider)
{
	if (pCollider == nullptr || pCollider->GetColliderType() != CCollider::OBB)
		return false;

	bool bCollision = false;

	
	CGameObject* pCrystal = CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"CRYSTAL");
	if (pCrystal == nullptr)
		return false;

	bool bCrystalCheck = false;
	for (auto& iterCheck : m_HitList)
	{
		if (iterCheck == pCrystal)
		{
			bCrystalCheck = true;
			break;
		}
	}

	if (bCrystalCheck == false)
	{
		CCollider*  pCrystalCollider = (CCollider*)pCrystal->GetComponent(L"COLLIDER_AABB");
		if (pCrystalCollider == nullptr)
			return false;

		if (pCollider->CheckCollision_OBB(pCrystalCollider) == true)
		{
			dynamic_cast<CCrystal*>(pCrystal)->SetDamage(-m_MonsterInfo.m_iDamge);
			m_HitList.push_back(pCrystal);
		}
	}



	list<CGameObject*>*	pBuildObjectList = CGameObjectMgr::GetInstance()->GetLayer(SCENESTATIC, L"BUILD_OBJECT");
	if (pBuildObjectList != nullptr)
	{
		for (auto& iter : *pBuildObjectList)
		{
			bool bCheckHit = false;

			for (auto& iterCheck : m_HitList)
			{
				if (iterCheck == iter)
				{
					bCheckHit = true;
					break;
				}
			}			

			if (bCheckHit == true)
				continue;

			CCollider* pTargetCollider = (CCollider*)iter->GetComponent(L"COLLIDER_OBB");
			if (pTargetCollider == nullptr)
				return false;

			bool bCheck = false;
			
			bCheck = pCollider->CheckCollision_OBB(pTargetCollider);			

			if (bCheck == true)
			{
				bCollision = true;

				D3DXVECTOR3 vWeaponPosition = *(D3DXVECTOR3*)&pCollider->GetWorldMatrix()->m[3][0];
				D3DXVECTOR3 vTargetCPosition = *(D3DXVECTOR3*)&pTargetCollider->GetWorldMatrix()->m[3][0];

				CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"TOWER_HIT_EFFECT", SCENESTATIC, L"EFFECT", &((vWeaponPosition+ vTargetCPosition)*0.5f));

				dynamic_cast<CTower*>(iter)->SetHp(-m_MonsterInfo.m_iDamge);
				m_HitList.push_back(iter);
			}
		}
	}

	CGameObject*	pInstance = CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
	if (pInstance == nullptr)
		return false;

	CCollider* pTargetCollider = (CCollider*)pInstance->GetComponent(L"COLLIDER_AABB");
	if (pTargetCollider == nullptr)
		return false;

	bool bCheck = false;
	
	bCheck = pCollider->CheckCollision_OBB(pTargetCollider);	

	if (bCheck == true)
	{
		for (auto& iter : m_HitList)
		{
			if (iter == pInstance)
				return false;
		}
		bCollision = true;
		dynamic_cast<CPlayer*>(pInstance)->SetHit(-m_MonsterInfo.m_iDamge);
		m_HitList.push_back(pInstance);
	}

	return bCollision;
}

bool CMonster::CheckExplosion(CCollider * pCollider)
{
	if (pCollider == nullptr || pCollider->GetColliderType() != CCollider::SPHERE)
		return false;	

	list<CGameObject*>*	pBuildObjectList = CGameObjectMgr::GetInstance()->GetLayer(SCENESTATIC, L"BUILD_OBJECT");
	if (pBuildObjectList != nullptr)
	{
		for (auto& iter : *pBuildObjectList)
		{
			list<CComponent*>*	pColliderList = iter->FindComponentList(L"COLLIDER_SPHERE");
			if (pColliderList == nullptr)
				return false;

			for (auto& Collider_iter : *pColliderList)
			{
				if (pCollider->CheckCollision_SPHERE((CCollider*)Collider_iter) == true)
				{
					dynamic_cast<CTower*>(iter)->SetHp(-m_MonsterInfo.m_iDamge);					
					break;
				}
			}
		}
	}

	return true;
}

bool CMonster::CheckCollision(CCollider * pCollider, CCollider::COLLIDER eType)
{
	if (pCollider == nullptr)
		return false;
	
	bool bCollision = false;

	list<CGameObject*>*	pBuildObjectList = CGameObjectMgr::GetInstance()->GetLayer(SCENESTATIC, L"BUILD_OBJECT");
	if (pBuildObjectList != nullptr)
	{
		for (auto& iter : *pBuildObjectList)
		{	
			bool bCheckHit = false;

			for (auto& iterCheck : m_HitList)
			{
				if (iterCheck == iter)
				{
					bCheckHit = true;
					break;					
				}
			}

			if (bCheckHit == true)
				continue;

			CCollider* pTargetCollider = (CCollider*)iter->GetComponent(L"COLLIDER_OBB");
			if (pTargetCollider == nullptr)
				return false;

			bool bCheck = false;

			switch (eType)
			{
			case CCollider::AABB:
				bCheck = pCollider->CheckCollision_AABB(pTargetCollider);
				break;
			case CCollider::OBB:
				bCheck = pCollider->CheckCollision_OBB(pTargetCollider);
				break;
			case CCollider::SPHERE:
				bCheck = pCollider->CheckCollision_SPHERE(pTargetCollider);
				break;
			}

			if (bCheck == true)
			{
				bCollision = true;

				dynamic_cast<CTower*>(iter)->SetHp(-m_MonsterInfo.m_iDamge);
				m_HitList.push_back(iter);				
			}
		}
	}

	CGameObject*	pInstance = CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
	if (pInstance == nullptr)
		return false;

	CCollider* pTargetCollider =(CCollider*)pInstance->GetComponent(L"COLLIDER_AABB");
	if (pTargetCollider == nullptr)
		return false;

	bool bCheck = false;

	switch (eType)
	{
	case CCollider::AABB:
		bCheck = pCollider->CheckCollision_AABB(pTargetCollider);
		break;
	case CCollider::OBB:
		bCheck = pCollider->CheckCollision_OBB(pTargetCollider);
		break;
	case CCollider::SPHERE:
		bCheck = pCollider->CheckCollision_SPHERE(pTargetCollider);
		break;	
	}
	
	if (bCheck == true)
	{
		for (auto& iter : m_HitList)
		{
			if (iter == pInstance)
				return false;
		}
		bCollision = true;
		//dynamic_cast<CTower*>(pInstance)->SetHp(-m_MonsterInfo.m_iDamge);
		m_HitList.push_back(pInstance);
	}

	return bCollision;
}

CMonster::CMonster(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CMonster::CMonster(const CMonster & rhs)
	: CGameObject(rhs)
{
	memcpy(&m_MonsterInfo, &rhs.m_MonsterInfo, sizeof(tagMonsterInfo));
}

_int CMonster::Progress(const _float & fTimeDelta)
{
	

	return _int();
}

_int CMonster::LateProgress(const _float & fTimeDelta)
{

	return _int();
}

HRESULT CMonster::Render()
{
	if (m_pMeshDynamic != nullptr)
		m_pMeshDynamic->PlayAnimation(m_fTimeDelta);

	if (GetAsyncKeyState('C'))
	{
		for (auto& iter : m_pCollider)
			iter->Render();
	}

	LPD3DXEFFECT pEffect = m_pShader->GetEffect();
	if (pEffect == nullptr)
		return E_FAIL;
	D3DXMATRIX  matView, matProj;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matWorld", m_pTransform->GetWorldMatrix());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);

	pEffect->Begin(nullptr, 0);
	for (int j = 0; j < 1; ++j)
	{
		if (FAILED(m_pMeshDynamic->UpdateSkinnedMesh(j)))
			break;

		for (int i = 0; i < m_pMeshDynamic->GetMaterialNum(j); ++i)
		{
			if (FAILED(m_pMeshDynamic->SetShaderMeshTex(pEffect, j, i, "g_Texture", MESHTEXTURE::MESH_DIFFUSE)))
				break;

			pEffect->CommitChanges();
			pEffect->BeginPass(0);


			m_pMeshDynamic->Render(j, i);
			pEffect->EndPass();

		}
	}
	pEffect->End();

	return NOERROR;

}

HRESULT CMonster::RenderShadow()
{
	LPD3DXEFFECT pEffect = m_pShader->GetEffect();
	if (pEffect == nullptr)
		return E_FAIL;
	D3DXMATRIX  matView, matProj;

	D3DXVECTOR3 vLightPosition, vLightDirection, vLightUp;

	if (FAILED(CLightMgr::GetInstance()->GetDirectionalLight(CManageMent::GetInstance()->GetCurrSceneID(), &vLightPosition, &vLightDirection, &vLightUp)))
		return E_FAIL;

	D3DXMatrixIdentity(&matView);

	D3DXMatrixLookAtLH(&matView, &vLightPosition, &vLightDirection, &vLightUp);
	//D3DXMatrixInverse(&matView, nullptr, &matView);

	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matWorld", m_pTransform->GetWorldMatrix());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);

	pEffect->Begin(nullptr, 0);
	for (int j = 0; j < 1; ++j)
	{
		if (FAILED(m_pMeshDynamic->UpdateSkinnedMesh(j)))
			break;

		for (int i = 0; i < m_pMeshDynamic->GetMaterialNum(j); ++i)
		{
			if (FAILED(m_pMeshDynamic->SetShaderMeshTex(pEffect, j, i, "g_Texture", MESHTEXTURE::MESH_DIFFUSE)))
				break;

			pEffect->CommitChanges();
			pEffect->BeginPass(7);


			m_pMeshDynamic->Render(j, i);
			pEffect->EndPass();

		}
	}
	pEffect->End();

	return NOERROR;
}

HRESULT CMonster::SetHp(float _fInput)
{
	if (m_pCollider.front()->GetIsCollision() == true)
		return E_FAIL;

	m_MonsterInfo.m_fCurrHP += _fInput;
	
	CSoundMgr::GetSceneInst()->PlaySound("hit.wav", CSoundMgr::BLOOD);

	CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"BLOODEFFECT", SCENESTATIC, L"EFFECT", &POS_TARGET(*(D3DXVECTOR3*)&m_pCollider[COLLIDER_BODY]->GetWorldMatrix()->m[3][0], m_MonsterInfo.m_vBloodColor));
  
   if (_fInput <= -m_MonsterInfo.m_fMaxHP * 0.3f)
   {
	   m_MonsterInfo.m_State = STATE_HIT;
   }


   m_pMonsterHpBar->SetRender();

   return NOERROR;
}

CGameObject * CMonster::Clone(void * pArg)
{
	return nullptr;
}

void CMonster::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pShader);
	Safe_Release(m_pMeshDynamic);
	Safe_Release(m_pNaviMesh);

	for (int i = 0; i < m_pCollider.size(); ++i)
	{
		Safe_Release(m_pCollider[i]);
	}

	m_pCollider.clear();
	
	if(m_pMonsterHpBar!=nullptr)
		m_pMonsterHpBar->SetIsDie(true);

	CGameObject::Free();
}
