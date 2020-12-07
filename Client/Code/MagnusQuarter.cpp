#include "stdafx.h"
#include "..\Header\MagnusQuarter.h"

_USING(Client)

HRESULT CMagnusQuarter::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	return NOERROR;
}

HRESULT CMagnusQuarter::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CMagnusQuarter::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;	

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADER", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"MAGUSQUARTER", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	

	return NOERROR;
}

CMagnusQuarter::CMagnusQuarter(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CMagnusQuarter::CMagnusQuarter(const CMagnusQuarter & rhs)
	: CGameObject(rhs)

{
}

_int CMagnusQuarter::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta*0.01f;
	if (m_fTimeDelta >= 1.f)
		m_fTimeDelta = 0.f;
	return _int();
}

_int CMagnusQuarter::LateProgress(const _float & fTimeDelta)
{
	
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::NONALPHA, this)))
		return -1;	

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::DECAL_OBJECT, this)))
		return -1;

	return _int();
}

HRESULT CMagnusQuarter::Render()
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
	pEffect->SetFloat("g_fUV_X", m_fTimeDelta);
	pEffect->SetFloat("g_fUV_Y", m_fTimeDelta);

	pEffect->Begin(nullptr, 0);
	unsigned long iSubsetNum = m_pMeshStatic->GetSubsetNum();

	for (int i = 0; i < iSubsetNum; ++i)
	{
		m_pMeshStatic->SetShaderMeshTex(pEffect, i, "g_Texture", MESHTEXTURE::MESH_DIFFUSE);
		
		pEffect->CommitChanges();

	/*	if(i==11 || i==46 || i==58)
			pEffect->BeginPass(4);
		else*/
			pEffect->BeginPass(0);

		m_pMeshStatic->Render(i);
		pEffect->EndPass();
	}
	pEffect->End();
	return NOERROR;
}

CGameObject * CMagnusQuarter::Clone(void * pArg)
{
	CMagnusQuarter*	pInstance = new CMagnusQuarter(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CMagnusQuarter Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMagnusQuarter::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pShader);
	Safe_Release(m_pMeshStatic);
	
	CGameObject::Free();
}

CMagnusQuarter * CMagnusQuarter::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CMagnusQuarter*	pInstance = new CMagnusQuarter(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CMagnusQuarter Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
