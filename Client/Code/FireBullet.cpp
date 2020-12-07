#include "stdafx.h"
#include "..\Header\FireBullet.h"


_USING(Client)


HRESULT CFireBullet::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	if (FAILED(CBullet::Initialize()))
		return E_FAIL;

	m_pTransform->Scaling(0.0025f, 0.0025f, 0.0025f);

	D3DXVECTOR3 vPosition = m_pTransform->GetPosition();
	vPosition -= m_vRight*2.0f;
	m_vRight += D3DXVECTOR3(rand() % 30 / 100.f-0.15f, rand() % 30 / 100.f - 0.15f, rand() % 30 / 100.f - 0.15f);

	D3DXVec3Normalize(&m_vRight, &m_vRight);

	CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"FIREBULLET_FIRE", SCENESTATIC, L"FIREBULLET_FIRE", &vPosition);

	fBulletSpeed = 30.f + rand() % 3;

	m_fDamage = 0.3f;

	return NOERROR;
}

HRESULT CFireBullet::Initialize_Prototype()
{
	if (FAILED(CGameObject::LoadColliderData(L"Data/CrossBowArrow.dat")))
		return E_FAIL;

	return NOERROR;
}

HRESULT CFireBullet::AddComponent()
{
	if (FAILED(CBullet::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"FIREBULLET", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	

	return NOERROR;
}

CFireBullet::CFireBullet(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CBullet(_m_pGraphicDev)
{
}

CFireBullet::CFireBullet(const CFireBullet & rhs)
	: CBullet(rhs)
{
}

_int CFireBullet::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta;
	if (m_fTimeDelta >= 0.5f)
		return -1;

	m_pTransform->RotationAxis(m_pTransform->GetRight(), D3DXToRadian(360), fTimeDelta*5.f);
	m_pTransform->Move(-m_vRight.x, -m_vRight.y, -m_vRight.z, fBulletSpeed, fTimeDelta);


	if (-1 == CBullet::CheckCollision(L"FIREBULLETEFFECT"))
		return -1;

	return _int();
}

_int CFireBullet::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::NONALPHA, this)))
		return -1;
	
	return _int();
}

CGameObject * CFireBullet::Clone(void * pArg)
{
	CFireBullet*	pInstance = new CFireBullet(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CFireBullet Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CFireBullet::Free()
{
	CBullet::Free();
}

CFireBullet * CFireBullet::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CFireBullet*	pInstance = new CFireBullet(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CFireBullet Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
