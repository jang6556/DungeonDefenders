#include "stdafx.h"
#include "..\Header\BuildLoadingContent.h"


_USING(Client)
HRESULT CBuildLoadingContent::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	m_pTransform->Scaling(166, 52.5f, 0);
	m_pTransform->Move(-186.f, -283.5f, 0, 1, 1);

	m_iTexNum = 7;
	m_iPassNum = 5;
}

HRESULT CBuildLoadingContent::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CBuildLoadingContent::AddComponent()
{
	if (FAILED(CPlayerUI::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADERUI", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"PANEL", (CComponent**)&m_Texture)))
		return E_FAIL;

	return NOERROR;
}

CBuildLoadingContent::CBuildLoadingContent(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	: CPlayerUI(_m_pGraphicDev)
{
}

CBuildLoadingContent::CBuildLoadingContent(const CBuildLoadingContent & rhs)
	: CPlayerUI(rhs)
{
}

_int CBuildLoadingContent::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta * 0.25f;
	if (m_fTimeDelta >= 1)
		m_fTimeDelta = 0;


	CPlayer* pPlayer = (CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
	if (pPlayer == nullptr)
		return -1;

	if (pPlayer->GetBuildState() == CPlayer::BUILD_ING)
	{
		m_fRatio += fTimeDelta;
		if (m_fRatio >= pPlayer->GetBuildTimeRatio())
			m_fRatio = pPlayer->GetBuildTimeRatio();

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
			m_fRatio = 0.f;
		}
	}

	return _int();
}

_int CBuildLoadingContent::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CBuildLoadingContent::Render()
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
	pEffect->SetFloat("g_fRatio", m_fRatio);
	pEffect->SetFloat("g_fU", -m_fTimeDelta);
	pEffect->SetFloat("g_fSizeX", 3.f);
	pEffect->SetFloat("g_fSizeY", 1.f);
	pEffect->SetFloat("g_fAlpha", m_fAlpha);
	pEffect->SetVector("g_vColor", &D3DXVECTOR4(0.086f, 0.318f, 0.737f, 1.f));

	m_Texture->SetTexture(pEffect, "g_Texture", m_iTexNum);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(m_iPassNum);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
	
}

CGameObject * CBuildLoadingContent::Clone(void * pArg)
{
	CBuildLoadingContent*	pInstance = new CBuildLoadingContent(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CBuildLoadingContent Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBuildLoadingContent::Free()
{
	CPlayerUI::Free();
}

CBuildLoadingContent * CBuildLoadingContent::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CBuildLoadingContent*	pInstance = new CBuildLoadingContent(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CBuildLoadingContent Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
