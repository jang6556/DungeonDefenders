#include "stdafx.h"
#include "..\Header\CrystalRing.h"


_USING(Client)

HRESULT CCrystalRing::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	m_pTransform->Scaling(0.01f, 0.01f, 0.01f);

	return NOERROR;
}

HRESULT CCrystalRing::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	m_pTransform->Scaling(0.01f, 0.01f, 0.01f);

	D3DXVECTOR3 vPosition = *(D3DXVECTOR3*)pArg;

	m_pTransform->SetPosition(vPosition);
	return NOERROR;
}

HRESULT CCrystalRing::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CCrystalRing::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADER", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"CRYSTAL_RING", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	return NOERROR;
}

CCrystalRing::CCrystalRing(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CCrystalRing::CCrystalRing(const CCrystalRing & rhs)
	: CGameObject(rhs)
{
}

_int CCrystalRing::Progress(const _float & fTimeDelta)
{
	m_pTransform->RotationAxis(m_pTransform->GetUp(), D3DXToRadian(-30), fTimeDelta);
	return _int();
}

_int CCrystalRing::LateProgress(const _float & fTimeDelta)
{
	

	return _int();
}

HRESULT CCrystalRing::Render()
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

	pEffect->Begin(nullptr, 0);
	unsigned long iSubsetNum = m_pMeshStatic->GetSubsetNum();

	for (int i = 0; i < iSubsetNum; ++i)
	{
		m_pMeshStatic->SetShaderMeshTex(pEffect, i, "g_Texture", MESHTEXTURE::MESH_DIFFUSE);

		pEffect->CommitChanges();
		pEffect->BeginPass(0);
		m_pMeshStatic->Render(i);
		pEffect->EndPass();
	}
	pEffect->End();

	return NOERROR;
}

HRESULT CCrystalRing::RenderShadow()
{
	LPD3DXEFFECT pEffect = m_pShader->GetEffect();
	if (pEffect == nullptr)
		return E_FAIL;
	D3DXMATRIX  matView, matProj;

	D3DXVECTOR3 vLightPosition, vLightDirection, vLightUp;

	if (FAILED(CLightMgr::GetInstance()->GetDirectionalLight(CManageMent::GetInstance()->GetCurrSceneID(), &vLightPosition, &vLightDirection, &vLightUp)))
		return E_FAIL;

	D3DXMatrixIdentity(&matView);

	D3DXMatrixLookAtLH(&matView, &vLightPosition, &vLightDirection, &vLightUp);

	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matWorld", m_pTransform->GetWorldMatrix());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);

	pEffect->Begin(nullptr, 0);
	unsigned long iSubsetNum = m_pMeshStatic->GetSubsetNum();

	for (int i = 0; i < iSubsetNum; ++i)
	{
		m_pMeshStatic->SetShaderMeshTex(pEffect, i, "g_Texture", MESHTEXTURE::MESH_DIFFUSE);

		pEffect->CommitChanges();
		pEffect->BeginPass(7);
		m_pMeshStatic->Render(i);
		pEffect->EndPass();
	}
	pEffect->End();

	return NOERROR;
}

CGameObject * CCrystalRing::Clone(void * pArg)
{
	CCrystalRing*	pInstance = new CCrystalRing(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CCrystalRing Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCrystalRing::Free()
{
	Safe_Release(m_pTransform);
	
	Safe_Release(m_pShader);
	Safe_Release(m_pMeshStatic);
	CGameObject::Free();
}

CCrystalRing * CCrystalRing::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CCrystalRing*	pInstance = new CCrystalRing(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CCrystalRing Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
