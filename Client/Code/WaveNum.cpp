#include "stdafx.h"
#include "..\Header\WaveNum.h"


_USING(Client)

HRESULT CWaveNum::Initialize()
{
	return NOERROR;
}

HRESULT CWaveNum::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	m_iTexNum = *(int*)pArg;
	m_iPassNum = 4;

	m_pTransform->Scaling(435, 171, 0);
	m_pTransform->Move(12.5f, 93.5f, 0, 1, 1);

	return NOERROR;
}

HRESULT CWaveNum::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CWaveNum::AddComponent()
{
	if (FAILED(CPlayerUI::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADERUI", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"WAVE_NUM", (CComponent**)&m_Texture)))
		return E_FAIL;


	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	return NOERROR;
}

CWaveNum::CWaveNum(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CPlayerUI(_m_pGraphicDev)
{
}

CWaveNum::CWaveNum(const CWaveNum & rhs)
	: CPlayerUI(rhs)
{
}

_int CWaveNum::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta;
	
	if (m_fTimeDelta <= 2.f || m_fTimeDelta >= 3.f)
	{
		m_pTransform->Scaling(-fTimeDelta, -fTimeDelta*0.4f, 0, 75);

		m_fAlpha += fTimeDelta*m_fFlag*0.5f;
		if (m_fAlpha >= 1)
			m_fAlpha = 1.f;

	}
	else
	{
		if (m_fFlag == 1.f)
			m_fFlag*=-1.f;
	}

	if (m_fTimeDelta >= 4.5f)
		return -1;
	
	return _int();
}

_int CWaveNum::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::UI, this)))
		return -1;

	return _int();
}

HRESULT CWaveNum::Render()
{
	LPD3DXEFFECT pEffect = m_pShader->GetEffect();

	if (pEffect == nullptr)
		return E_FAIL;

	D3DXMATRIX  matView, matProj;

	D3DXMatrixIdentity(&matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	D3DXMatrixOrthoLH(&matProj, iWINCX, iWINCY, 0.f, 1.f);

	pEffect->SetMatrix("g_matWorld", m_pTransform->GetWorldMatrix());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);
	pEffect->SetFloat("g_fAlpha", m_fAlpha);
	
	m_Texture->SetTexture(pEffect, "g_Texture", m_iTexNum);


	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(m_iPassNum);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
	
}

CGameObject * CWaveNum::Clone(void * pArg)
{
	CWaveNum*	pInstance = new CWaveNum(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CWaveNum Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CWaveNum::Free()
{
	Safe_Release(m_pRenderer);
	CPlayerUI::Free();
}

CWaveNum * CWaveNum::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CWaveNum*	pInstance = new CWaveNum(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CWaveNum Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
