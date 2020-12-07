#include "stdafx.h"
#include "..\Header\Phase.h"

_USING(Client)

HRESULT CPhase::Initialize()
{
	return NOERROR;
}

HRESULT CPhase::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	m_iTexNum = *(int*)pArg;
	m_iPassNum = 4;

	m_pTransform->Scaling(729.5f, 178, 0);
	m_pTransform->Move(3.5f, 157.5f, 0, 1, 1);

	return NOERROR;
}

HRESULT CPhase::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CPhase::AddComponent()
{
	if (FAILED(CPlayerUI::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADERUI", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"PHASE", (CComponent**)&m_Texture)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	return NOERROR;
}

CPhase::CPhase(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CPlayerUI(_m_pGraphicDev)
{
}

CPhase::CPhase(const CPhase & rhs)
	: CPlayerUI(rhs)
{
}

_int CPhase::Progress(const _float & fTimeDelta)
{	
	m_fTimeDelta += fTimeDelta;

	if (m_fTimeDelta <= 1.5f || m_fTimeDelta >= 2.5f)
	{
		m_pTransform->Scaling(-fTimeDelta, -fTimeDelta*0.25f, 0, 100);

		m_fAlpha += fTimeDelta*m_fFlag*0.85f;
		if (m_fAlpha >= 1)
			m_fAlpha = 1.f;

	}
	else
	{
		if (m_fFlag == 1.f)
			m_fFlag *= -1.f;
	}

	if (m_fTimeDelta >= 4.f)
		m_fTimeDelta = 0.f;

	return _int();
}

_int CPhase::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::UI, this)))
		return -1;

	return _int();
}

HRESULT CPhase::Render()
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

CGameObject * CPhase::Clone(void * pArg)
{
	CPhase*	pInstance = new CPhase(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CPhase Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CPhase::Free()
{
	Safe_Release(m_pRenderer);
	CPlayerUI::Free();
}

CPhase * CPhase::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CPhase*	pInstance = new CPhase(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CPhase Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
