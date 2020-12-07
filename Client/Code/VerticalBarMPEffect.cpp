#include "stdafx.h"
#include "../Header/VerticalBarMPEffect.h"


_USING(Client)

HRESULT CVerticalBarMPEffect::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	m_pTransform->Scaling(55, 220, 0);
	m_pTransform->SetPosition(D3DXVECTOR3(-545.f, -315, 0));

	m_pPlayer =(CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");

	m_pPlayer->AddRef();

	return NOERROR;
}

HRESULT CVerticalBarMPEffect::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CVerticalBarMPEffect::AddComponent()
{
	if (FAILED(CPlayerUI::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADERVERTICALEFFECT", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"VERTICALBAR", (CComponent**)&m_Texture)))
		return E_FAIL;

	return NOERROR;
}

CVerticalBarMPEffect::CVerticalBarMPEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CPlayerUI(_m_pGraphicDev)
{
}

CVerticalBarMPEffect::CVerticalBarMPEffect(const CVerticalBarMPEffect & rhs)
	: CPlayerUI(rhs)
{
}

_int CVerticalBarMPEffect::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta -= fTimeDelta*0.5f;
	if (m_fTimeDelta <= 0)
	{
		m_fTimeDelta = 1.f;

	}

	m_fGlare += m_iGlare*fTimeDelta*0.5f;
	if (m_fGlare >= 0.3f)
	{
		m_fGlare = 0.3f;
		m_iGlare *= -1;
	}

	if (m_fGlare <= -0.2f)
	{
		m_fGlare = -0.2f;
		m_iGlare *= -1;
	}

	return _int();
}

_int CVerticalBarMPEffect::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CVerticalBarMPEffect::Render()
{
	LPD3DXEFFECT pEffect = m_pShader->GetEffect();

	if (pEffect == nullptr)
		return E_FAIL;

	D3DXMATRIX  matView, matProj;

	D3DXMatrixIdentity(&matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	D3DXMatrixOrthoLH(&matProj, iWINCX, iWINCY, 0.f, 1.f);
	
	float fRatio =(float)m_pPlayer->GetPlayerInfo().iCurrMp / (float)m_pPlayer->GetPlayerInfo().iMaxMp;
	if (fRatio <= 0)
		fRatio = 0.01f;
	m_pTransform->Scaling(55, 220* fRatio, 1);

	pEffect->SetMatrix("g_matWorld", m_pTransform->GetWorldMatrix());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);
	pEffect->SetFloat("g_fMP", 0.7f); //g_Color
	pEffect->SetFloat("g_fUV", m_fTimeDelta);
	pEffect->SetFloat("g_fGlare", m_fGlare);
	pEffect->SetBool("g_Color", true);

	m_Texture->SetTexture(pEffect, "g_Texture", 5);


	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(0);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
}

CGameObject * CVerticalBarMPEffect::Clone(void * pArg)
{
	CVerticalBarMPEffect*	pInstance = new CVerticalBarMPEffect(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CVerticalBarMPEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CVerticalBarMPEffect::Free()
{
	Safe_Release(m_pPlayer);
	CPlayerUI::Free();
}

CVerticalBarMPEffect * CVerticalBarMPEffect::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CVerticalBarMPEffect*	pInstance = new CVerticalBarMPEffect(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CVerticalBarMPEffect Created Failed");
		Safe_Release(pInstance);
	}

	return pInstance;
}
