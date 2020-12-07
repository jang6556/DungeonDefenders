#include "stdafx.h"
#include "..\Header\BloodEffect.h"

_USING(Client)

HRESULT CBloodEffect::Initialize(void* pArg)
{
	if (FAILED(CEffect::AddComponent()))
		return E_FAIL;

	if (FAILED(AddComponent()))
		return E_FAIL;

	POS_TARGET vPositionColor = *(POS_TARGET*)pArg;

	
	m_pTransform->SetPosition(vPositionColor.vPosition);
	m_vColor = vPositionColor.vTarget;
	return NOERROR;
}

HRESULT CBloodEffect::Initialize()
{
	return NOERROR;
}

HRESULT CBloodEffect::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CBloodEffect::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"BLOODEFFECT", (CComponent**)&m_pTexture)))
		return E_FAIL;

	return NOERROR;
}

CBloodEffect::CBloodEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CEffect(_m_pGraphicDev)
{

}

CBloodEffect::CBloodEffect(const CBloodEffect & rhs)
	: CEffect(rhs)
{

}

_int CBloodEffect::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta*40;
	if (m_fTimeDelta >= 19)
		return -1;

	CGameObject::ComputeZ(m_pTransform->GetPosition());
	return _int();
}

_int CBloodEffect::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::ALPHA_OBJECT, this)))
		return -1;

	return _int();
}

HRESULT CBloodEffect::Render()
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
	m_pTransform->Scaling(3, 3, 1);
	m_pTransform->SetPosition(vPostion);

	pEffect->SetMatrix("g_matWorld", m_pTransform->GetWorldMatrix());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);	
	pEffect->SetVector("g_vColor", &D3DXVECTOR4(m_vColor, 0));

	m_pTexture->SetTexture(pEffect, "g_Texture",(int)m_fTimeDelta);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(1);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;	
}

CGameObject * CBloodEffect::Clone(void * pArg)
{
	CBloodEffect*	pInstance = new CBloodEffect(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CBloodEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBloodEffect::Free()
{
	CEffect::Free();
}

CBloodEffect * CBloodEffect::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CBloodEffect*	pInstance = new CBloodEffect(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CBloodEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
