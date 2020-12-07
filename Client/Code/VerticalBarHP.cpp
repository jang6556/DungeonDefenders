#include "stdafx.h"
#include "..\Header\VerticalBarHP.h"


_USING(Client)

HRESULT CVerticalBarHP::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	m_pTransform->Scaling(-55, 110, 0);
	m_pTransform->SetPosition(D3DXVECTOR3(-600.f, -260, 0));
	
	return NOERROR;
}

HRESULT CVerticalBarHP::Initialize_Prototype()
{
	

	return NOERROR;
}

HRESULT CVerticalBarHP::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADERVERTICAL", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RECT_UI", (CComponent**)&m_pBuffer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"VERTICALBAR", (CComponent**)&m_Texture)))
		return E_FAIL;

	return NOERROR;
}

CVerticalBarHP::CVerticalBarHP(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CVerticalBarHP::CVerticalBarHP(const CVerticalBarHP & rhs)
	: CGameObject(rhs)
{
}

_int CVerticalBarHP::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta -= fTimeDelta;
	if (m_fTimeDelta <= 0)
		m_fTimeDelta = 1.f;

	return _int();
}

_int CVerticalBarHP::LateProgress(const _float & fTimeDelta)
{
	

	return _int();
}

HRESULT CVerticalBarHP::Render()
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
	pEffect->SetFloat("g_fHP", 1.f); //g_Color
	pEffect->SetBool("g_Color", false);

	m_Texture->SetTexture(pEffect, "g_Texture", 1);
	

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(0);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	

	return NOERROR;

	
}

CGameObject * CVerticalBarHP::Clone(void * pArg)
{
	CVerticalBarHP*	pInstance = new CVerticalBarHP(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CVerticalBarHP Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CVerticalBarHP::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_Texture);
	Safe_Release(m_pShader);
	Safe_Release(m_pBuffer);
	CGameObject::Free();
}

CVerticalBarHP * CVerticalBarHP::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CVerticalBarHP*	pInstance = new CVerticalBarHP(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CVerticalBarHP Created Failed");
		Safe_Release(pInstance);
	}

	return pInstance;
}
