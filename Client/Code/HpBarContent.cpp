#include "stdafx.h"
#include "..\Header\HpBarContent.h"


_USING(Client)

HRESULT CHpBarContent::Initialize()
{
	return NOERROR;
}

HRESULT CHpBarContent::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXVECTOR4 vPosition = *(D3DXVECTOR4*)pArg;
	vPosition.y += 0.5f;

	m_pTransform->SetPosition(D3DXVECTOR3(vPosition.x, vPosition.y, vPosition.z));

	m_fScale = vPosition.w;

	return NOERROR;
}

HRESULT CHpBarContent::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CHpBarContent::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADERUI", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RECT_UI", (CComponent**)&m_pBuffer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"MONSTER_UI", (CComponent**)&m_pTexture)))
		return E_FAIL;

	return NOERROR;
}

CHpBarContent::CHpBarContent(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CHpBarContent::CHpBarContent(const CHpBarContent & rhs)
	: CGameObject(rhs)
{
}

_int CHpBarContent::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CHpBarContent::LateProgress(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta*0.5f;
	if (m_fTimeDelta >= 1.f)
		m_fTimeDelta = 0.f;

	return _int();
}

HRESULT CHpBarContent::Render()
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

	pEffect->SetFloat("g_fRatio", m_fRatio);
	pEffect->SetFloat("g_fU", -m_fTimeDelta);
	pEffect->SetFloat("g_fSizeX", 1.f);
	pEffect->SetFloat("g_fSizeY", 0.5f);

	float fRed, fGreen;

	fRed = (1 - m_fRatio)*2.f;
	if (fRed >= 1.f)
		fRed = 1.f;

	fGreen = (m_fRatio)*2.f;
	if (fGreen >= 1.f)
		fGreen = 1.f;

	pEffect->SetVector("g_vColor", &D3DXVECTOR4(fRed, fGreen, 0.f, 1.f));

	m_pTexture->SetTexture(pEffect, "g_Texture", 1);
	m_pTexture->SetTexture(pEffect, "g_Filter", 2);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(2);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
}

CGameObject * CHpBarContent::Clone(void * pArg)
{
	CHpBarContent*	pInstance = new CHpBarContent(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CHpBarContent Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CHpBarContent::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pShader);
	Safe_Release(m_pBuffer);
	CGameObject::Free();
}

CHpBarContent * CHpBarContent::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CHpBarContent*	pInstance = new CHpBarContent(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CHpBarContent Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
