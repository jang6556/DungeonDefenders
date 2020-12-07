#include "stdafx.h"
#include "..\Header\Tower.h"
#include "../Header/HpBarContent.h"
#include "../Header/HpBarUI.h"

_USING(Client)

HRESULT CTower::Initialize()
{
	m_TowerState = STATE_IDLE;

	return NOERROR;
}

HRESULT CTower::Initialize(void * pArg)
{
	return NOERROR;
}

HRESULT CTower::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CTower::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADER", (CComponent**)&m_pShader)))
		return E_FAIL;

	
		
	return NOERROR;
}

HRESULT CTower::AttackMonster(_float _fRange)
{
	if (_fRange < 0)
		return E_FAIL;	

	if (m_TowerState == STATE_ATTACK)
		return NOERROR;

	float fLength = _fRange;

	list<CGameObject*>*	MonsterList = (list<CGameObject*>*)CGameObjectMgr::GetInstance()->GetLayer(SCENE_MAGNUS, L"MONSTER");
	if (MonsterList == nullptr)
		return E_FAIL;
	
	CGameObject* pMonster = nullptr;

	for (auto& iter : *MonsterList)
	{
		CTransform* pTransform = (CTransform*)iter->GetComponent(L"TRANSFORM");
		if (pTransform == nullptr)
			return E_FAIL;

		float fTargetLength = D3DXVec3Length(&(pTransform->GetPosition() - m_pTransform->GetPosition()));

		if (fLength > fTargetLength)
		{
			if (dynamic_cast<CMonster*>(iter)->GetMonsterInfo()->m_State != CMonster::STATE_DIE)
			{				
				fLength = fTargetLength;
				pMonster = iter;

			}
		}
	}

	if (fLength < _fRange)
	{
		m_TowerState = STATE_ATTACK;

		CCollider* pCollider=(CCollider*)pMonster->GetComponent(L"COLLIDER_SPHERE");

		D3DXMATRIX matWorld = *pCollider->GetWorldMatrix();
	
		D3DXVECTOR3 vPosition;
		memcpy(&vPosition, &matWorld.m[3][0], sizeof(D3DXVECTOR3));

		m_vTargetPos = vPosition;
		
	}


	return NOERROR;
}

HRESULT CTower::SetPosition(void * pArg)
{
	if (pArg == nullptr || m_pTransform == nullptr)
		return E_FAIL;

	D3DXVECTOR3	vPosition = *(D3DXVECTOR3*)pArg;

	CTransform* pTransform = (CTransform*)CGameObjectMgr::GetInstance()->FindComponent(SCENESTATIC,L"PLAYER", L"TRANSFORM");

	D3DXVECTOR3 vLook = vPosition - pTransform->GetPosition();
	D3DXVec3Normalize(&vLook, &vLook);

	D3DXVECTOR3 vRight, vUp;

	D3DXVec3Cross(&vRight, &D3DXVECTOR3(0.f, 1.f, 0.f), &vLook);
	D3DXVec3Cross(&vUp, &vLook, &vRight);

	D3DXVec3Normalize(&vRight, &vRight);
	D3DXVec3Normalize(&vUp, &vUp);

	m_pTransform->SetRight(vRight);
	m_pTransform->SetUp(D3DXVECTOR3(0.f, 1.f, 0.f));
	m_pTransform->SetLook(vLook);
	m_pTransform->SetPosition(vPosition);


	return NOERROR;
}

_int CTower::RotationToMonster(const _float & fTimeDelta)
{
	D3DXVECTOR3 vDir = m_vTargetPos - m_pTransform->GetPosition();
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

	return _int();
}

HRESULT CTower::SetColliderData()
{
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

CTower::CTower(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CTower::CTower(const CTower & rhs)
	:CGameObject(rhs)
{
}

_int CTower::Progress(const _float & fTimeDelta)
{
	if (m_iCurrHp <= 0)
		return -1;
	
	return _int();
}

_int CTower::LateProgress(const _float & fTimeDelta)
{
	if (m_iCurrHp <= 0)
		return -1;


	CGameObject::ComputeZ(m_pTransform->GetPosition());

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::NONALPHA, this)))
		return -1;

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::DEPTH_SHADOW, this)))
		return -1;
	
	return _int();
}

HRESULT CTower::Render()
{
	if (GetAsyncKeyState('C'))
	{
		for (auto& iter : m_pCollider)
			iter->Render();
	}

	if (m_pMeshDynamic != nullptr)
		m_pMeshDynamic->PlayAnimation(m_fTimeDelta);

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

HRESULT CTower::RenderShadow()
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

void CTower::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pShader);	
	Safe_Release(m_pMeshDynamic);
	for (auto& iter : m_pCollider)
		Safe_Release(iter);

	m_pCollider.clear();
	CGameObject::Free();
}
