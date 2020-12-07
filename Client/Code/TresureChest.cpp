#include "stdafx.h"
#include "..\Header\TresureChest.h"

_USING(Client)

HRESULT CTresureChest::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;	

	return NOERROR;
}

HRESULT CTresureChest::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXMATRIX matWorld = *(D3DXMATRIX*)pArg;

	m_pTransform->SetWorldMatrix(matWorld);

	m_pTransform->RotationAxis(m_pTransform->GetUp(), D3DXToRadian(180),1.f);

	m_pCollider->SetBoneMatrix(m_pTransform->GetWorldMatrix(), &m_ColliderData[0]->matWorld);
	return NOERROR;
}

HRESULT CTresureChest::Initialize_Prototype()
{
	if (FAILED(CGameObject::LoadColliderData(L"Data/TresureChest.dat")))
		return E_FAIL;

	return NOERROR;
}

HRESULT CTresureChest::AddComponent()
{
	if(FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADER", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRESURECHEST", (CComponent**)&m_pMeshDynamic)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"COLLIDER_AABB", (CComponent**)&m_pCollider, L"COLLIDER_BODY")))
		return E_FAIL;
	


	return NOERROR;
}

CTresureChest::CTresureChest(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{

}

CTresureChest::CTresureChest(const CTresureChest & rhs)
	: CGameObject(rhs)
{

}

_int CTresureChest::Progress(const _float & fTimeDelta)
{

	CCollider*	pPlayerCollider = (CCollider*)CGameObjectMgr::GetInstance()->FindComponent(SCENESTATIC, L"PLAYER", L"COLLIDER_AABB");

	if (m_pCollider->GetIsCollision() == false && m_pCollider->CheckCollision_AABB(pPlayerCollider))
	{
		m_pCollider->SetIsCollision(true);
		m_IsOpen = true;
		m_pMeshDynamic->SetAnimationSet(0);

		for (int i = 0; i < rand()%3+3; ++i)
			if (FAILED(CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"MANA_TOKEN", SCENESTATIC, L"ITEM", &(m_pTransform->GetPosition() + D3DXVECTOR3(0,0.5f,0)))))
				return -1;
	}

	if (m_IsOpen && m_pMeshDynamic->AnimationEnd(0.1f))
 		m_IsOpen = false;	

	return _int();
}

_int CTresureChest::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::NONALPHA, this)))
		return -1;

	if (m_IsOpen == true)
		m_fTimeDelta = fTimeDelta;
	else
		m_fTimeDelta = 0.f;

	return _int();
}

HRESULT CTresureChest::Render()
{
	if (GetAsyncKeyState('C'))
	{		
		m_pCollider->Render();		
	}

	LPD3DXEFFECT pEffect = m_pShader->GetEffect();
	if (pEffect == nullptr)
		return E_FAIL;
	D3DXMATRIX  matView, matProj;
	
	m_pMeshDynamic->PlayAnimation(m_fTimeDelta);

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

CGameObject * CTresureChest::Clone(void * pArg)
{
	CTresureChest*	pInstance = new CTresureChest(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CTresureChest Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTresureChest::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pShader);
	Safe_Release(m_pMeshDynamic);
	Safe_Release(m_pCollider);	

	CGameObject::Free();
}

CTresureChest * CTresureChest::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CTresureChest*	pInstance = new CTresureChest(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CTresureChest Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
