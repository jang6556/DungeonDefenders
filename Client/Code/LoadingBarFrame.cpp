#include "stdafx.h"
#include "..\Header\LoadingBarFrame.h"


_USING(Client)

HRESULT CLoadingBarFrame::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	m_pTransform->Scaling(700, 70, 1);
	m_pTransform->SetPosition(D3DXVECTOR3(0, -315, 0));
	return NOERROR;
}

HRESULT CLoadingBarFrame::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CLoadingBarFrame::AddComponent()
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

CLoadingBarFrame::CLoadingBarFrame(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CLoadingBarFrame::CLoadingBarFrame(const CLoadingBarFrame & rhs)
	: CGameObject(rhs)
{
}

_int CLoadingBarFrame::Progress(const _float & fTimeDelta)
{	
	return _int();
}

_int CLoadingBarFrame::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::UI, this)))
		return -1;

	return _int();
}

HRESULT CLoadingBarFrame::Render()
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

	m_Texture->SetTexture(pEffect, "g_Texture", 2);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(0);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
}

CGameObject * CLoadingBarFrame::Clone(void * pArg)
{
	CLoadingBarFrame*	pInstance = new CLoadingBarFrame(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CLoadingBarFrame Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLoadingBarFrame::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_Texture);
	Safe_Release(m_pShader);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pBuffer);
	CGameObject::Free();
}

CLoadingBarFrame * CLoadingBarFrame::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CLoadingBarFrame*	pInstance = new CLoadingBarFrame(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CLoadingBarFrame Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
