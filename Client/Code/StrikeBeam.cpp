#include "stdafx.h"
#include "..\Header\StrikeBeam.h"

_USING(Client)

HRESULT CStrikeBeam::Initialize()
{
	return NOERROR;
}

HRESULT CStrikeBeam::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	m_fScale = 0.01f;
	m_pTransform->Scaling(m_fScale, m_fScale, m_fScale);

	

	return NOERROR;
}

HRESULT CStrikeBeam::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CStrikeBeam::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADER", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"LIGHTNING_BOLT", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;
	return NOERROR;
}

CStrikeBeam::CStrikeBeam(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CStrikeBeam::CStrikeBeam(const CStrikeBeam & rhs)
	: CGameObject(rhs)
{
}

_int CStrikeBeam::Progress(const _float & fTimeDelta)
{
	
	m_fTimeDelta += fTimeDelta;
	if (m_fTimeDelta >= 1.f)
		m_fTimeDelta = 0.f;

	if (m_IsRender == true)
	{
		m_fScale -= fTimeDelta*0.01f;
		m_pTransform->Scaling(m_pTransform->GetScale().x, m_fScale, m_fScale);
		if (m_fScale <= 0)
			m_IsRender = false;
	}

	return _int();
}

_int CStrikeBeam::LateProgress(const _float & fTimeDelta)
{
	if (m_IsRender == true)
	{
		CGameObject::ComputeZ(m_pTransform->GetPosition());

		if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::ALPHA_OBJECT, this)))
			return -1;
	}

	return _int();
}

HRESULT CStrikeBeam::Render()
{
	LPD3DXEFFECT pEffect = m_pShader->GetEffect();
	if (pEffect == nullptr)
		return E_FAIL;
	D3DXMATRIX matView, matProj;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matWorld", m_pTransform->GetWorldMatrix());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);

	pEffect->SetVector("g_vColor", &D3DXVECTOR4(1.f,1.f, 0.0f, 0.f));
	pEffect->SetFloat("g_fUV_X", -m_fTimeDelta);

	pEffect->Begin(nullptr, 0);
	unsigned long iSubsetNum = m_pMeshStatic->GetSubsetNum();

	for (int i = 0; i < iSubsetNum; ++i)
	{
		m_pMeshStatic->SetShaderMeshTex(pEffect, i, "g_Texture", MESHTEXTURE::MESH_DIFFUSE);

		pEffect->CommitChanges();
		pEffect->BeginPass(5);
		m_pMeshStatic->Render(i);
		pEffect->EndPass();
	}
	pEffect->End();

	return NOERROR;
	
}

HRESULT CStrikeBeam::SetTarget(POS_TARGET vPosTarget, bool IsRender)
{
	m_IsRender = IsRender;

	if (m_IsRender == false)
		return NOERROR;

	D3DXVECTOR3 vPosition = vPosTarget.vPosition;
	D3DXVECTOR3 vTarget = vPosTarget.vTarget;

	D3DXVECTOR3 vRight = vTarget - vPosition;
	float fDistance = D3DXVec3Length(&vRight);

	D3DXVECTOR3 vUp, vLook;

	D3DXVec3Cross(&vLook, &vRight, &D3DXVECTOR3(0, 1, 0));
	D3DXVec3Cross(&vUp, &vLook, &vRight);

	D3DXVec3Normalize(&vRight, &vRight);
	D3DXVec3Normalize(&vUp, &vUp);
	D3DXVec3Normalize(&vLook, &vLook);

	m_pTransform->SetRight(vRight);
	m_pTransform->SetUp(vUp);
	m_pTransform->SetLook(vLook);
	m_pTransform->SetPosition(vPosition);

	m_fScale = 0.01f;
	m_pTransform->Scaling(0.013f*fDistance, m_fScale, m_fScale);

	m_pTransform->RotationAxis(m_pTransform->GetUp(), D3DXToRadian(180), 1);

	return NOERROR;
}

CGameObject * CStrikeBeam::Clone(void * pArg)
{
	CStrikeBeam*	pInstance = new CStrikeBeam(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CStrikeBeam Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CStrikeBeam::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pShader);
	Safe_Release(m_pMeshStatic);
	Safe_Release(m_pRenderer);
	CGameObject::Free();
}

CStrikeBeam * CStrikeBeam::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CStrikeBeam*	pInstance = new CStrikeBeam(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CStrikeBeam Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
