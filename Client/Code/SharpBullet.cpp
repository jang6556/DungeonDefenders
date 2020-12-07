#include "stdafx.h"
#include "..\Header\SharpBullet.h"
#include "../Header/SharpBulletEffect.h"

_USING(Client)

HRESULT CSharpBullet::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	if (FAILED(CBullet::Initialize()))
		return E_FAIL;

	m_pTransform->Scaling(0.01f, 0.01f, 0.01f);
	m_pTransform->RotationAxis(m_pTransform->GetUp(), D3DXToRadian(-90), 1);

	m_pSharpBulletEffect = (CSharpBulletEffect*)CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"SHARPBULLETEFFECT",m_pTransform);
}

HRESULT CSharpBullet::Initialize_Prototype()
{
	if (FAILED(CGameObject::LoadColliderData(L"Data/CrossBowArrow.dat")))
		return E_FAIL;

	return NOERROR;
}

HRESULT CSharpBullet::AddComponent()
{
	if (FAILED(CBullet::AddComponent()))
		return E_FAIL;


	return NOERROR;
}

CSharpBullet::CSharpBullet(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CBullet(_m_pGraphicDev)
{
}

CSharpBullet::CSharpBullet(const CSharpBullet & rhs)
	: CBullet(rhs)
{
}

_int CSharpBullet::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta;
	if (m_fTimeDelta >= 2.0f)
		return -1;

	m_pTransform->Move(-m_vRight.x, -m_vRight.y, -m_vRight.z, 30.f, fTimeDelta);

	if (-1 == CBullet::CheckCollision(L"SHARPBULLETEXPLOSIVE"))
		return -1;


	m_fDamage = 2.f;
	return _int();
}

_int CSharpBullet::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::ALPHA_OBJECT, this)))
		return -1;

	return _int();
}

HRESULT CSharpBullet::Render()
{
	/*if (FAILED(CBullet::Render()))
		return E_FAIL;*/

	if (GetAsyncKeyState('C'))
	{
		m_pCollider->Render();
	}

	m_pSharpBulletEffect->Render();

	return NOERROR;
}

CGameObject * CSharpBullet::Clone(void * pArg)
{
	CSharpBullet*	pInstance = new CSharpBullet(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CSharpBullet Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CSharpBullet::Free()
{
	Safe_Release(m_pSharpBulletEffect);
	CBullet::Free();
}

CSharpBullet * CSharpBullet::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CSharpBullet*	pInstance = new CSharpBullet(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CSharpBullet Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
