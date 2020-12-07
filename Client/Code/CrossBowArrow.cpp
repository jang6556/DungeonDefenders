#include "stdafx.h"
#include "..\Header\CrossBowArrow.h"

_USING(Client)

HRESULT CCrossBowArrow::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;	
	
	if (FAILED(CBullet::Initialize()))
		return E_FAIL;

	m_pTransform->Scaling(0.05f, 0.05f, 0.05f);
	m_pTransform->RotationAxis(m_pTransform->GetUp(), D3DXToRadian(180), 1);

	m_vRight *= 2;

	m_fDamage = 1.f;
	
	return NOERROR;
}

HRESULT CCrossBowArrow::Initialize_Prototype()
{
	if (FAILED(CGameObject::LoadColliderData(L"Data/CrossBowArrow.dat")))
		return E_FAIL;

	return NOERROR;
}

HRESULT CCrossBowArrow::AddComponent()
{
	if (FAILED(CBullet::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"CROSSBOWARROW", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	return NOERROR;
}

CCrossBowArrow::CCrossBowArrow(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CBullet(_m_pGraphicDev)
{

}

CCrossBowArrow::CCrossBowArrow(const CCrossBowArrow & rhs)
	: CBullet(rhs)
{

}

_int CCrossBowArrow::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta;
	if (m_fTimeDelta >= 2.0f)
		return -1;

	m_pTransform->Move(-m_vRight.x, -m_vRight.y, -m_vRight.z,40.f, fTimeDelta);
	

	if (-1 == CBullet::CheckCollision(L"SHARPBULLETEXPLOSIVE"))
		return -1;

	return _int();
}

_int CCrossBowArrow::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::NONALPHA, this)))
		return -1;

	return _int();
}

CGameObject * CCrossBowArrow::Clone(void * pArg)
{
	CCrossBowArrow*	pInstance = new CCrossBowArrow(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CCrossBowArrow Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCrossBowArrow::Free()
{
	CBullet::Free();
}

CCrossBowArrow * CCrossBowArrow::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CCrossBowArrow*	pInstance = new CCrossBowArrow(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CCrossBowArrow Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
