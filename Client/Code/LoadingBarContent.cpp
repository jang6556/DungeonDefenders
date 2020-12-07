#include "stdafx.h"
#include "..\Header\LoadingBarContent.h"


_USING(Client)

HRESULT CLoadingBarContent::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	m_pTransform->Scaling(700, 70, 1);
	m_pTransform->SetPosition(D3DXVECTOR3(0, -315, 0));
	return NOERROR;
}

HRESULT CLoadingBarContent::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CLoadingBarContent::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RECT_UI", (CComponent**)&m_pBuffer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(INTRO, L"SHADER_INTRO", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(INTRO, L"LOADINGBAR", (CComponent**)&m_Texture)))
		return E_FAIL;

	return NOERROR;
}

CLoadingBarContent::CLoadingBarContent(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CLoadingBarContent::CLoadingBarContent(const CLoadingBarContent & rhs)
	: CGameObject(rhs)
{
}

_int CLoadingBarContent::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CLoadingBarContent::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::UI, this)))
		return -1;

	return _int();
}

HRESULT CLoadingBarContent::Render()
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
	pEffect->SetFloat("g_fAlpha", m_fComplete);

	m_Texture->SetTexture(pEffect, "g_Texture", 3);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(1);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
}

CGameObject * CLoadingBarContent::Clone(void * pArg)
{
	CLoadingBarContent*	pInstance = new CLoadingBarContent(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CLoadingBarContent Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLoadingBarContent::SetComplete(int iComplete, const _float & fTimeDelta)
{
	m_fComplete += fTimeDelta;
	float fComplete = (float)iComplete / 100.f;
	if (m_fComplete >= fComplete)
	{
		m_fComplete = fComplete;
	}
}

void CLoadingBarContent::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_Texture);
	Safe_Release(m_pShader);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pBuffer);
	CGameObject::Free();
}

CLoadingBarContent * CLoadingBarContent::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CLoadingBarContent*	pInstance = new CLoadingBarContent(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CLoadingBarContent Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
