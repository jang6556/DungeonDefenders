#include "stdafx.h"
#include "..\Header\LavaEffect.h"


_USING(Client)
HRESULT CLavaEffect::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXMATRIX matPosition = *(D3DXMATRIX*)pArg;

	D3DXVECTOR3 vPosition;
	memcpy(&vPosition, &matPosition.m[3][0], sizeof(D3DXVECTOR3));
	m_pTransform->SetPosition(vPosition);

	m_iShaderPass = 9;

	m_vScale.x = 2.f;
	m_vScale.y = 2.f;
	return NOERROR;
}

HRESULT CLavaEffect::Initialize()
{
	return NOERROR;
}

HRESULT CLavaEffect::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CLavaEffect::AddComponent()
{
	if (FAILED(CEffect::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"LAVA_EFFECT", (CComponent**)&m_pTexture)))
		return E_FAIL;

	return NOERROR;
}

CLavaEffect::CLavaEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	: CEffect(_m_pGraphicDev)
{
}

CLavaEffect::CLavaEffect(const CLavaEffect & rhs)
	: CEffect(rhs)
{
}

_int CLavaEffect::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta * 0.1f;
	if (m_fTimeDelta >= 1.f)
		m_fTimeDelta = 0.f;
	return _int();
}

_int CLavaEffect::LateProgress(const _float & fTimeDelta)
{
	CGameObject::ComputeZ(m_pTransform->GetPosition());

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::ALPHA_OBJECT, this)))
		return -1;

	return _int();
}

HRESULT CLavaEffect::Render()
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

	pEffect->SetFloat("g_fU", 0);
	pEffect->SetFloat("g_fV", m_fTimeDelta);
	pEffect->SetFloat("g_fAlpha", 1.f);

	m_pTexture->SetTexture(pEffect, "g_Texture", (int)0);
	m_pTexture->SetTexture(pEffect, "g_FilterTexture", (int)1);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(m_iShaderPass);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
}

CGameObject * CLavaEffect::Clone(void * pArg)
{
	CLavaEffect*	pInstance = new CLavaEffect(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CLavaEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLavaEffect::Free()
{
	CEffect::Free();
}

CLavaEffect * CLavaEffect::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CLavaEffect*	pInstance = new CLavaEffect(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CLavaEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
