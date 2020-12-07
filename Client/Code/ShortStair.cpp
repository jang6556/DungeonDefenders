#include "stdafx.h"
#include "..\Header\ShortStair.h"

_USING(Client)

HRESULT CShortStair::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	return NOERROR;
}

HRESULT CShortStair::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CShortStair::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;	

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADER", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHORTSTAIR", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	return NOERROR;
}

CShortStair::CShortStair(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CShortStair::CShortStair(const CShortStair & rhs)
	: CGameObject(rhs)
{
}

_int CShortStair::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CShortStair::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::NONALPHA, this)))
		return -1;

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::DECAL_OBJECT, this)))
		return -1;
	
	return _int();
}

HRESULT CShortStair::Render()
{
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

CGameObject * CShortStair::Clone(void * pArg)
{
	CShortStair*	pInstance = new CShortStair(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CShortStair Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CShortStair::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pShader);
	Safe_Release(m_pMeshStatic);
	CGameObject::Free();
}

CShortStair * CShortStair::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CShortStair*	pInstance = new CShortStair(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CShortStair Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
