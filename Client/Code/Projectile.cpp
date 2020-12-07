#include "stdafx.h"
#include "..\Header\Projectile.h"


_USING(Client)

HRESULT CProjectile::Initialize()
{
	return NOERROR;
}

HRESULT CProjectile::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	m_pParentsTransform = (CTransform*)pArg;

	m_pParentsTransform->AddRef();	

	m_pTransform->Scaling(0.7f, 0.7f, 0.7f);

	m_pTransform->Move(-2.f, 0.f, 0.f, 1.f, 1.f);

	return NOERROR;
}

HRESULT CProjectile::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CProjectile::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADER_TOWER_BULLET", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"PROJECTILE", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	
	return NOERROR;
}

CProjectile::CProjectile(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CProjectile::CProjectile(const CProjectile & rhs)
	: CGameObject(rhs)
{
}

_int CProjectile::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CProjectile::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CProjectile::Render()
{
	LPD3DXEFFECT pEffect = m_pShader->GetEffect();
	if (pEffect == nullptr)
		return E_FAIL;
	D3DXMATRIX matWorld, matView, matProj;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	matWorld = *m_pTransform->GetWorldMatrix() * *m_pParentsTransform->GetWorldMatrix();

	pEffect->SetMatrix("g_matWorld", &matWorld);
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);

	pEffect->SetFloat("g_fUV_X", 0);

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

CGameObject * CProjectile::Clone(void * pArg)
{
	CProjectile*	pInstance = new CProjectile(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CProjectile Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CProjectile::Free()
{
	Safe_Release(m_pShader);
	Safe_Release(m_pMeshStatic);
	Safe_Release(m_pTransform);
	Safe_Release(m_pParentsTransform);
	CGameObject::Free();
}

CProjectile * CProjectile::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CProjectile*	pInstance = new CProjectile(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CProjectile Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
