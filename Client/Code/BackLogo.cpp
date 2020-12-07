#include "stdafx.h"
#include "..\Header\BackLogo.h"

_USING(Client)

HRESULT CBackLogo::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	m_pTransform->Scaling(iWINCX, iWINCY, 1);

	return NOERROR;
}

HRESULT CBackLogo::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CBackLogo::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;
		
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RECT_UI", (CComponent**)&m_pBuffer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(INTRO, L"SHADER_INTRO", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(INTRO, L"BACKLOGO", (CComponent**)&m_Texture)))
		return E_FAIL;

	return NOERROR;
}

CBackLogo::CBackLogo(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{

}

CBackLogo::CBackLogo(const CBackLogo & rhs)
	: CGameObject(rhs)
{

}

_int CBackLogo::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta;
	if (m_fTimeDelta >= 18)
		m_fTimeDelta = 0.f;

	return _int();
}

_int CBackLogo::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::UI, this)))
		return -1;

	return _int();
}

HRESULT CBackLogo::Render()
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

	m_Texture->SetTexture(pEffect, "g_Texture", m_fTimeDelta);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(0);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
	
}

CGameObject * CBackLogo::Clone(void * pArg)
{
	CBackLogo*	pInstance = new CBackLogo(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CBackLogo Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBackLogo::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_Texture);
	Safe_Release(m_pShader);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pBuffer);
	CGameObject::Free();
}

CBackLogo * CBackLogo::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CBackLogo*	pInstance = new CBackLogo(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CBackLogo Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
