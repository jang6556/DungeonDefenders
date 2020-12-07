#include "stdafx.h"
#include "..\Header\DarkElfArrow.h"

_USING(Client)

HRESULT CDarkElfArrow::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	POS_TARGET vPosTarget;
	vPosTarget = *(POS_TARGET*)pArg;	

	m_vDir = vPosTarget.vTarget -(vPosTarget.vPosition+D3DXVECTOR3(0.f, 1.7f, 0.5f));
	
	D3DXVec3Normalize(&m_vDir, &m_vDir);

	D3DXVECTOR3 vRight, vUp;

	D3DXVec3Cross(&vUp, &m_vDir, &D3DXVECTOR3(1, 0, 0));
	D3DXVec3Cross(&vRight, &vUp, &m_vDir);

	D3DXVec3Normalize(&vRight, &vRight);
	D3DXVec3Normalize(&vUp, &vUp);

	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	memcpy(&matWorld.m[0][0], &vRight, sizeof(D3DXVECTOR3));
	memcpy(&matWorld.m[1][0], &vUp, sizeof(D3DXVECTOR3));
	memcpy(&matWorld.m[2][0], &m_vDir, sizeof(D3DXVECTOR3));
	memcpy(&matWorld.m[3][0], &(vPosTarget.vPosition + D3DXVECTOR3(0.f, 1.7f, 0.5f)), sizeof(D3DXVECTOR3));

	m_pTransform->SetWorldMatrix(matWorld);

	m_pTransform->Scaling(0.025f, 0.025f, 0.025f);
	
	m_pTransform->RotationAxis(m_pTransform->GetUp(), D3DXToRadian(180), 1.f);	

	m_pCollider->SetBoneMatrix(m_pTransform->GetWorldMatrix(), &m_ColliderData[0]->matWorld);
	return NOERROR;
}

HRESULT CDarkElfArrow::Initialize_Prototype()
{
	if (FAILED(CGameObject::LoadColliderData(L"Data/CrossBowArrow.dat")))
		return E_FAIL;

	return NOERROR;
}

HRESULT CDarkElfArrow::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADER", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"ARROW", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"COLLIDER_SPHERE", (CComponent**)&m_pCollider)))
		return E_FAIL;

	return NOERROR;
}

bool CDarkElfArrow::CheckCollision()
{
	if (m_pCollider == nullptr)
		return false;

	


	CGameObject* pCrystal = CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"CRYSTAL");
	if (pCrystal == nullptr)
		return false;	

	
	CCollider*  pCrystalCollider = (CCollider*)pCrystal->GetComponent(L"COLLIDER_SPHERE");
	if (pCrystalCollider == nullptr)
		return false;

	if (m_pCollider->CheckCollision_SPHERE(pCrystalCollider) == true)
	{
		dynamic_cast<CCrystal*>(pCrystal)->SetDamage(-10);
		return true;
	}
	


	list<CGameObject*>*	pBuildObjectList = CGameObjectMgr::GetInstance()->GetLayer(SCENESTATIC, L"BUILD_OBJECT");
	if (pBuildObjectList != nullptr)
	{
		for (auto& iter : *pBuildObjectList)
		{	
			list<CComponent*>* ColliderList= iter->FindComponentList(L"COLLIDER_SPHERE");;
			for (auto& ColliderIter : *ColliderList)
			{
				CCollider* pTargetCollider = (CCollider*)ColliderIter;
				if (pTargetCollider == nullptr)
					return false;

				if (m_pCollider->CheckCollision_SPHERE(pTargetCollider) == true)
				{
					D3DXVECTOR3 vWeaponPosition = *(D3DXVECTOR3*)&m_pCollider->GetWorldMatrix()->m[3][0];
					D3DXVECTOR3 vTargetCPosition = *(D3DXVECTOR3*)&pTargetCollider->GetWorldMatrix()->m[3][0];

					CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"TOWER_HIT_EFFECT", SCENESTATIC, L"EFFECT", &((vWeaponPosition + vTargetCPosition)*0.5f));

					dynamic_cast<CTower*>(iter)->SetHp(-10);
					return true;
				}
			}
		}
	}

	CGameObject*	pInstance = CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
	if (pInstance == nullptr)
		return false;

	CCollider* pPlayerCollider = (CCollider*)pInstance->GetComponent(L"COLLIDER_SPHERE");
	if (pPlayerCollider == nullptr)
		return false;

	if (m_pCollider->CheckCollision_SPHERE(pPlayerCollider) == true)
	{
		dynamic_cast<CPlayer*>(pInstance)->SetHit(-10);
		return true;
	}


	return false;
}

CDarkElfArrow::CDarkElfArrow(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	: CGameObject(_m_pGraphicDev)
{
}

CDarkElfArrow::CDarkElfArrow(const CDarkElfArrow & rhs)
	: CGameObject(rhs)
{
}

_int CDarkElfArrow::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta;
	if (m_fTimeDelta >= 2.0f)
		return -1;

	m_pTransform->MoveStraight(-30.f, fTimeDelta);

	return _int();
}

_int CDarkElfArrow::LateProgress(const _float & fTimeDelta)
{
	if (CheckCollision() == true)
		return -1;

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::NONALPHA, this)))
		return -1;

	return _int();
}

HRESULT CDarkElfArrow::Render()
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

CGameObject * CDarkElfArrow::Clone(void * pArg)
{
	CDarkElfArrow*	pInstance = new CDarkElfArrow(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CDarkElfArrow Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CDarkElfArrow::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pShader);
	Safe_Release(m_pMeshStatic);
	Safe_Release(m_pCollider);
	CGameObject::Free();
}

CDarkElfArrow * CDarkElfArrow::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CDarkElfArrow*	pInstance = new CDarkElfArrow(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CDarkElfArrow Created Failed");
		Safe_Release(pInstance);
	}

	return pInstance;
}
