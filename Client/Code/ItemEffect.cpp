#include "stdafx.h"
#include "..\Header\ItemEffect.h"


_USING(Client)
HRESULT CItemEffect::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXVECTOR4 vPosition = *(D3DXVECTOR4*)pArg;



	m_pTransform->SetPosition(D3DXVECTOR3(vPosition.x,vPosition.y,vPosition.z));


	int iType = vPosition.w;
	if (FAILED(SeletColor((CItemEffect::COLOR)iType)))
		return E_FAIL;


	m_iShaderPass = 5;
	m_iTexNum = 4;

	int Rand = rand() % 50;

	m_vScale = { 0.8f + Rand/100.f,0.8f + Rand / 100.f,1 };
	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);	

	return NOERROR;
}

HRESULT CItemEffect::Initialize()
{
	return NOERROR;
}

HRESULT CItemEffect::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CItemEffect::AddComponent()
{
	if (FAILED(CEffect::AddComponent()))
		return E_FAIL;


	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"PARTICLE", (CComponent**)&m_pTexture)))
		return E_FAIL;
	return NOERROR;
}

HRESULT CItemEffect::SeletColor(COLOR eType)
{
	if (eType >= COLOR_END)
		return E_FAIL;

	switch (eType)
	{
	case COLOR_BLUE:
		m_vColor = { 0.0275f,0.3922f,1.f };
		break;
	case COLOR_RED:
		m_vColor = { 1.f,0.3725f,0.251f };
		break;
	case COLOR_GREEN:
		m_vColor = { 0.3176f,1.f,0.051f };
		break;
	case COLOR_PURPLE:
		m_vColor = { 0.6824f,0.f,0.949f };
		break;
	case COLOR_SKY:
		m_vColor = { 0.1922f,0.8941f,1.f };
		break;
	case COLOR_YELLOW:
		m_vColor = { 0.9686f,0.902f,0.f };
		break;	
	}

	return NOERROR;
}

CItemEffect::CItemEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CEffect(_m_pGraphicDev)
{
}

CItemEffect::CItemEffect(const CItemEffect & rhs)
	: CEffect(rhs)
{
}

_int CItemEffect::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta;
	if (m_fTimeDelta >= 0.5f)
	{
		m_fAlpha -= fTimeDelta;
		if (m_fAlpha <= 0)
			return -1;
	}
	m_vScale.x -= fTimeDelta*2.f;
	m_vScale.y -= fTimeDelta*2.f;
	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);
	m_pTransform->Move(0, 2, 0, 1, fTimeDelta);

	return _int();
}

_int CItemEffect::LateProgress(const _float & fTimeDelta)
{
	CGameObject::ComputeZ(m_pTransform->GetPosition());

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::ALPHA_OBJECT, this)))
		return -1;
	return _int();
}

HRESULT CItemEffect::Render()
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

CGameObject * CItemEffect::Clone(void * pArg)
{
	CItemEffect*	pInstance = new CItemEffect(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CItemEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CItemEffect::Free()
{
	CEffect::Free();
}

CItemEffect * CItemEffect::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CItemEffect*	pInstance = new CItemEffect(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CItemEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
