#include "stdafx.h"
#include "..\Header\MissileTowerBullet.h"


_USING(Client)
HRESULT CMissileTowerBullet::Initialize()
{
	return NOERROR;
}

HRESULT CMissileTowerBullet::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	if (FAILED(CTowerBullet::Initialize(pArg)))
		return E_FAIL;	

	m_pTransform->Scaling(0.03f, 0.03f, 0.03f);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
	
	m_pTransform->RotationAxis(m_pTransform->GetUp(), D3DXToRadian(-90), 1);
	m_iShaderPass = 0;

	m_pCollider->SetBoneMatrix(m_pTransform->GetWorldMatrix(), &m_ColliderData[0]->matWorld);
	m_pColliderExplosion->SetBoneMatrix(m_pTransform->GetWorldMatrix(), &m_ColliderData[1]->matWorld);

	m_fDamge = 1.2f;

	return NOERROR;
}

HRESULT CMissileTowerBullet::Initialize_Prototype()
{
	if (FAILED(CGameObject::LoadColliderData(L"Data/MissileBullet.dat")))
		return E_FAIL;

	return NOERROR;
}

HRESULT CMissileTowerBullet::AddComponent()
{
	if (FAILED(CTowerBullet::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"PROJECTILE", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	return NOERROR;
}

CMissileTowerBullet::CMissileTowerBullet(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CTowerBullet(_m_pGraphicDev)
{
}

CMissileTowerBullet::CMissileTowerBullet(const CMissileTowerBullet & rhs)
	: CTowerBullet(rhs)
{
}

_int CMissileTowerBullet::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta;
	if (m_fTimeDelta >= 1.f)
		m_fTimeDelta = 1;

	m_pTransform->MoveSide(30, fTimeDelta);	

	return _int();
}

_int CMissileTowerBullet::LateProgress(const _float & fTimeDelta)
{
	if (CTowerBullet::bCheckCollision() == true)
		if (-1 == CTowerBullet::Explosion())
			return -1;

	CGameObject::ComputeZ(m_pTransform->GetPosition());

	if (m_fTimeDelta>=0.05f &&FAILED(m_pRenderer->AddRenderGroup(CRenderer::ALPHA_OBJECT, this)))
		return -1;

	return _int();
}

HRESULT CMissileTowerBullet::Render()
{	
	if (FAILED(CTowerBullet::Render()))
		return E_FAIL;	

	return NOERROR;
}

CGameObject * CMissileTowerBullet::Clone(void * pArg)
{
	CMissileTowerBullet*	pInstance = new CMissileTowerBullet(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CMissileTowerBullet Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMissileTowerBullet::Free()
{ 
	CTowerBullet::Free();
}

CMissileTowerBullet * CMissileTowerBullet::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CMissileTowerBullet*	pInstance = new CMissileTowerBullet(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CMissileTowerBullet Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
