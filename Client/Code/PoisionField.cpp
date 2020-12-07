#include "stdafx.h"
#include "..\Header\PoisionField.h"
#include "../Header/FogEffect.h"

_USING(Client)

HRESULT CPoisionField::Initialize()
{
	return NOERROR;
}

HRESULT CPoisionField::Initialize(void * pArg)
{
	if (FAILED(CBuildObject::Initialize()))
		return E_FAIL;

	if (FAILED(AddComponent()))
		return E_FAIL;

	if (m_ColliderData.size() != 0)
		m_pCollider->SetBoneMatrix(m_pTransform->GetWorldMatrix(), &m_ColliderData[0]->matWorld);

	D3DXVECTOR3	vPosition = *(D3DXVECTOR3*)pArg;

	m_pTransform->SetPosition(vPosition);
	m_pFogEffect =(CFogEffect*)CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"FOG_EFFECT", &vPosition);
	
	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"SUMMONDECAL", SCENESTATIC, L"DECAL", &D3DXVECTOR4(vPosition,0))))
		return E_FAIL;

	m_pDecal =(CDecal*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"DECAL", -1);

	m_fDamage = 0.1f;

	return NOERROR;
}

HRESULT CPoisionField::Initialize_Prototype()
{
	if (FAILED(CGameObject::LoadColliderData(L"Data/PresentBomb.dat")))
		return E_FAIL;

	

	return NOERROR;
}

HRESULT CPoisionField::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"COLLIDER_SPHERE", (CComponent**)&m_pCollider)))
		return E_FAIL;
}

CPoisionField::CPoisionField(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CBuildObject(_m_pGraphicDev)
{
}

CPoisionField::CPoisionField(const CPoisionField & rhs)
	:CBuildObject(rhs)
{
}

_int CPoisionField::Progress(const _float & fTimeDelta)
{
	if (-1 == m_pFogEffect->Progress(fTimeDelta))
		return -1;

	m_fEffect += fTimeDelta;
	if (m_fEffect >= 0.1f)
	{
		D3DXVECTOR3 vPosition = m_pTransform->GetPosition();
		float Randx = (float)(rand() % 200) / 100.f;
		
		vPosition.x += (float)(rand() % 200) / 100.f -1.f;
		vPosition.z += (float)(rand() % 200) / 100.f -1.f;
		vPosition.y += (float)(rand() % 50) / 100.f;
		CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"POISON_FIELD_EFFECT", SCENESTATIC, L"EFFECT", &vPosition);
		m_fEffect = 0;
	}

	m_fTimeDelta += fTimeDelta;
	if (m_fTimeDelta >= 1.f)
	{
		list<CGameObject*>*	MonsterList = (list<CGameObject*>*)CGameObjectMgr::GetInstance()->GetLayer(SCENE_MAGNUS, L"MONSTER");
		if (MonsterList == nullptr)
			return _int();

		for (auto& iter : *MonsterList)
		{
			list<CComponent*>*	pMonsterColliderList = iter->FindComponentList(L"COLLIDER_SPHERE");

			for (auto& Coll_iter : *pMonsterColliderList)
			{
				CCollider*	pMonsterCollider = (CCollider*)Coll_iter;

				if (true == m_pCollider->CheckCollision_SPHERE(pMonsterCollider))
				{
					CPlayer* pPlayer = (CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
					if (pPlayer == nullptr)
						return -1;

					int iDamage = (m_fDamage*pPlayer->GetPlayerInfo().iAttack)*pPlayer->GetAbility(CPlayer::ABILITY_DAMAGE);
					iDamage *= -1.f;


					if (FAILED(dynamic_cast<CMonster*>(iter)->SetHp(iDamage)))
						return _int();

					CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"DAMAGE_FONT", SCENESTATIC, L"DAMAGE", &(D3DXVECTOR4(m_pTransform->GetPosition(), iDamage)));

				}
			}

		}

		m_fTimeDelta = 0.f;
	}
	
	return _int();
}

_int CPoisionField::LateProgress(const _float & fTimeDelta)
{
	CGameObject::ComputeZ(m_pTransform->GetPosition());

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::ALPHA_OBJECT, this)))
		return -1;

	return _int();
}

HRESULT CPoisionField::Render()
{
	if (FAILED(CBuildObject::Render()))
		return E_FAIL;

	if (FAILED(m_pFogEffect->Render()))
		return E_FAIL;

	return NOERROR;
}

CGameObject * CPoisionField::Clone(void * pArg)
{
	CPoisionField*	pInstance = new CPoisionField(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CPoisionField Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CPoisionField::Free()
{
	Safe_Release(m_pFogEffect);
	CBuildObject::Free();
}

CPoisionField * CPoisionField::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CPoisionField*	pInstance = new CPoisionField(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CPoisionField Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
