#include "stdafx.h"
#include "..\Header\PoisonFieldEffect.h"


_USING(Client)

HRESULT CPoisonFieldEffect::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXVECTOR3 vPosition = *(D3DXVECTOR3*)pArg;



	m_pTransform->SetPosition(vPosition);


	m_iShaderPass = 5;
	m_iTexNum = 2;

	int Rand = rand() % 25;

	m_vScale = { Rand / 100.f,Rand / 100.f,1 };
	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	m_vColor = { 0.f,1.f,0.f };
	return NOERROR;
}

HRESULT CPoisonFieldEffect::Initialize()
{
	return NOERROR;
}

HRESULT CPoisonFieldEffect::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CPoisonFieldEffect::AddComponent()
{
	if (FAILED(CEffect::AddComponent()))
		return E_FAIL;


	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"PARTICLE", (CComponent**)&m_pTexture)))
		return E_FAIL;

	return NOERROR;
}

CPoisonFieldEffect::CPoisonFieldEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CEffect(_m_pGraphicDev)
{
}

CPoisonFieldEffect::CPoisonFieldEffect(const CPoisonFieldEffect & rhs)
	: CEffect(rhs)
{
}

_int CPoisonFieldEffect::Progress(const _float & fTimeDelta)
{
	m_fAlpha -= fTimeDelta;
			
	m_vScale.x -= fTimeDelta;
	m_vScale.y -= fTimeDelta;
	if (m_vScale.x <= 0 || m_vScale.y <= 0)
		return -1;

	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	m_pTransform->Move(0, 2, 0, 1, fTimeDelta);
	return _int();
}

_int CPoisonFieldEffect::LateProgress(const _float & fTimeDelta)
{
	CGameObject::ComputeZ(m_pTransform->GetPosition());

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::ALPHA_OBJECT, this)))
		return -1;
	return _int();
}

HRESULT CPoisonFieldEffect::Render()
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
	pEffect->SetVector("g_vColor", &D3DXVECTOR4(m_vColor, 0.f));
	pEffect->SetFloat("g_fAlpha", m_fAlpha);

	m_pTexture->SetTexture(pEffect, "g_Texture", (int)m_iTexNum);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(m_iShaderPass);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
}

CGameObject * CPoisonFieldEffect::Clone(void * pArg)
{
	CPoisonFieldEffect*	pInstance = new CPoisonFieldEffect(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CPoisonFieldEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CPoisonFieldEffect::Free()
{
	CEffect::Free();
}

CPoisonFieldEffect * CPoisonFieldEffect::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CPoisonFieldEffect*	pInstance = new CPoisonFieldEffect(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CPoisonFieldEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
