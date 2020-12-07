#include "stdafx.h"
#include "..\Header\CrystalHead.h"

_USING(Client)

HRESULT CCrystalHead::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	m_pTransform->Scaling(0.01f, 0.01f, 0.01f);

	return NOERROR;
}

HRESULT CCrystalHead::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	m_pTransform->Scaling(0.01f, 0.01f, 0.01f);

	D3DXVECTOR3 vPosition = *(D3DXVECTOR3*)pArg;

	m_pTransform->SetPosition(vPosition);

	return NOERROR;
}

HRESULT CCrystalHead::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CCrystalHead::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADER", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"CRYSTAL_HEAD", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	return NOERROR;
}

CCrystalHead::CCrystalHead(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CCrystalHead::CCrystalHead(const CCrystalHead & rhs)
	: CGameObject(rhs)
{
}

_int CCrystalHead::Progress(const _float & fTimeDelta)
{
	m_pTransform->RotationAxis(m_pTransform->GetUp(), D3DXToRadian(15), fTimeDelta);
	return _int();
}

_int CCrystalHead::LateProgress(const _float & fTimeDelta)
{
	

	return _int();
}

HRESULT CCrystalHead::Render()
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

HRESULT CCrystalHead::RenderShadow()
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

CGameObject * CCrystalHead::Clone(void * pArg)
{
	CCrystalHead*	pInstance = new CCrystalHead(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CCrystalHead Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCrystalHead::Free()
{
	Safe_Release(m_pTransform);	
	Safe_Release(m_pShader);
	Safe_Release(m_pMeshStatic);
	CGameObject::Free();
}

CCrystalHead * CCrystalHead::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CCrystalHead*	pInstance = new CCrystalHead(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CCrystalHead Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
