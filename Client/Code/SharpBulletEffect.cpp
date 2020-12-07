#include "stdafx.h"
#include "..\Header\SharpBulletEffect.h"


_USING(Client)

HRESULT CSharpBulletEffect::Initialize(void * pArg)
{
	if (FAILED(CEffect::AddComponent()))
		return E_FAIL;

	if (FAILED(AddComponent()))
		return E_FAIL;

	m_pParentTransform = (CTransform*)pArg;
	m_pParentTransform->AddRef();
}

HRESULT CSharpBulletEffect::Initialize()
{
	return NOERROR;
}

HRESULT CSharpBulletEffect::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CSharpBulletEffect::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHARPBULLET_EFFECT", (CComponent**)&m_pTexture)))
		return E_FAIL;

	return NOERROR;
}

CSharpBulletEffect::CSharpBulletEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CEffect(_m_pGraphicDev)
{
}

CSharpBulletEffect::CSharpBulletEffect(const CSharpBulletEffect & rhs)
	: CEffect(rhs)
{
}

_int CSharpBulletEffect::Progress(const _float & fTimeDelta)
{
	CGameObject::ComputeZ(m_pTransform->GetPosition());
	return _int();
}

_int CSharpBulletEffect::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::ALPHA_EFFECT, this)))
		return -1;

	return _int();
}

HRESULT CSharpBulletEffect::Render()
{
	LPD3DXEFFECT pEffect = m_pShader->GetEffect();

	if (pEffect == nullptr)
		return E_FAIL;

	D3DXMATRIX matWorld, matView, matProj;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	matWorld = *m_pTransform->GetWorldMatrix();

	D3DXMatrixInverse(&matWorld, nullptr, &matView);

	D3DXVECTOR3 vPostion = m_pParentTransform->GetPosition();

	m_pTransform->SetWorldMatrix(matWorld);
	m_pTransform->Scaling(2, 2, 1);
	m_pTransform->SetPosition(vPostion);

	pEffect->SetMatrix("g_matWorld", m_pTransform->GetWorldMatrix());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);
	pEffect->SetFloat("g_fUV", 0);

	m_pTexture->SetTexture(pEffect, "g_Texture", (int)m_fTimeDelta);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(2);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
}

CGameObject * CSharpBulletEffect::Clone(void * pArg)
{
	CSharpBulletEffect*	pInstance = new CSharpBulletEffect(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CSharpBulletEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CSharpBulletEffect::Free()
{
	Safe_Release(m_pParentTransform);
	CEffect::Free();
}

CSharpBulletEffect * CSharpBulletEffect::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CSharpBulletEffect*	pInstance = new CSharpBulletEffect(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CSharpBulletEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
