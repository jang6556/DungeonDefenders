#include "stdafx.h"
#include "..\Header\PlayerUI.h"


_USING(Client)

HRESULT CPlayerUI::Initialize()
{
	return NOERROR;
}

HRESULT CPlayerUI::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CPlayerUI::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;
	
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RECT_UI", (CComponent**)&m_pBuffer)))
		return E_FAIL;

	return NOERROR;
}

CPlayerUI::CPlayerUI(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CPlayerUI::CPlayerUI(const CPlayerUI & rhs)
	: CGameObject(rhs)
{
}

_int CPlayerUI::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CPlayerUI::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CPlayerUI::Render()
{
	LPD3DXEFFECT pEffect = m_pShader->GetEffect();

	if (pEffect == nullptr)
		return E_FAIL;

	D3DXMATRIX  matView, matProj;

	D3DXMatrixIdentity(&matView);
	D3DXMatrixOrthoLH(&matProj, iWINCX, iWINCY, 0.f, 1.f);

	pEffect->SetMatrix("g_matWorld", m_pTransform->GetWorldMatrix());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);
	pEffect->SetFloat("g_fUV", 0);

	m_Texture->SetTexture(pEffect, "g_Texture", m_iTexNum);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(m_iPassNum);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
}

CGameObject * CPlayerUI::Clone(void * pArg)
{
	return nullptr;
}

void CPlayerUI::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_Texture);
	Safe_Release(m_pShader);
	Safe_Release(m_pBuffer);
	CGameObject::Free();
}
