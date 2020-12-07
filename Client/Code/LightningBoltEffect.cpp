#include "stdafx.h"
#include "..\Header\LightningBoltEffect.h"


_USING(Client)
HRESULT CLightningBoltEffect::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXVECTOR3 vPosition = *(D3DXVECTOR3*)pArg;

	m_pTransform->SetPosition(vPosition);

	m_iShaderPass = 4;
	m_iTexNum = 0;

	m_vScale = { 0.7f,0.7f,1 };
	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	m_vColor = { 0.6f, 0.4f, 0.8f };
	return NOERROR;
}

HRESULT CLightningBoltEffect::Initialize()
{
	return NOERROR;
}

HRESULT CLightningBoltEffect::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CLightningBoltEffect::AddComponent()
{
	if (FAILED(CEffect::AddComponent()))
		return E_FAIL;


	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"LIGHTNING_EFFECT", (CComponent**)&m_pTexture)))
		return E_FAIL;
	return NOERROR;
}

CLightningBoltEffect::CLightningBoltEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CEffect(_m_pGraphicDev)
{
}

CLightningBoltEffect::CLightningBoltEffect(const CLightningBoltEffect & rhs)
	: CEffect(rhs)
{
}

_int CLightningBoltEffect::Progress(const _float & fTimeDelta)
{
	m_vScale.x += fTimeDelta*5.f;
	m_vScale.y += fTimeDelta*5.f;
	if (m_vScale.x >= 1.5f || m_vScale.y >= 1.5f)
		return -1;

	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	return _int();
}

_int CLightningBoltEffect::LateProgress(const _float & fTimeDelta)
{
	CGameObject::ComputeZ(m_pTransform->GetPosition());

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::ALPHA_OBJECT, this)))
		return -1;
	return _int();
}

HRESULT CLightningBoltEffect::Render()
{
	return CEffect::Render();
}

CGameObject * CLightningBoltEffect::Clone(void * pArg)
{
	CLightningBoltEffect*	pInstance = new CLightningBoltEffect(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CLightningBoltEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLightningBoltEffect::Free()
{
	CEffect::Free();
}

CLightningBoltEffect * CLightningBoltEffect::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CLightningBoltEffect*	pInstance = new CLightningBoltEffect(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CLightningBoltEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
