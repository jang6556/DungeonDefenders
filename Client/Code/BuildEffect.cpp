#include "stdafx.h"
#include "..\Header\BuildEffect.h"

_USING(Client)

HRESULT CBuildEffect::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXVECTOR4 vPosition = *(D3DXVECTOR3*)pArg;
	vPosition.y += 0.25f;
	m_pTransform->SetPosition(D3DXVECTOR3(vPosition.x, vPosition.y, vPosition.z));

	m_fTimeLimit = vPosition.w;

	m_iShaderPass = 8;
	m_iTexNum = 7;

	m_vScale = { 0.35f,0.35f,1 };
	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	m_vColor = { 1,0.8f,0.7f };

	return NOERROR;
}

HRESULT CBuildEffect::Initialize()
{
	return NOERROR;
}

HRESULT CBuildEffect::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CBuildEffect::AddComponent()
{
	if (FAILED(CEffect::AddComponent()))
		return E_FAIL;


	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"PARTICLE", (CComponent**)&m_pTexture)))
		return E_FAIL;

	return NOERROR;
}

CBuildEffect::CBuildEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CEffect(_m_pGraphicDev)
{
}

CBuildEffect::CBuildEffect(const CBuildEffect & rhs)
	: CEffect(rhs)
{
}

_int CBuildEffect::Progress(const _float & fTimeDelta)
{
	m_fTimeLimit -= fTimeDelta;
	if (m_fTimeLimit <= 0)
		return -1;

	m_vScale.x +=fTimeDelta*m_iFlag*0.4f;
	m_vScale.y += fTimeDelta*m_iFlag*0.4f;

	if (m_vScale.x >= 0.6 || m_vScale.y >= 0.6)
		m_iFlag *= -1;

	if (m_vScale.x <= 0.35 || m_vScale.y <= 0.35)
		m_iFlag *= -1;

	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);
	return _int();
}

_int CBuildEffect::LateProgress(const _float & fTimeDelta)
{
	CGameObject::ComputeZ(m_pTransform->GetPosition());

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::ALPHA_EFFECT, this)))
		return -1;

	return _int();
}

HRESULT CBuildEffect::Render()
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
	pEffect->SetVector("g_vColorPng", &D3DXVECTOR4(m_vColor, 0.9f));

	m_pTexture->SetTexture(pEffect, "g_Texture", (int)m_iTexNum);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(m_iShaderPass);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
}

CGameObject * CBuildEffect::Clone(void * pArg)
{
	CBuildEffect*	pInstance = new CBuildEffect(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CBuildEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBuildEffect::Free()
{
	CEffect::Free();
}

CBuildEffect * CBuildEffect::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CBuildEffect*	pInstance = new CBuildEffect(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CBuildEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
