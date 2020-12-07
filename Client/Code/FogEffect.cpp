#include "stdafx.h"
#include "..\Header\FogEffect.h"

_USING(Client)

HRESULT CFogEffect::Initialize(void * pArg)
{
	if (FAILED(CEffect::AddComponent()))
		return E_FAIL;

	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXVECTOR3 vPosition = *(D3DXVECTOR3*)pArg;
	m_pTransform->SetPosition(vPosition);

	return NOERROR;
}

HRESULT CFogEffect::Initialize()
{
	return NOERROR;
}

HRESULT CFogEffect::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CFogEffect::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"FOG_EFFECT", (CComponent**)&m_pTexture)))
		return E_FAIL;

	return NOERROR;
}

CFogEffect::CFogEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CEffect(_m_pGraphicDev)
{
}

CFogEffect::CFogEffect(const CFogEffect & rhs)
	: CEffect(rhs)
{
}

_int CFogEffect::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta*0.25f;
	if (m_fTimeDelta >= 1.f)
		m_fTimeDelta = 0.f;

	m_fAlpha += fTimeDelta*m_iFlag *0.25f;
	if (m_fAlpha >= 1.f || m_fAlpha<=0.5f)
		m_iFlag*=-1.f;

	CGameObject::ComputeZ(m_pTransform->GetPosition());
	
	return _int();
}

_int CFogEffect::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CFogEffect::Render()
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

	matWorld.m[0][1] = 0.f;
	matWorld.m[2][1] = 0.f;

	matWorld.m[1][0] = 0.f;
	matWorld.m[1][1] = 1.f;
	matWorld.m[1][2] = 0.f;

	m_pTransform->SetWorldMatrix(matWorld);
	m_pTransform->Scaling(1.8f, 2.5f, 1);
	m_pTransform->SetPosition(vPostion);		
	
	pEffect->SetMatrix("g_matWorld", m_pTransform->GetWorldMatrix());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);
	pEffect->SetFloat("g_fUV", m_fTimeDelta);
	pEffect->SetFloat("g_fAlpha", m_fAlpha);
	
	m_pTexture->SetTexture(pEffect, "g_Texture", 0);
	m_pTexture->SetTexture(pEffect, "g_FilterTexture", 1);
	
	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(3);
	
	m_pBuffer->Render();
	
	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
}

CGameObject * CFogEffect::Clone(void * pArg)
{
	CFogEffect*	pInstance = new CFogEffect(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CFogEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CFogEffect::Free()
{
	CEffect::Free();
}

CFogEffect * CFogEffect::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CFogEffect*	pInstance = new CFogEffect(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CFogEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
