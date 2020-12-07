#include "stdafx.h"
#include "..\Header\SkillPanel.h"


_USING(Client)

HRESULT CSkillPanel::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	m_pTransform->Scaling(400, 180, 0);
	m_pTransform->SetPosition(D3DXVECTOR3(-443, -277, 0));
	//m_pTransform->SetPosition(D3DXVECTOR3(-242, -230, 0));
	return NOERROR;
}

HRESULT CSkillPanel::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CSkillPanel::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;	
	
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADERUI", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RECT_UI", (CComponent**)&m_pBuffer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"PANEL", (CComponent**)&m_Texture)))
		return E_FAIL;

	return NOERROR;
}

CSkillPanel::CSkillPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CSkillPanel::CSkillPanel(const CSkillPanel & rhs)
	: CGameObject(rhs)
{
}

_int CSkillPanel::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta;
	if (m_fTimeDelta >= 1)
		m_fTimeDelta = 0.f;

	return _int();
}

_int CSkillPanel::LateProgress(const _float & fTimeDelta)
{
	

	return _int();
}

HRESULT CSkillPanel::Render()
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

	m_Texture->SetTexture(pEffect, "g_Texture", 1);
	
	pEffect->Begin(nullptr, 0);	
	pEffect->BeginPass(0);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();
	return NOERROR;
	
}

CGameObject * CSkillPanel::Clone(void * pArg)
{
	CSkillPanel*	pInstance = new CSkillPanel(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CSkillPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CSkillPanel::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_Texture);
	Safe_Release(m_pShader);	
	Safe_Release(m_pBuffer);
	CGameObject::Free();
}

CSkillPanel * CSkillPanel::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CSkillPanel*	pInstance = new CSkillPanel(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CSkillPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
