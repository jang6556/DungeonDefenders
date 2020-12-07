#include "stdafx.h"
#include "..\Header\TowerBullet.h"


_USING(Client)

bool CTowerBullet::bCheckCollision()
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
				CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"BLUE_EXPLOSION", SCENESTATIC, L"EFFECT", &m_pTransform->GetPosition());

				return true;
			}
		}

	}

	return false;
}

int CTowerBullet::Explosion()
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

			if (true == m_pColliderExplosion->CheckCollision_SPHERE(pMonsterCollider))
			{
				CPlayer* pPlayer = (CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
				float	 fDamage = m_fDamge*pPlayer->GetPlayerInfo().iAttack * pPlayer->GetAbility(CPlayer::ABILITY_DAMAGE);

				if (FAILED(dynamic_cast<CMonster*>(iter)->SetHp(-fDamage)))
					return -1;

				CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"DAMAGE_FONT", SCENESTATIC, L"DAMAGE", &(D3DXVECTOR4(m_pTransform->GetPosition(), -fDamage)));

				
			}
		}

	}

	return -1;
}

HRESULT CTowerBullet::Initialize()
{
	return NOERROR;
}

HRESULT CTowerBullet::Initialize(void * pArg)
{
	if (pArg == nullptr)
		return E_FAIL;

	m_tBulletInfo = *(TOWER_BULLET_INFO*)pArg;

	D3DXVECTOR3 vPosition = m_tBulletInfo.vPosition;
	vPosition.y += 2.25f;
	m_pTransform->SetPosition(vPosition);

	D3DXVECTOR3 vRight, vUp, vLook;

	vLook = m_tBulletInfo.vDir - vPosition;
	D3DXVec3Normalize(&vLook, &vLook);

	D3DXVec3Cross(&vRight, &D3DXVECTOR3(0.f, 1.f, 0.f), &vLook);
	D3DXVec3Cross(&vUp, &vLook, &vRight);

	D3DXVec3Normalize(&vRight, &vRight);
	D3DXVec3Normalize(&vUp, &vUp);

	m_pTransform->SetRight(vRight);
	m_pTransform->SetUp(vUp);
	m_pTransform->SetLook(vLook);
		

	return NOERROR;
}

HRESULT CTowerBullet::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CTowerBullet::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADER_TOWER_BULLET", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"COLLIDER_SPHERE", (CComponent**)&m_pCollider)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"COLLIDER_SPHERE", (CComponent**)&m_pColliderExplosion)))
		return E_FAIL;


	return NOERROR;
}

CTowerBullet::CTowerBullet(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CTowerBullet::CTowerBullet(const CTowerBullet & rhs)
	: CGameObject(rhs)
{
}

_int CTowerBullet::Progress(const _float & fTimeDelta)
{
	

	return _int();
}

_int CTowerBullet::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CTowerBullet::Render()
{
	/*if (GetAsyncKeyState('C'))
	{
		m_pCollider->Render();
	}*/

	LPD3DXEFFECT pEffect = m_pShader->GetEffect();
	if (pEffect == nullptr)
		return E_FAIL;
	D3DXMATRIX matView, matProj;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matWorld", m_pTransform->GetWorldMatrix());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);

	/*pEffect->SetFloat("g_fUV_X", m_fTimeDelta);*/
	//pEffect->SetFloat("g_fUV_Y", m_fTimeDelta);


	pEffect->Begin(nullptr, 0);
	unsigned long iSubsetNum = m_pMeshStatic->GetSubsetNum();

	for (int i = 0; i < iSubsetNum; ++i)
	{
		m_pMeshStatic->SetShaderMeshTex(pEffect, i, "g_Texture", MESHTEXTURE::MESH_DIFFUSE);

		pEffect->CommitChanges();
		pEffect->BeginPass(m_iShaderPass);
		m_pMeshStatic->Render(i);
		pEffect->EndPass();
	}
	pEffect->End();

	return NOERROR;
}

CGameObject * CTowerBullet::Clone(void * pArg)
{
	return nullptr;
}

void CTowerBullet::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pShader);
	Safe_Release(m_pMeshStatic);
	Safe_Release(m_pCollider);
	Safe_Release(m_pColliderExplosion);
	CGameObject::Free();
}
