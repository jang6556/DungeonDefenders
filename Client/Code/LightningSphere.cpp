#include "stdafx.h"
#include "..\Header\LightningSphere.h"


_USING(Client)

HRESULT CLightningSphere::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXVECTOR3 vPosition = *(D3DXVECTOR3*)pArg;

	m_pTransform->SetPosition(vPosition);

	m_iShaderPass = 4;
	m_iTexNum = 1;

	m_vScale = { 1.f,1.f,1 };
	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	m_vColor = { 0.6f, 0.4f, 0.8f };

	return NOERROR;
}

HRESULT CLightningSphere::Initialize()
{
	return NOERROR;
}

HRESULT CLightningSphere::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CLightningSphere::AddComponent()
{
	if (FAILED(CEffect::AddComponent()))
		return E_FAIL;


	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"LIGHTNING_EFFECT", (CComponent**)&m_pTexture)))
		return E_FAIL;
	return NOERROR;
}

CLightningSphere::CLightningSphere(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CEffect(_m_pGraphicDev)
{
}

CLightningSphere::CLightningSphere(const CLightningSphere & rhs)
	: CEffect(rhs)
{
}

_int CLightningSphere::Progress(const _float & fTimeDelta)
{
	m_vScale.x += fTimeDelta*7.f;
	m_vScale.y += fTimeDelta*7.f;
	if (m_vScale.x >= 2.f || m_vScale.y >= 2.f)
		return -1;

	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	return _int();
}

_int CLightningSphere::LateProgress(const _float & fTimeDelta)
{
	CGameObject::ComputeZ(m_pTransform->GetPosition());

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::ALPHA_OBJECT, this)))
		return -1;
	return _int();
}

HRESULT CLightningSphere::Render()
{
	return CEffect::Render();
}

CGameObject * CLightningSphere::Clone(void * pArg)
{
	CLightningSphere*	pInstance = new CLightningSphere(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CLightningSphere Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLightningSphere::Free()
{
	CEffect::Free();
}

CLightningSphere * CLightningSphere::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CLightningSphere*	pInstance = new CLightningSphere(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CLightningSphere Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
