#include "stdafx.h"
#include "..\Header\FireBulletEffect.h"


_USING(Client)

HRESULT CFireBulletEffect::Initialize(void * pArg)
{
	if (FAILED(CEffect::AddComponent()))
		return E_FAIL;

	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXVECTOR3 vPosition = *(D3DXVECTOR3*)pArg;


	m_pTransform->SetPosition(vPosition); 
	
	return NOERROR;
}
HRESULT CFireBulletEffect::Initialize()
{
	return NOERROR;
}

HRESULT CFireBulletEffect::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CFireBulletEffect::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"FIREBULLETEFFECT", (CComponent**)&m_pTexture)))
		return E_FAIL;

	return NOERROR;
}

CFireBulletEffect::CFireBulletEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	: CEffect(_m_pGraphicDev)
{
}

CFireBulletEffect::CFireBulletEffect(const CFireBulletEffect & rhs)
	: CEffect(rhs)
{
}

_int CFireBulletEffect::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta * 60.f;
	if (m_fTimeDelta >= 31)
		return -1;

	

	return _int();
}

_int CFireBulletEffect::LateProgress(const _float & fTimeDelta)
{
	CGameObject::ComputeZ(m_pTransform->GetPosition());
	
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::ALPHA_EFFECT, this)))
		return -1;

	return _int();
}

HRESULT CFireBulletEffect::Render()
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

CGameObject * CFireBulletEffect::Clone(void * pArg)
{
	CFireBulletEffect*	pInstance = new CFireBulletEffect(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CFireBulletEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CFireBulletEffect::Free()
{
	CEffect::Free();
}

CFireBulletEffect * CFireBulletEffect::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CFireBulletEffect*	pInstance = new CFireBulletEffect(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CFireBulletEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

