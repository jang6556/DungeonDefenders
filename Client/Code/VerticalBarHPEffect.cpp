#include "stdafx.h"
#include "..\Header\VerticalBarHPEffect.h"


_USING(Client)

HRESULT CVerticalBarHPEffect::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	m_pTransform->Scaling(55, 220, 0);
	m_pTransform->SetPosition(D3DXVECTOR3(-600.f, -315, 0));
	
	m_pPlayer = (CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");

	m_pPlayer->AddRef();

	return NOERROR;
}

HRESULT CVerticalBarHPEffect::Initialize_Prototype()
{


	return NOERROR;
}

HRESULT CVerticalBarHPEffect::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADERVERTICALEFFECT", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RECT_UI", (CComponent**)&m_pBuffer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"VERTICALBAR", (CComponent**)&m_Texture)))
		return E_FAIL;

	return NOERROR;
}

CVerticalBarHPEffect::CVerticalBarHPEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CVerticalBarHPEffect::CVerticalBarHPEffect(const CVerticalBarHPEffect & rhs)
	: CGameObject(rhs)
{
}

_int CVerticalBarHPEffect::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta -= fTimeDelta*0.5f;
	if (m_fTimeDelta <= 0)
	{
		m_fTimeDelta = 1.f;
	
	}
	
	m_fGlare += m_iGlare*fTimeDelta*0.5f;
	if (m_fGlare >= 0.3f )
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

_int CVerticalBarHPEffect::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CVerticalBarHPEffect::Render()
{
	LPD3DXEFFECT pEffect = m_pShader->GetEffect();

	if (pEffect == nullptr)
		return E_FAIL;


	D3DXMATRIX  matView, matProj;

	D3DXMatrixIdentity(&matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	D3DXMatrixOrthoLH(&matProj, iWINCX, iWINCY, 0.f, 1.f);

	float fRatio = (float)m_pPlayer->GetPlayerInfo().iCurrHp / (float)m_pPlayer->GetPlayerInfo().iMaxHp;
	if (fRatio <= 0)
		fRatio = 0.01f;
	m_pTransform->Scaling(55, 220 * fRatio, 1);

	pEffect->SetMatrix("g_matWorld", m_pTransform->GetWorldMatrix());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);
	pEffect->SetFloat("g_fHP", 0.7f); //g_Color
	pEffect->SetFloat("g_fUV", -m_fTimeDelta);
	pEffect->SetFloat("g_fGlare", m_fGlare);
	pEffect->SetBool("g_Color", false);

	m_Texture->SetTexture(pEffect, "g_Texture", 5);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(0);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();



	return NOERROR;

}

CGameObject * CVerticalBarHPEffect::Clone(void * pArg)
{
	CVerticalBarHPEffect*	pInstance = new CVerticalBarHPEffect(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CVerticalBarHPEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CVerticalBarHPEffect::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_Texture);
	Safe_Release(m_pShader);	
	Safe_Release(m_pBuffer);
	Safe_Release(m_pPlayer);
	CGameObject::Free();
}

CVerticalBarHPEffect * CVerticalBarHPEffect::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CVerticalBarHPEffect*	pInstance = new CVerticalBarHPEffect(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CVerticalBarHPEffect Created Failed");
		Safe_Release(pInstance);
	}

	return pInstance;
}
