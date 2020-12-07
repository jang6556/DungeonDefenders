#include "stdafx.h"
#include "..\Header\GlowBall.h"


_USING(Client)

HRESULT CGlowBall::Initialize()
{
	return NOERROR;
}

HRESULT CGlowBall::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXVECTOR3 vPosition = *(D3DXVECTOR3*)pArg;

	m_fScale = 0.0035f;
	m_pTransform->Scaling(m_fScale, m_fScale, m_fScale);

	m_pTransform->SetPosition(vPosition);

	return NOERROR;
}

HRESULT CGlowBall::Initialize_Prototype()
{
	
	return NOERROR;
}

HRESULT CGlowBall::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADER", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"GLOWBALL", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CGlowBall::ComputeMatrix(D3DXMATRIX * pOut)
{
	if (pOut == nullptr || m_pParentTransform == nullptr)
		return E_FAIL;	

	D3DXMATRIX Matrix = m_pParentBoneMatirx * *m_pParentTransform->GetWorldMatrix();

	D3DXMATRIX matCompute;
	D3DXMatrixIdentity(&matCompute);
	
	memcpy(&matCompute.m[3][0], &Matrix.m[3][0], sizeof(D3DXVECTOR3));	

	*pOut = *m_pTransform->GetWorldMatrix()*matCompute;

	return NOERROR;
}

CGlowBall::CGlowBall(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CGlowBall::CGlowBall(const CGlowBall & rhs)
	: CGameObject(rhs)
{
}

_int CGlowBall::Progress(const _float & fTimeDelta)
{	
	/*if (m_bScaleFlag == true)
		return _int();

	if (-1 == Idle(fTimeDelta))
		return -1;	*/

	return _int();
}

_int CGlowBall::LateProgress(const _float & fTimeDelta)
{
	CGameObject::ComputeZ(m_pTransform->GetPosition());

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::ALPHA_EFFECT, this)))
		return -1;

	return _int();
}

HRESULT CGlowBall::Render()
{	
	D3DXMATRIX matWorld;
	ComputeMatrix(&matWorld);

	LPD3DXEFFECT pEffect = m_pShader->GetEffect();
	if (pEffect == nullptr)
		return E_FAIL;
	D3DXMATRIX matView, matProj;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);	

	pEffect->SetMatrix("g_matWorld", &matWorld);
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);

	pEffect->Begin(nullptr, 0);
	unsigned long iSubsetNum = m_pMeshStatic->GetSubsetNum();

	for (int i = 0; i < iSubsetNum; ++i)
	{
		m_pMeshStatic->SetShaderMeshTex(pEffect, i, "g_Texture", MESHTEXTURE::MESH_DIFFUSE);

		pEffect->CommitChanges();
		pEffect->BeginPass(1);
		m_pMeshStatic->Render(i);
		pEffect->EndPass();
	}
	pEffect->End();

	

	return NOERROR;
}

CGameObject * CGlowBall::Clone(void * pArg)
{
	CGlowBall*	pInstance = new CGlowBall(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CGlowBall Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

HRESULT CGlowBall::SetMatrix(CTransform * pParentTransform, D3DXMATRIX pParentBoneMatirx)
{
	if (pParentTransform == nullptr)
		return E_FAIL;

	m_pParentTransform = pParentTransform;
	m_pParentBoneMatirx = pParentBoneMatirx;

	return NOERROR;
}


void CGlowBall::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pShader);	
	Safe_Release(m_pMeshStatic);
	Safe_Release(m_pRenderer);
	CGameObject::Free();
}

CGlowBall * CGlowBall::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CGlowBall*	pInstance = new CGlowBall(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CGlowBall Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
