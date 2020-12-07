#include "stdafx.h"
#include "..\Header\StaticLoadObject.h"


_USING(Client)
HRESULT CStaticLoadObject::Initialize()
{
	return NOERROR;
}

HRESULT CStaticLoadObject::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	STATICLOAD LoadData = *(STATICLOAD*)pArg;

	m_pTransform->SetWorldMatrix(LoadData.matWorld);

	if (FAILED(SetMesh((MAPOBJECT)LoadData.iType)))
		return E_FAIL;
	return NOERROR;
}

HRESULT CStaticLoadObject::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CStaticLoadObject::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADER", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"FRUSTUM", (CComponent**)&m_pFrustum)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CStaticLoadObject::SetMesh(MAPOBJECT _iType)
{
	
	switch (_iType)
	{	
	case Client::CStaticLoadObject::SIDESTAIR:
		if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SIDE_STAIR", (CComponent**)&m_pMeshStatic)))
			return E_FAIL;

		m_fRadius = 1000.f;
		break;
	case Client::CStaticLoadObject::SHORT_RAIL:
		if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHORT_RAIL", (CComponent**)&m_pMeshStatic)))
			return E_FAIL;
		break;
	case Client::CStaticLoadObject::ROOF:
		if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"ROOF", (CComponent**)&m_pMeshStatic)))
			return E_FAIL;

		m_fRadius = 1000.f;
		break;
	case Client::CStaticLoadObject::SINGLE_BRIDGE:
		if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SINGLE_BRIDGE", (CComponent**)&m_pMeshStatic)))
			return E_FAIL;
		break;
	case Client::CStaticLoadObject::WALL_BANNER_0:
		if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"WALL_BANNER_0", (CComponent**)&m_pMeshStatic)))
			return E_FAIL;

		m_fRadius = 1000.f;
		break;
	case Client::CStaticLoadObject::WALL_BANNER_1:
		if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"WALL_BANNER_1", (CComponent**)&m_pMeshStatic)))
			return E_FAIL;
		break;
	case Client::CStaticLoadObject::WALL_BANNER_2:
		if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"WALL_BANNER_2", (CComponent**)&m_pMeshStatic)))
			return E_FAIL;
		break;
	case Client::CStaticLoadObject::WALL_BANNER_3:
		if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"WALL_BANNER_3", (CComponent**)&m_pMeshStatic)))
			return E_FAIL;	

		m_fRadius = 1000.f;
		break;
	case Client::CStaticLoadObject::WALL_BANNER_4:
		if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"WALL_BANNER_4", (CComponent**)&m_pMeshStatic)))
			return E_FAIL;
		break;
	case Client::CStaticLoadObject::WALL_BANNER_5:
		if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"WALL_BANNER_5", (CComponent**)&m_pMeshStatic)))
			return E_FAIL;
		break;
	case Client::CStaticLoadObject::WALL_BANNER_6:
		if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"WALL_BANNER_6", (CComponent**)&m_pMeshStatic)))
			return E_FAIL;
		break;

	case Client::CStaticLoadObject::BARREL_0:
		if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"BARREL_0", (CComponent**)&m_pMeshStatic)))
			return E_FAIL;
		break;

	case Client::CStaticLoadObject::BARREL_1:
		if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"BARREL_1", (CComponent**)&m_pMeshStatic)))
			return E_FAIL;
		break;

	case Client::CStaticLoadObject::BARREL_2:
		if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"BARREL_2", (CComponent**)&m_pMeshStatic)))
			return E_FAIL;
		break;

	case Client::CStaticLoadObject::BARREL_3:
		if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"BARREL_3", (CComponent**)&m_pMeshStatic)))
			return E_FAIL;
		break;

	case Client::CStaticLoadObject::TABLE_0:
		if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TABLE_0", (CComponent**)&m_pMeshStatic)))
			return E_FAIL;
		break;

	case Client::CStaticLoadObject::TABLE_1:
		if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TABLE_1", (CComponent**)&m_pMeshStatic)))
			return E_FAIL;
		break;

	case Client::CStaticLoadObject::DOOR:
		if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"DOOR", (CComponent**)&m_pMeshStatic)))
			return E_FAIL;
		break;
	}
	return NOERROR;
}

CStaticLoadObject::CStaticLoadObject(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	: CGameObject(_m_pGraphicDev)
{
}

CStaticLoadObject::CStaticLoadObject(const CStaticLoadObject & rhs)
	: CGameObject(rhs)
{
}

_int CStaticLoadObject::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CStaticLoadObject::LateProgress(const _float & fTimeDelta)
{
	if (m_pFrustum->IsInFrustum(m_pTransform->GetPosition(), m_pTransform, m_fRadius) == true)
	{
		if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::NONALPHA, this)))
			return -1;	

		if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::DEPTH_SHADOW, this)))
			return -1;
	}

	return _int();
}

HRESULT CStaticLoadObject::Render()
{
	LPD3DXEFFECT pEffect = m_pShader->GetEffect();
	if (pEffect == nullptr)
		return E_FAIL;
	D3DXMATRIX  matView, matProj;

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

		pEffect->BeginPass(6);

		m_pMeshStatic->Render(i);
		pEffect->EndPass();
	}
	pEffect->End();

	return NOERROR;
}

HRESULT CStaticLoadObject::RenderShadow()
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

CGameObject * CStaticLoadObject::Clone(void * pArg)
{
	CStaticLoadObject*	pInstance = new CStaticLoadObject(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CStaticLoadObject Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CStaticLoadObject::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pShader);
	Safe_Release(m_pMeshStatic);
	Safe_Release(m_pFrustum);
	CGameObject::Free();
}

CStaticLoadObject * CStaticLoadObject::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CStaticLoadObject*	pInstance = new CStaticLoadObject(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CStaticLoadObject Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
