#include "stdafx.h"
#include "..\Header\Demon.h"

_USING(Client)

HRESULT CDemon::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	m_pTransform->Scaling(0.5f, 0.5f, 0.5f);

	return NOERROR;
}

HRESULT CDemon::Initialize_Prototype()
{
	if (FAILED(CGameObject::LoadColliderData(L"Data/Demon.dat")))
		return E_FAIL;
		

	return NOERROR;
}

HRESULT CDemon::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADER", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"DEMON", (CComponent**)&m_pMeshDynamic)))
		return E_FAIL;
	
	for (int i = 0; i < m_ColliderData.size(); ++i)
	{
		CCollider* pInstance = nullptr;

		
		if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"COLLIDER_SPHERE", (CComponent**)&pInstance, L"COLLIDER_BODY")))
			return E_FAIL;		

		if (m_pMeshDynamic != nullptr)
			pInstance->SetBoneMatrix(m_pTransform->GetWorldMatrix(),&m_ColliderData[i]->matWorld, m_pMeshDynamic->GetBoneMatrix(m_ColliderData[i]->szBoneName));

		if (pInstance != nullptr)
			m_pCollider.push_back(pInstance);		
	}
	


	return NOERROR;
}

CDemon::CDemon(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CDemon::CDemon(const CDemon & rhs)
	:CGameObject(rhs)
{
}

_int CDemon::Progress(const _float & fTimeDelta)
{
	

	if (m_State == STATE_IDLE)
	{
		m_pMeshDynamic->SetAnimationSet(0);
	}

	if (m_State == STATE_HIT)
	{
		m_pMeshDynamic->SetAnimationSet(7);
	}

	if (m_pMeshDynamic != nullptr)
		m_pMeshDynamic->PlayAnimation(fTimeDelta);

	CGameObject::ComputeZ(m_pTransform->GetPosition());

	return _int();
}

_int CDemon::LateProgress(const _float & fTimeDelta)
{
	if (m_State != STATE_HIT &&m_pCollider[0]->GetIsCollision() == true)
	{
		m_State = STATE_HIT;
		m_pMeshDynamic->SetAnimationSet(7);
	}

	if (m_State == STATE_HIT && m_pMeshDynamic->AnimationEnd(0.3f))
	{
		m_State = STATE_IDLE;
		m_pCollider[0]->SetIsCollision(false);	
		m_pMeshDynamic->SetAnimationSet(0);
	}

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::ALPHA_OBJECT, this)))
		return -1;

	return _int();
}

HRESULT CDemon::Render()
{
	if (GetAsyncKeyState('C'))
	{
		for(auto& iter : m_pCollider)
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

CGameObject * CDemon::Clone(void * pArg)
{
	CDemon*	pInstance = new CDemon(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CDemon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CDemon::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pShader);
	Safe_Release(m_pMeshDynamic);
	
	for (int i = 0; i < m_pCollider.size(); ++i)
	{
		Safe_Release(m_pCollider[i]);
	}
	

	m_pCollider.clear();

	CGameObject::Free();
}

CDemon * CDemon::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CDemon*	pInstance = new CDemon(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CDemon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
