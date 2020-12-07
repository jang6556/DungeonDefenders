#include "stdafx.h"
#include "..\Header\LavaFogEffect.h"

_USING(Client)

HRESULT CLavaFogEffect::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXMATRIX matPosition = *(D3DXMATRIX*)pArg;

	
	memcpy(&m_vPosition, &matPosition.m[3][0], sizeof(D3DXVECTOR3));
	m_pTransform->SetPosition(m_vPosition);

	m_iShaderPass = 9;

	m_vScale.x = 0.5f;
	m_vScale.y = 0.5f;

	m_vUV.x = rand() % 100 / 100.f;
	m_vUV.y = rand() % 100 / 100.f;
	return NOERROR;
}

HRESULT CLavaFogEffect::Initialize()
{
	return NOERROR;
}

HRESULT CLavaFogEffect::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CLavaFogEffect::AddComponent()
{
	if (FAILED(CEffect::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"LAVA_EFFECT", (CComponent**)&m_pTexture)))
		return E_FAIL;

	return NOERROR;
}

CLavaFogEffect::CLavaFogEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	: CEffect(_m_pGraphicDev)
{
}

CLavaFogEffect::CLavaFogEffect(const CLavaFogEffect & rhs)
	: CEffect(rhs)
{
}

_int CLavaFogEffect::Progress(const _float & fTimeDelta)
{
	int Rand = (rand() % 4);
	m_vScale += D3DXVECTOR3(fTimeDelta* 0.25f*Rand, fTimeDelta* 0.25f*Rand, 0);
	m_pTransform->Move(0, 0.5f, 0, 1, fTimeDelta);
	if (m_vScale.x >= 4.f || m_vScale.y >= 4.f)
	{
		m_vScale.x = 0.5f;
		m_vScale.y = 0.5f;
		m_pTransform->SetPosition(m_vPosition);
	}

	m_fTimeDelta += fTimeDelta * 0.25f*Rand/3.5f;
	if (m_fTimeDelta >= 1.f)
		m_fTimeDelta = 0.f;

	return _int();
}

_int CLavaFogEffect::LateProgress(const _float & fTimeDelta)
{
	CGameObject::ComputeZ(m_pTransform->GetPosition());

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::ALPHA_OBJECT, this)))
		return -1;

	return _int();
}

HRESULT CLavaFogEffect::Render()
{
	LPD3DXEFFECT pEffect = m_pShader->GetEffect();

	if (pEffect == nullptr)
		return E_FAIL;

	D3DXMATRIX matWorld, matView, matProj;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	D3DXMatrixInverse(&matWorld, nullptr, &matView);

	D3DXVECTOR3 vPostion = m_pTransform->GetPosition();

	m_pTransform->SetWorldMatrix(matWorld);
	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);
	m_pTransform->SetPosition(vPostion);

	pEffect->SetMatrix("g_matWorld", m_pTransform->GetWorldMatrix());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);

	pEffect->SetFloat("g_fU", m_vUV.x);
	pEffect->SetFloat("g_fV", m_vUV.y);
	pEffect->SetFloat("g_fAlpha", 1-m_fTimeDelta);


	m_pTexture->SetTexture(pEffect, "g_Texture", (int)0);
	m_pTexture->SetTexture(pEffect, "g_FilterTexture", (int)2);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(m_iShaderPass);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
}

CGameObject * CLavaFogEffect::Clone(void * pArg)
{
	CLavaFogEffect*	pInstance = new CLavaFogEffect(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CLavaFogEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLavaFogEffect::Free()
{
	CEffect::Free();
}

CLavaFogEffect * CLavaFogEffect::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CLavaFogEffect*	pInstance = new CLavaFogEffect(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CLavaFogEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
