#include "stdafx.h"
#include "..\Header\Item.h"


_USING(Client)

HRESULT CItem::Initialize()
{
	return NOERROR;
}

HRESULT CItem::Initialize(void * pArg)
{
	D3DXVECTOR3 vPosition = *(D3DXVECTOR3*)pArg;

	if (m_pTransform != nullptr)
		m_pTransform->SetPosition(vPosition);

	if (m_pNaviMesh != nullptr)
		m_pNaviMesh->SetIndex(vPosition);

	
	return NOERROR;
}

HRESULT CItem::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CItem::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADER", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"NAVIMESH", (CComponent**)&m_pNaviMesh)))
		return E_FAIL;
	
	return NOERROR;
}

CItem::CItem(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CItem::CItem(const CItem & rhs)
	: CGameObject(rhs)
{
}

_int CItem::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CItem::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CItem::Render()
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
		pEffect->BeginPass(m_iShaderPass);
		m_pMeshStatic->Render(i);
		pEffect->EndPass();
	}
	pEffect->End();

	return NOERROR;

}

void CItem::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pShader);
	Safe_Release(m_pMeshStatic);
	Safe_Release(m_pNaviMesh);
	CGameObject::Free();
}

