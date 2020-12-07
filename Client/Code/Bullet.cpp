#include "stdafx.h"
#include "..\Header\Bullet.h"

_USING(Client)

HRESULT CBullet::Initialize()
{
	m_pBowTransform = (CTransform*)CGameObjectMgr::GetInstance()->FindComponent(SCENESTATIC, L"CROSSBOW", L"TRANSFORM");
	m_pPlayerBone = (CMeshDynamic*)CGameObjectMgr::GetInstance()->FindComponent(SCENESTATIC, L"PLAYER", L"HUNTRESS");
	m_pPlayerWorld = (CTransform*)CGameObjectMgr::GetInstance()->FindComponent(SCENESTATIC, L"PLAYER", L"TRANSFORM");


	matWorld = *m_pBowTransform->GetWorldMatrix() *(*m_pPlayerBone->GetBoneMatrix(L"b_WristR")) * (*m_pPlayerWorld->GetWorldMatrix());

	D3DXVECTOR3 vPosition;
	memcpy(&vPosition, &matWorld.m[3][0], sizeof(D3DXVECTOR3));
	m_pTransform->SetPosition(vPosition);


	D3DXMATRIX matProj, matView;
	D3DXVECTOR3 vDir;

	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);

	D3DVIEWPORT9 ViewPort;
	ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));
	m_pGraphicDev->GetViewport(&ViewPort);

	D3DXVECTOR3 vMouse = D3DXVECTOR3(iWINCX / 2.f, iWINCY / 2.f, 1000.f);

	m_pGraphicDev->GetViewport(&ViewPort);

	vMouse.x = vMouse.x / (ViewPort.Width / 2.f) - 1.f;
	vMouse.y = vMouse.y / (ViewPort.Height / -2.f) + 1.f;	

	D3DXMatrixInverse(&matProj, nullptr, &matProj);
	D3DXVec3TransformCoord(&vDir, &vMouse, &matProj);

	D3DXMatrixInverse(&matView, nullptr, &matView);
	D3DXVec3TransformNormal(&vDir, &vDir, &matView);

	D3DXVec3Normalize(&vDir, &vDir);

	D3DXVECTOR3 vUp, vLook;

	D3DXVec3Cross(&vLook, &vDir, &D3DXVECTOR3(0, 1, 0));
	D3DXVec3Cross(&vUp, &vLook, &vDir);

	D3DXVec3Normalize(&vUp, &vUp);
	D3DXVec3Normalize(&vLook, &vLook);

	m_vRight = vDir;	

	m_pTransform->SetRight(vDir);
	m_pTransform->SetUp(vUp);
	m_pTransform->SetLook(vLook);
	

	m_pCollider->SetBoneMatrix(m_pTransform->GetWorldMatrix(), &m_ColliderData[0]->matWorld);
	return NOERROR;
}

HRESULT CBullet::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CBullet::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADER", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"COLLIDER_SPHERE", (CComponent**)&m_pCollider)))
		return E_FAIL;

	return NOERROR;
}

_int CBullet::CheckCollision(const _tchar* szEffectTag)
{
	list<CGameObject*>*	MonsterList = (list<CGameObject*>*)CGameObjectMgr::GetInstance()->GetLayer(SCENE_MAGNUS, L"MONSTER");
	if (MonsterList == nullptr)
		return _int();

	for (auto& iter : *MonsterList)
	{
		list<CComponent*>*	pMonsterColliderList = iter->FindComponentList(L"COLLIDER_SPHERE");
		if (pMonsterColliderList == nullptr)
			continue;
		for (auto& Coll_iter : *pMonsterColliderList)
		{
			CCollider*	pMonsterCollider = (CCollider*)Coll_iter;

			if (true == m_pCollider->CheckCollision_SPHERE(pMonsterCollider))
			{
				CPlayer* pPlayer =(CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
				if (pPlayer == nullptr)
					return -1;

				int iDamage = (m_fDamage*pPlayer->GetPlayerInfo().iAttack)*pPlayer->GetAbility(CPlayer::ABILITY_DAMAGE);

				if (FAILED(dynamic_cast<CMonster*>(iter)->SetHp(-iDamage)))
					return -1;

				CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, szEffectTag, SCENESTATIC, L"EFFECT", &(m_pTransform->GetPosition()));

				CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"DAMAGE_FONT", SCENESTATIC, L"DAMAGE", &(D3DXVECTOR4( m_pTransform->GetPosition(),-iDamage)));

				return -1;
			}
		}

	}

	return _int();
}

CBullet::CBullet(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CBullet::CBullet(const CBullet & rhs)
	: CGameObject(rhs)
{
}

_int CBullet::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CBullet::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CBullet::Render()
{
	if (GetAsyncKeyState('C'))
	{
		m_pCollider->Render();
	}

	LPD3DXEFFECT pEffect = m_pShader->GetEffect();
	if (pEffect == nullptr)
		return E_FAIL;
	D3DXMATRIX matView, matProj;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matWorld", m_pTransform->GetWorldMatrix());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);

	pEffect->Begin(nullptr, 0);
	unsigned long iSubsetNum = m_pMeshStatic->GetSubsetNum();

	for (int i = 0; i < iSubsetNum; ++i)
	{
		m_pMeshStatic->SetShaderMeshTex(pEffect, i, "g_Texture", MESHTEXTURE::MESH_DIFFUSE);

		pEffect->CommitChanges();
		pEffect->BeginPass(0);
		m_pMeshStatic->Render(i);
		pEffect->EndPass();
	}
	pEffect->End();
	return NOERROR;
}

void CBullet::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pShader);
	Safe_Release(m_pMeshStatic);
	Safe_Release(m_pCollider);
	CGameObject::Free();
}
