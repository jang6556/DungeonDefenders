#include "stdafx.h"
#include "..\Header\HpBarUI.h"


_USING(Client)

HRESULT CHpBarUI::Initialize()
{
	return NOERROR;
}

HRESULT CHpBarUI::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXVECTOR4 vPosition = *(D3DXVECTOR4*)pArg;
	vPosition.y += 0.5f;

	m_pTransform->SetPosition(D3DXVECTOR3(vPosition.x,vPosition.y,vPosition.z));

	m_fScale = vPosition.w;

	return NOERROR;
}

HRESULT CHpBarUI::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CHpBarUI::AddComponent()
{
	if(FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADERUI", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RECT_UI", (CComponent**)&m_pBuffer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"MONSTER_UI", (CComponent**)&m_pTexture)))
		return E_FAIL;

	return NOERROR;
}

CHpBarUI::CHpBarUI(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CHpBarUI::CHpBarUI(const CHpBarUI & rhs)
	: CGameObject(rhs)
{
}

_int CHpBarUI::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CHpBarUI::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CHpBarUI::Render()
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
	m_pTransform->Scaling(m_fScale, m_fScale / 4.f, 1);
	m_pTransform->SetPosition(vPostion);
	
	pEffect->SetMatrix("g_matWorld", m_pTransform->GetWorldMatrix());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);
	pEffect->SetFloat("g_fUV", 0);

	m_pTexture->SetTexture(pEffect, "g_Texture", 0);
	m_pTexture->SetTexture(pEffect, "g_AlphaTexture", 1);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(6);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
}

CGameObject * CHpBarUI::Clone(void * pArg)
{
	CHpBarUI*	pInstance = new CHpBarUI(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CHpBarUI Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CHpBarUI::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pShader);
	Safe_Release(m_pBuffer);
	CGameObject::Free();
}

CHpBarUI * CHpBarUI::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CHpBarUI*	pInstance = new CHpBarUI(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CHpBarUI Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
