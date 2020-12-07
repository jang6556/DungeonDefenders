#include "stdafx.h"
#include "..\Header\NumberUI.h"

_USING(Client)
HRESULT CNumberUI::Initialize()
{
	return NOERROR;
}

HRESULT CNumberUI::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	if (pArg == nullptr)
		return E_FAIL;

	DRAGPANEL tDragPanel = *(DRAGPANEL*)pArg;
	
	m_iTexNum = 0;

	m_vScale = { 36,36 };
	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	m_vPosition = tDragPanel.vPosition;

	m_pTransform->SetPosition(D3DXVECTOR3(m_vPosition.x, m_vPosition.y, 1));

	m_vColor = tDragPanel.vColor;
}

HRESULT CNumberUI::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CNumberUI::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADERUI", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RECT_UI", (CComponent**)&m_pBuffer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"NUMBER_UI", (CComponent**)&m_Texture)))
		return E_FAIL;

	return NOERROR;
}

CNumberUI::CNumberUI(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CNumberUI::CNumberUI(const CNumberUI & rhs)
	: CGameObject(rhs)
{
}

_int CNumberUI::Progress(const _float & fTimeDelta)
{

	return _int();
}

_int CNumberUI::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CNumberUI::Render()
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
	pEffect->SetFloat("g_fUV", 0);
	pEffect->SetVector("g_vColor", &D3DXVECTOR4(m_vColor, 1));

	m_Texture->SetTexture(pEffect, "g_Texture", m_iTexNum);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(8);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	
	return NOERROR;
}

CGameObject * CNumberUI::Clone(void * pArg)
{
	CNumberUI*	pInstance = new CNumberUI(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CNumberUI Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

HRESULT CNumberUI::SetTextureNum(int iNum)
{
	if (iNum < 0)
		return E_FAIL;

	m_iTexNum = iNum;
	return NOERROR;
}

HRESULT CNumberUI::SetScale(float fScale)
{
	m_vScale.x = fScale;
	m_vScale.y = fScale;
	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	return NOERROR;
}

HRESULT CNumberUI::SetPosition(D3DXVECTOR2 vPosition)
{
	m_vPosition = vPosition;

	return NOERROR;
}

void CNumberUI::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_Texture);
	Safe_Release(m_pShader);
	Safe_Release(m_pBuffer);
	CGameObject::Free();
}

CNumberUI * CNumberUI::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CNumberUI*	pInstance = new CNumberUI(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CNumberUI Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
