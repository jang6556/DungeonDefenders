#include "stdafx.h"
#include "..\Header\BuildPoint.h"


_USING(Client)
HRESULT CBuildPoint::Initialize()
{
	return NOERROR;
}

HRESULT CBuildPoint::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	m_fScale = 6.f;
	m_pTransform->Scaling(m_fScale, m_fScale, m_fScale);

	return NOERROR;
}

HRESULT CBuildPoint::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CBuildPoint::AddComponent()
{
	if (FAILED(CDecal::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"DECAL", (CComponent**)&m_pTexture)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"NAVIMESH", (CComponent**)&m_pNaviMesh)))
		return E_FAIL;

	D3DVIEWPORT9 ViewPort;
	ZeroMemory(&ViewPort, sizeof(ViewPort));

	m_pGraphicDev->GetViewport(&ViewPort);

	m_pBuffer = CScreenTex_Buffer::Create(m_pGraphicDev, -0.5f, -0.5f, ViewPort.Width, ViewPort.Height);
	if (m_pBuffer == nullptr)
		return E_FAIL;

	return NOERROR;
}

CBuildPoint::CBuildPoint(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CDecal(_m_pGraphicDev)
{
}

CBuildPoint::CBuildPoint(const CBuildPoint & rhs)
	: CDecal(rhs)
{
}

_int CBuildPoint::Progress(const _float & fTimeDelta)
{
	if (m_bIsRelease == true)
		return -1;

	POINT		ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	D3DXVECTOR3 vPoisition;

	if (m_pNaviMesh->NaviMeshPicking(ptMouse, &vPoisition) == true)
	{
		m_pTransform->SetPosition(vPoisition);

		CTransform* pPlayer =(CTransform*)CGameObjectMgr::GetInstance()->FindComponent(SCENESTATIC, L"PLAYER",L"TRANSFORM");
		if (pPlayer == nullptr)
			return int();
		float fDistance = D3DXVec3Length(&(vPoisition - pPlayer->GetPosition()));
		if (fDistance < 6.f)
			m_IsInRange = true;
		else
			m_IsInRange = false;
	}

	return _int();
}

_int CBuildPoint::LateProgress(const _float & fTimeDelta)
{
	if (m_bIsRelease == true)
		return -1;

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::DECAL, this)))
		return -1;

	return _int();
}

HRESULT CBuildPoint::Render(LPD3DXEFFECT pEffect)
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
	pEffect->SetVector("g_vColor", &D3DXVECTOR4(1- m_IsInRange, m_IsInRange,0,0.8f));

	m_pTexture->SetTexture(pEffect, "g_DecalTexture", 3);

	pEffect->CommitChanges();

	pEffect->BeginPass(2);

	m_pBuffer->Render();

	pEffect->EndPass();

	return NOERROR;
}

CGameObject * CBuildPoint::Clone(void * pArg)
{
	CBuildPoint*	pInstance = new CBuildPoint(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CBuildPoint Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBuildPoint::Free()
{
	Safe_Release(m_pNaviMesh);
	CDecal::Free();
}

CBuildPoint * CBuildPoint::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CBuildPoint*	pInstance = new CBuildPoint(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CBuildPoint Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
