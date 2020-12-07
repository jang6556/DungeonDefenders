#include "stdafx.h"
#include "..\Header\RangeDecal.h"


_USING(Client)

HRESULT CRangeDecal::Initialize()
{
	return NOERROR;
}

HRESULT CRangeDecal::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXVECTOR3 vPosition = *(D3DXVECTOR3*)pArg;
		
	m_pTransform->SetPosition(vPosition);


	m_fScale = 13.f;
	m_pTransform->Scaling(m_fScale, m_fScale, m_fScale);

	return NOERROR;
}

HRESULT CRangeDecal::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CRangeDecal::AddComponent()
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

CRangeDecal::CRangeDecal(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CDecal(_m_pGraphicDev)
{
}

CRangeDecal::CRangeDecal(const CRangeDecal & rhs)
	: CDecal(rhs)
{
}

_int CRangeDecal::Progress(const _float & fTimeDelta)
{
	if (m_bIsRelease == true)
		return -1;
	
	m_pTransform->RotationAxis(m_pTransform->GetUp(), D3DXToRadian(10), fTimeDelta);

	return _int();
}

_int CRangeDecal::LateProgress(const _float & fTimeDelta)
{
	if (m_bIsRelease == true)
		return -1;

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::DECAL, this)))
		return -1;

	return _int();
}

HRESULT CRangeDecal::Render(LPD3DXEFFECT pEffect)
{
	if (pEffect == nullptr)
		return E_FAIL;

	if (m_bIsRelease == true)
		return NOERROR;

	D3DXMATRIX matView, matProj, matWorld;

	matWorld = *m_pTransform->GetWorldMatrix();
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	D3DXMatrixInverse(&matView, nullptr, &matView);
	D3DXMatrixInverse(&matProj, nullptr, &matProj);
	D3DXMatrixInverse(&matWorld, nullptr, &matWorld);

	pEffect->SetMatrix("g_matViewInv", &matView);
	pEffect->SetMatrix("g_matProjInv", &matProj);
	pEffect->SetMatrix("g_matBoxWorldInv", &matWorld);
	pEffect->SetVector("g_vColor", &D3DXVECTOR4(0, 0.5f, 1, 1.f));
	m_pTexture->SetTexture(pEffect, "g_DecalTexture", 2);	

	pEffect->CommitChanges();

	pEffect->BeginPass(2);

	m_pBuffer->Render();

	pEffect->EndPass();

	return NOERROR;
}

CGameObject * CRangeDecal::Clone(void * pArg)
{
	CRangeDecal*	pInstance = new CRangeDecal(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CRangeDecal Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CRangeDecal::Free()
{
	CDecal::Free();
}

CRangeDecal * CRangeDecal::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CRangeDecal*	pInstance = new CRangeDecal(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CRangeDecal Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
