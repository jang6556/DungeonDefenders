#include "stdafx.h"
#include "..\Header\BuildLoadingBar.h"


_USING(Client)
HRESULT CBuildLoadingBar::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	m_pTransform->Scaling(166, 52.5f, 0);
	m_pTransform->Move(-186.f, -283.5f, 0, 1, 1);

	m_iTexNum = 9;
	m_iPassNum = 4;
}

HRESULT CBuildLoadingBar::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CBuildLoadingBar::AddComponent()
{
	if (FAILED(CPlayerUI::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADERUI", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"PANEL", (CComponent**)&m_Texture)))
		return E_FAIL;

	return NOERROR;
}

CBuildLoadingBar::CBuildLoadingBar(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	: CPlayerUI(_m_pGraphicDev)
{
}

CBuildLoadingBar::CBuildLoadingBar(const CBuildLoadingBar & rhs)
	: CPlayerUI(rhs)
{
}
 
_int CBuildLoadingBar::Progress(const _float & fTimeDelta)
{
	CPlayer* pPlayer = (CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
	if (pPlayer == nullptr)
		return -1;

	if (pPlayer->GetBuildState() == CPlayer::BUILD_ING)
	{
		m_fAlpha += fTimeDelta*3.f;
		if (m_fAlpha >= 1.f)
			m_fAlpha = 1.f;
	}
	else
	{
		m_fAlpha -= fTimeDelta*3.f;
		if (m_fAlpha <= 0)
		{
			m_fAlpha = 0.f;
			
		}
	}
	return _int();
}

_int CBuildLoadingBar::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CBuildLoadingBar::Render()
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
	pEffect->SetFloat("g_fAlpha", m_fAlpha);


	m_Texture->SetTexture(pEffect, "g_Texture", m_iTexNum);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(m_iPassNum);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
}

CGameObject * CBuildLoadingBar::Clone(void * pArg)
{
	CBuildLoadingBar*	pInstance = new CBuildLoadingBar(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CBuildLoadingBar Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBuildLoadingBar::Free()
{
	CPlayerUI::Free();
}

CBuildLoadingBar * CBuildLoadingBar::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CBuildLoadingBar*	pInstance = new CBuildLoadingBar(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CBuildLoadingBar Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
