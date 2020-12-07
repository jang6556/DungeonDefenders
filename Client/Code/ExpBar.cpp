#include "stdafx.h"
#include "..\Header\ExpBar.h"

_USING(Client)

HRESULT CExpBar::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	
	m_pTransform->Scaling(409, 36, 0);
	m_pTransform->Move(-456.5f, -346.f, 0,1,1);

	m_iTexNum = 5;
	m_iPassNum = 2;



	return NOERROR;
}

HRESULT CExpBar::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CExpBar::AddComponent()
{
	if (FAILED(CPlayerUI::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADERUI", (CComponent**)&m_pShader)))
		return E_FAIL;
	
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"PANEL", (CComponent**)&m_Texture)))
		return E_FAIL;

	return NOERROR;
}

CExpBar::CExpBar(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CPlayerUI(_m_pGraphicDev)
{

}

CExpBar::CExpBar(const CExpBar & rhs)
	: CPlayerUI(rhs)
{

}

_int CExpBar::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta * 0.25f;
	if (m_fTimeDelta >= 1)
		m_fTimeDelta = 0;
	return _int();
}

_int CExpBar::LateProgress(const _float & fTimeDelta)
{
	CPlayer* pPlayer = (CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
	if (pPlayer == nullptr)
		return -1;

	m_fExpRatio.x += fTimeDelta * 100.f;
	if (m_fExpRatio.x >= pPlayer->GetExp().x)
		m_fExpRatio.x = pPlayer->GetExp().x;

	m_fExpRatio.y= pPlayer->GetExp().y;

	return _int();
}

HRESULT CExpBar::Render()
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
	pEffect->SetFloat("g_fRatio", m_fExpRatio.x/ m_fExpRatio.y);
	pEffect->SetFloat("g_fU", -m_fTimeDelta);
	pEffect->SetFloat("g_fSizeX", 6.f);
	pEffect->SetFloat("g_fSizeY", 1.f);

	pEffect->SetVector("g_vColor", &D3DXVECTOR4(0.9725f, 0.6078f, 0.f, 1.f));

	m_Texture->SetTexture(pEffect, "g_Texture", m_iTexNum);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(m_iPassNum);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
}

CGameObject * CExpBar::Clone(void * pArg)
{
	CExpBar*	pInstance = new CExpBar(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CExpBar Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CExpBar::Free()
{
	CPlayerUI::Free();
}

CExpBar * CExpBar::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CExpBar*	pInstance = new CExpBar(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CExpBar Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
