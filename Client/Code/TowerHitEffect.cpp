#include "stdafx.h"
#include "..\Header\TowerHitEffect.h"


_USING(Client)
HRESULT CTowerHitEffect::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXVECTOR3 vPosition = *(D3DXVECTOR3*)pArg;



	m_pTransform->SetPosition(vPosition);
	


	m_iShaderPass = 5;
	m_iTexNum = 5;	
	m_vScale = { 0.1f,0.1f,1 };

	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);
	return NOERROR;
}

HRESULT CTowerHitEffect::Initialize()
{	
	return NOERROR;
}

HRESULT CTowerHitEffect::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CTowerHitEffect::AddComponent()
{
	if (FAILED(CEffect::AddComponent()))
		return E_FAIL;


	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"PARTICLE", (CComponent**)&m_pTexture)))
		return E_FAIL;
	return NOERROR;
}

CTowerHitEffect::CTowerHitEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CEffect(_m_pGraphicDev)
{
}

CTowerHitEffect::CTowerHitEffect(const CTowerHitEffect & rhs)
	: CEffect(rhs)
{
}

_int CTowerHitEffect::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta;
	if (m_fTimeDelta >= 0.5f)
	{
		m_fAlpha -= fTimeDelta*2.f;		
	}

	m_vScale.x += fTimeDelta*4.f;
	m_vScale.y += fTimeDelta*4.f;

	if (m_vScale.x >= 0.3f || m_vScale.y >= 0.3f)
		return -1;

	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);
	
	return _int();
}

_int CTowerHitEffect::LateProgress(const _float & fTimeDelta)
{
	CGameObject::ComputeZ(m_pTransform->GetPosition());

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::ALPHA_OBJECT, this)))
		return -1;
	return _int();
}

HRESULT CTowerHitEffect::Render()
{
	LPD3DXEFFECT pEffect = m_pShader->GetEffect();

	if (pEffect == nullptr)
		return E_FAIL;

	D3DXMATRIX matWorld, matView, matProj;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	matWorld = *m_pTransform->GetWorldMatrix();

	D3DXMatrixInverse(&matWorld, nullptr, &matView);

	D3DXVECTOR3 vPostion = m_pTransform->GetPosition();

	m_pTransform->SetWorldMatrix(matWorld);
	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);
	m_pTransform->SetPosition(vPostion);

	pEffect->SetMatrix("g_matWorld", m_pTransform->GetWorldMatrix());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);
	pEffect->SetVector("g_vColor", &D3DXVECTOR4(0,0,0, 0.f));
	pEffect->SetFloat("g_fAlpha", m_fAlpha);

	m_pTexture->SetTexture(pEffect, "g_Texture", (int)m_iTexNum);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(m_iShaderPass);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
	
}

CGameObject * CTowerHitEffect::Clone(void * pArg)
{
	CTowerHitEffect*	pInstance = new CTowerHitEffect(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CTowerHitEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTowerHitEffect::Free()
{
	CEffect::Free();
}

CTowerHitEffect * CTowerHitEffect::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CTowerHitEffect*	pInstance = new CTowerHitEffect(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CTowerHitEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
