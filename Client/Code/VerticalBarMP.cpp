#include "stdafx.h"
#include "..\Header\VerticalBarMP.h"


_USING(Client)

HRESULT CVerticalBarMP::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	m_pTransform->Scaling(55, 110, 0);
	m_pTransform->SetPosition(D3DXVECTOR3(-545.f, -260, 0));

	return NOERROR;
}

HRESULT CVerticalBarMP::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CVerticalBarMP::AddComponent()
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

CVerticalBarMP::CVerticalBarMP(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CVerticalBarMP::CVerticalBarMP(const CVerticalBarMP & rhs)
	: CGameObject(rhs)
{
}

_int CVerticalBarMP::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta -= fTimeDelta;
	if (m_fTimeDelta <= 0)
		m_fTimeDelta = 1.f;

	return _int();
}

_int CVerticalBarMP::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CVerticalBarMP::Render()
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
	pEffect->SetFloat("g_fMP", 1); 
	pEffect->SetBool("g_Color", true);

	m_Texture->SetTexture(pEffect, "g_Texture", 1);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(0);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();



	return NOERROR;
}

CGameObject * CVerticalBarMP::Clone(void * pArg)
{
	CVerticalBarMP*	pInstance = new CVerticalBarMP(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CVerticalBarMP Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CVerticalBarMP::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_Texture);
	Safe_Release(m_pShader);
	Safe_Release(m_pBuffer);
	CGameObject::Free();
}

CVerticalBarMP * CVerticalBarMP::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CVerticalBarMP*	pInstance = new CVerticalBarMP(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CVerticalBarMP Created Failed");
		Safe_Release(pInstance);
	}

	return pInstance;
}
