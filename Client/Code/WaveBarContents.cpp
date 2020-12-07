#include "stdafx.h"
#include "..\Header\WaveBarContents.h"


_USING(Client)

HRESULT CWaveBarContents::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	m_pTransform->Scaling(442, 51.5f, 0);
	m_pTransform->Move(266.5f, 320.5f, 0, 1, 1);

	m_iTexNum = 3;
	m_iPassNum = 2;
}

HRESULT CWaveBarContents::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CWaveBarContents::AddComponent()
{
	if (FAILED(CPlayerUI::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADERUI", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"PANEL", (CComponent**)&m_Texture)))
		return E_FAIL;

	return NOERROR;
}

CWaveBarContents::CWaveBarContents(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	: CPlayerUI(_m_pGraphicDev)
{
}

CWaveBarContents::CWaveBarContents(const CWaveBarContents & rhs)
	: CPlayerUI(rhs)
{
}

_int CWaveBarContents::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta * 0.25f;
	if (m_fTimeDelta >= 1)
		m_fTimeDelta = 0;

	CMonsterController* pInstance = (CMonsterController*)CGameObjectMgr::GetInstance()->FindGameObject(SCENE_MAGNUS, L"CONTROLLER");
	if (pInstance == nullptr)
		return E_FAIL;

	D3DXVECTOR2 vRatio = pInstance->GetKillWave();


	m_vCurrWave.x += fTimeDelta * 0.5f;
	if (m_vCurrWave.x >= vRatio.x)
		m_vCurrWave.x = vRatio.x;

	m_vCurrWave.y = vRatio.y;

	return _int();
}

_int CWaveBarContents::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CWaveBarContents::Render()
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
	pEffect->SetFloat("g_fRatio", m_vCurrWave.x / m_vCurrWave.y);
	pEffect->SetFloat("g_fU", -m_fTimeDelta);
	pEffect->SetFloat("g_fSizeX", 5.f);
	pEffect->SetFloat("g_fSizeY", 1.f);
	pEffect->SetVector("g_vColor", &D3DXVECTOR4(1.f,0.2f,0.f,1.f));

	m_Texture->SetTexture(pEffect, "g_Texture", m_iTexNum);
	m_Texture->SetTexture(pEffect, "g_Filter", 6);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(m_iPassNum);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
}

CGameObject * CWaveBarContents::Clone(void * pArg)
{
	CWaveBarContents*	pInstance = new CWaveBarContents(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CWaveBarContents Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CWaveBarContents::Free()
{
	CPlayerUI::Free();
}

CWaveBarContents * CWaveBarContents::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CWaveBarContents*	pInstance = new CWaveBarContents(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CWaveBarContents Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
