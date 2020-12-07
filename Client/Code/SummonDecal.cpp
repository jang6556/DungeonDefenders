#include "stdafx.h"
#include "..\Header\SummonDecal.h"

_USING(Client)

HRESULT CSummonDecal::Initialize()
{
	return NOERROR;
}

HRESULT CSummonDecal::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXVECTOR4 vPosition = *(D3DXVECTOR4*)pArg;
	
	if (vPosition.w == 1)
		m_bFlag = true;
	m_pTransform->SetPosition(D3DXVECTOR3(vPosition.x, vPosition.y, vPosition.z));

	
	m_fScale = 2.5f;
	m_pTransform->Scaling(m_fScale, m_fScale, m_fScale);
	return NOERROR;
}

HRESULT CSummonDecal::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CSummonDecal::AddComponent()
{
	if (FAILED(CDecal::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"DECAL", (CComponent**)&m_pTexture)))
		return E_FAIL;

	D3DVIEWPORT9 ViewPort;
	ZeroMemory(&ViewPort, sizeof(ViewPort));

	m_pGraphicDev->GetViewport(&ViewPort);
	
	m_pBuffer = CScreenTex_Buffer::Create(m_pGraphicDev, -0.5f, -0.5f, ViewPort.Width, ViewPort.Height);
	if (m_pBuffer == nullptr)
		return E_FAIL;

	return NOERROR;
}

CSummonDecal::CSummonDecal(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CDecal(_m_pGraphicDev)
{
}

CSummonDecal::CSummonDecal(const CSummonDecal & rhs)
	: CDecal(rhs)
{
}

_int CSummonDecal::Progress(const _float & fTimeDelta)
{
	if (m_bIsRelease == true)
		return -1;

	
	return _int();
}

_int CSummonDecal::LateProgress(const _float & fTimeDelta)
{
	if (m_bIsRelease == true)
		return -1;

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::DECAL, this)))
		return -1;

	return _int();
}

HRESULT CSummonDecal::Render(LPD3DXEFFECT pEffect)
{
	if (pEffect == nullptr)
		return E_FAIL;

	if (m_bIsRelease == true)
		return NOERROR;

	D3DXMATRIX matView, matProj,matWorld;

	matWorld = *m_pTransform->GetWorldMatrix();
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	D3DXMatrixInverse(&matView, nullptr, &matView);
	D3DXMatrixInverse(&matProj, nullptr, &matProj);
	D3DXMatrixInverse(&matWorld, nullptr, &matWorld);

	pEffect->SetMatrix("g_matViewInv", &matView);
	pEffect->SetMatrix("g_matProjInv", &matProj);
	pEffect->SetMatrix("g_matBoxWorldInv", &matWorld);
	pEffect->SetBool("g_bFlag", m_bFlag);

	m_pTexture->SetTexture(pEffect, "g_DecalTexture", 0); 

	pEffect->CommitChanges();

	pEffect->BeginPass(1);

	m_pBuffer->Render();

	pEffect->EndPass();

	return NOERROR;
}

CGameObject * CSummonDecal::Clone(void * pArg)
{
	CSummonDecal*	pInstance = new CSummonDecal(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CSummonDecal Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CSummonDecal::Free()
{
	CDecal::Free();
}

CSummonDecal * CSummonDecal::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CSummonDecal*	pInstance = new CSummonDecal(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CSummonDecal Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
