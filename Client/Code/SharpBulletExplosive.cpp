#include "stdafx.h"
#include "..\Header\SharpBulletExplosive.h"

_USING(Client)

HRESULT CSharpBulletExplosive::Initialize(void * pArg)
{
	if (FAILED(CEffect::AddComponent()))
		return E_FAIL;

	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXVECTOR3 vPosition = *(D3DXVECTOR3*)pArg;


	m_pTransform->SetPosition(vPosition);
}

HRESULT CSharpBulletExplosive::Initialize()
{
	return NOERROR;
}

HRESULT CSharpBulletExplosive::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CSharpBulletExplosive::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHARPBULLETEXPLOSIVE", (CComponent**)&m_pTexture)))
		return E_FAIL;

	return NOERROR;
}

CSharpBulletExplosive::CSharpBulletExplosive(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CEffect(_m_pGraphicDev)
{
}

CSharpBulletExplosive::CSharpBulletExplosive(const CSharpBulletExplosive & rhs)
	: CEffect(rhs)
{
}

_int CSharpBulletExplosive::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta * 20;
	if (m_fTimeDelta >= 4)
		return -1;

	CGameObject::ComputeZ(m_pTransform->GetPosition());
	return _int();
}

_int CSharpBulletExplosive::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::ALPHA_EFFECT, this)))
		return -1;

	return _int();
}

HRESULT CSharpBulletExplosive::Render()
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
	m_pTransform->Scaling(3, 3, 1);
	m_pTransform->SetPosition(vPostion);

	pEffect->SetMatrix("g_matWorld", m_pTransform->GetWorldMatrix());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);
	pEffect->SetFloat("g_fUV", 0);

	m_pTexture->SetTexture(pEffect, "g_Texture", (int)m_fTimeDelta);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(0);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
}

CGameObject * CSharpBulletExplosive::Clone(void * pArg)
{
	CSharpBulletExplosive*	pInstance = new CSharpBulletExplosive(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CSharpBulletExplosive Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CSharpBulletExplosive::Free()
{
	CEffect::Free();
}

CSharpBulletExplosive * CSharpBulletExplosive::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CSharpBulletExplosive*	pInstance = new CSharpBulletExplosive(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CSharpBulletExplosive Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
