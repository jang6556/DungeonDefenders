#include "stdafx.h"
#include "..\Header\PresentBomb.h"
#include "../Header/Decal.h"

_USING(Client)
HRESULT CPresentBomb::Initialize()
{
	return NOERROR;
}

HRESULT CPresentBomb::Initialize(void * pArg)
{
	if (FAILED(CBuildObject::Initialize()))
		return E_FAIL;

	if (FAILED(AddComponent()))
		return E_FAIL;

	if (m_ColliderData.size() != 0)
		m_pCollider->SetBoneMatrix(m_pTransform->GetWorldMatrix(), &m_ColliderData[0]->matWorld);

	D3DXVECTOR3	vPosition = *(D3DXVECTOR3*)pArg;

	m_pTransform->SetPosition(vPosition);
	m_pTransform->Scaling(0.005f, 0.005f, 0.005f);

	if (FAILED(CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"SUMMONDECAL", SCENESTATIC, L"DECAL", &D3DXVECTOR4(vPosition, 1))))
		return E_FAIL;

	m_pDecal = (CDecal*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"DECAL", -1);

	m_fDamage = 3.f;
	return NOERROR;
}

HRESULT CPresentBomb::Initialize_Prototype()
{
	if (FAILED(CGameObject::LoadColliderData(L"Data/PresentBomb.dat")))
		return E_FAIL;

	return NOERROR;
}

HRESULT CPresentBomb::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"PRESENT_BOMB", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"COLLIDER_SPHERE", (CComponent**)&m_pCollider)))
		return E_FAIL;	

	return NOERROR;
}

CPresentBomb::CPresentBomb(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CBuildObject(_m_pGraphicDev)
{

}

CPresentBomb::CPresentBomb(const CPresentBomb & rhs)
	: CBuildObject(rhs)
{

}

_int CPresentBomb::Progress(const _float & fTimeDelta)
{
	m_pTransform->RotationAxis(m_pTransform->GetUp(), D3DXToRadian(90), fTimeDelta);


	m_fTimer += fTimeDelta;
	if (m_fTimer >= 3.f)
	{
		list<CGameObject*>*	MonsterList = (list<CGameObject*>*)CGameObjectMgr::GetInstance()->GetLayer(SCENE_MAGNUS, L"MONSTER");
		if (MonsterList == nullptr)
			return _int();

		for (auto& iter : *MonsterList)
		{
			CCollider*	pMonsterCollider = (CCollider*)iter->GetComponent(L"COLLIDER_SPHERE");

			if (true == m_pCollider->CheckCollision_SPHERE(pMonsterCollider))
			{
				CPlayer* pPlayer = (CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
				if (pPlayer == nullptr)
					return -1;

				int iDamage = (m_fDamage*pPlayer->GetPlayerInfo().iAttack)*pPlayer->GetAbility(CPlayer::ABILITY_DAMAGE);
				iDamage*=-1.f;

				if (FAILED(dynamic_cast<CMonster*>(iter)->SetHp(iDamage)))
					return _int();

				CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"DAMAGE_FONT", SCENESTATIC, L"DAMAGE", &(D3DXVECTOR4(m_pTransform->GetPosition(), iDamage)));
				
			}
		}
		CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"BOMB_EFFECT", SCENESTATIC, L"EFFECT", &m_pTransform->GetPosition());
		
		if (!CSoundMgr::GetSceneInst()->IsPlayingCheck(CSoundMgr::BOMB))
			CSoundMgr::GetSceneInst()->PlaySound("Explosive.wav", CSoundMgr::BOMB);

		m_pDecal->SetRelease();

		return -1;
	}


	return _int();
}

_int CPresentBomb::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::NONALPHA, this)))
		return -1;

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::DEPTH_SHADOW, this)))
		return -1;

	return _int();
}

HRESULT CPresentBomb::Render()
{
	if (FAILED(CBuildObject::Render()))
		return E_FAIL;

	return NOERROR;
}

HRESULT CPresentBomb::RenderShadow()
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

CGameObject * CPresentBomb::Clone(void * pArg)
{
	CPresentBomb*	pInstance = new CPresentBomb(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CPresentBomb Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CPresentBomb::Free()
{
	CBuildObject::Free();
}

CPresentBomb * CPresentBomb::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CPresentBomb*	pInstance = new CPresentBomb(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CPresentBomb Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
