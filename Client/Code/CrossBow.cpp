#include "stdafx.h"
#include "..\Header\CrossBow.h"


_USING(Client)

HRESULT CCrossBow::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	m_pPlayerBone  = (CMeshDynamic*)CGameObjectMgr::GetInstance()->FindComponent(SCENESTATIC, L"PLAYER", L"HUNTRESS");
	m_pPlayerWorld = (CTransform*)CGameObjectMgr::GetInstance()->FindComponent(SCENESTATIC, L"PLAYER", L"TRANSFORM");


	return NOERROR;
}

HRESULT CCrossBow::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CCrossBow::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	m_pTransform->Scaling(0.3f, 0.3f, 0.3f);
	m_pTransform->RotationAxis(m_pTransform->GetLook(), D3DXToRadian(180), 1);
	m_pTransform->RotationAxis(m_pTransform->GetUp(), D3DXToRadian(90), 1);
	m_pTransform->RotationAxis(m_pTransform->GetRight(), D3DXToRadian(-20), 1);
	
	
	m_pTransform->Move(-1.f, 0, 1.f,1,1);
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADER", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"CROSSBOW", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	return NOERROR;
}

CCrossBow::CCrossBow(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CCrossBow::CCrossBow(const CCrossBow & rhs)
	:CGameObject(rhs)
{
}

_int CCrossBow::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CCrossBow::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::NONALPHA, this)))
		return -1;

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::DEPTH_SHADOW, this)))
		return -1;

	return _int();
}

HRESULT CCrossBow::Render()
{
	LPD3DXEFFECT pEffect = m_pShader->GetEffect();
	if (pEffect == nullptr)
		return E_FAIL;
	D3DXMATRIX  matWorld,matView, matProj;


	matWorld = *m_pTransform->GetWorldMatrix() *(*m_pPlayerBone->GetBoneMatrix(L"b_WristR")) * (*m_pPlayerWorld->GetWorldMatrix());

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
		pEffect->BeginPass(0);
		m_pMeshStatic->Render(i);
		pEffect->EndPass();
	}
	pEffect->End();
	return NOERROR;	
}

HRESULT CCrossBow::RenderShadow()
{
	LPD3DXEFFECT pEffect = m_pShader->GetEffect();
	if (pEffect == nullptr)
		return E_FAIL;
	D3DXMATRIX  matWorld, matView, matProj;

	D3DXVECTOR3 vLightPosition, vLightDirection, vLightUp;

	if (FAILED(CLightMgr::GetInstance()->GetDirectionalLight(CManageMent::GetInstance()->GetCurrSceneID(), &vLightPosition, &vLightDirection, &vLightUp)))
		return E_FAIL;

	D3DXMatrixIdentity(&matView);

	D3DXMatrixLookAtLH(&matView, &vLightPosition, &vLightDirection, &vLightUp);
	//D3DXMatrixInverse(&matView, nullptr, &matView);

	matWorld = *m_pTransform->GetWorldMatrix() *(*m_pPlayerBone->GetBoneMatrix(L"b_WristR")) * (*m_pPlayerWorld->GetWorldMatrix());
	
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
		pEffect->BeginPass(7);
		m_pMeshStatic->Render(i);
		pEffect->EndPass();
	}
	pEffect->End();

	return NOERROR;
}

CGameObject * CCrossBow::Clone(void * pArg)
{
	CCrossBow*	pInstance = new CCrossBow(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CCrossBow Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCrossBow::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pShader);
	Safe_Release(m_pMeshStatic);
	CGameObject::Free();
}

CCrossBow * CCrossBow::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CCrossBow*	pInstance = new CCrossBow(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CCrossBow Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
