#include "stdafx.h"
#include "..\Header\BuildObject.h"


_USING(Client)
HRESULT CBuildObject::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;	

	return NOERROR;
}

HRESULT CBuildObject::Initialize(void * pArg)
{
	return NOERROR;
}

HRESULT CBuildObject::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CBuildObject::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADER", (CComponent**)&m_pShader)))
		return E_FAIL;

	

	return NOERROR;
}

HRESULT CBuildObject::Render_Static()
{
	if (m_pMeshStatic != nullptr)
	{
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
	}

	return NOERROR;
}

HRESULT CBuildObject::Render_Dynamic()
{
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

CBuildObject::CBuildObject(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{

}

CBuildObject::CBuildObject(const CBuildObject & rhs)
	:CGameObject(rhs)
{

}

_int CBuildObject::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta = fTimeDelta;
	return _int();
}

_int CBuildObject::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CBuildObject::Render()
{
	if (GetAsyncKeyState('C'))
	{
		m_pCollider->Render();
	}

	if (m_pMeshStatic != nullptr)
		Render_Static();
	else if(m_pMeshDynamic != nullptr)
		Render_Dynamic();
	

	return NOERROR;
}

void CBuildObject::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pShader);
	Safe_Release(m_pMeshStatic);
	Safe_Release(m_pMeshDynamic);
	Safe_Release(m_pCollider);
	CGameObject::Free();
}
