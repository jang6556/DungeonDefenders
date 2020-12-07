#include "stdafx.h"
#include "..\Header\FireBulletFireEffect.h"


_USING(Client)
HRESULT CFireBulletFireEffect::Initialize(void * pArg)
{
	if (FAILED(CEffect::AddComponent()))
		return E_FAIL;

	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXVECTOR3 vPosition = *(D3DXVECTOR3*)pArg;


	m_pTransform->SetPosition(vPosition);

	return NOERROR;
}

HRESULT CFireBulletFireEffect::Initialize()
{
	return NOERROR;
}

HRESULT CFireBulletFireEffect::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CFireBulletFireEffect::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"FIREBULLET_FIRE", (CComponent**)&m_pTexture)))
		return E_FAIL;

	return NOERROR;
}

CFireBulletFireEffect::CFireBulletFireEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	: CEffect(_m_pGraphicDev)
{
}

CFireBulletFireEffect::CFireBulletFireEffect(const CFireBulletFireEffect & rhs)
	: CEffect(rhs)
{
}

_int CFireBulletFireEffect::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta *10.f;
	if (m_fTimeDelta >= 2)
		return -1;

	CGameObject::ComputeZ(m_pTransform->GetPosition());
	return _int();
	
}

_int CFireBulletFireEffect::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::ALPHA_EFFECT, this)))
		return -1;

	return _int();
}

HRESULT CFireBulletFireEffect::Render()
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
	m_pTransform->Scaling(1, 1, 1);
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

CGameObject * CFireBulletFireEffect::Clone(void * pArg)
{
	CFireBulletFireEffect*	pInstance = new CFireBulletFireEffect(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CFireBulletFireEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CFireBulletFireEffect::Free()
{
	CEffect::Free();
}

CFireBulletFireEffect * CFireBulletFireEffect::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CFireBulletFireEffect*	pInstance = new CFireBulletFireEffect(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CFireBulletFireEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
