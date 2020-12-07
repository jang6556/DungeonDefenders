#include "stdafx.h"
#include "..\Header\Crystal.h"


_USING(Client)

HRESULT CCrystal::Initialize()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	m_pTransform->SetPosition(D3DXVECTOR3(0.f, 0.f, 0.f));
	

	m_pCrystal.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"CRYSTAL_CORE", &m_pTransform->GetPosition()));
	m_pCrystal.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"CRYSTAL_HEAD", &m_pTransform->GetPosition()));
	m_pCrystal.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"CRYSTAL_RING", &m_pTransform->GetPosition()));

	for (int i = 0; i < m_ColliderData.size(); ++i)
	{
		CCollider* pInstance = nullptr;

		switch (m_ColliderData[i]->iColliderType)
		{
		case CCollider::AABB:
			if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"COLLIDER_AABB", (CComponent**)&pInstance)))
				return E_FAIL;
			break;
		case CCollider::OBB:
			if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"COLLIDER_OBB", (CComponent**)&pInstance)))
				return E_FAIL;
			break;
		case CCollider::SPHERE:
			if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"COLLIDER_SPHERE", (CComponent**)&pInstance)))
				return E_FAIL;
			break;
		}


		pInstance->SetBoneMatrix(m_pTransform->GetWorldMatrix(), &m_ColliderData[i]->matWorld);

		if (pInstance != nullptr)
			m_pCollider.push_back(pInstance);
	}

	return NOERROR;
}

HRESULT CCrystal::Initialize_Prototype()
{
	if (FAILED(CGameObject::LoadColliderData(L"Data/Crystal.dat")))
		return E_FAIL;

	m_iMaxHp = 1000;
	m_iCurrHp = m_iMaxHp;

	return NOERROR;
}
 
CCrystal::CCrystal(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CCrystal::CCrystal(const CCrystal & rhs)
	: CGameObject(rhs), m_iMaxHp(rhs.m_iMaxHp), m_iCurrHp(rhs.m_iCurrHp)
{
}

_int CCrystal::Progress(const _float & fTimeDelta)
{
	for (auto& iter : m_pCrystal)
		iter->Progress(fTimeDelta);

	return _int();
}

_int CCrystal::LateProgress(const _float & fTimeDelta)
{
	if (m_iCurrHp > 0)
	{
		if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::NONALPHA, this)))
			return -1;

		if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::DEPTH_SHADOW, this)))
			return -1;
	}

	for (auto& iter : m_pCrystal)
		iter->LateProgress(fTimeDelta);

	return _int();
}

HRESULT CCrystal::Render()
{
	if (GetAsyncKeyState('C'))
	{
		for (auto& iter : m_pCollider)
			iter->Render();
	}

	for (auto& iter : m_pCrystal)
		iter->Render();

	return NOERROR;
}

HRESULT CCrystal::RenderShadow()
{
	for (auto& iter : m_pCrystal)
		iter->RenderShadow();

	return NOERROR;
}

CGameObject * CCrystal::Clone(void * pArg)
{
	CCrystal*	pInstance = new CCrystal(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CCrystal Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCrystal::Free()
{
	Safe_Release(m_pRenderer);
	Safe_Release(m_pTransform);

	for (auto& iter : m_pCrystal)
		Safe_Release(iter);

	m_pCrystal.clear();

	for (auto& iter : m_pCollider)
		Safe_Release(iter);

	m_pCollider.clear();

	CGameObject::Free();
}

HRESULT CCrystal::SetDamage(_int iDamage)
{
	m_iCurrHp += iDamage;
	if (m_iCurrHp <= 0)
		m_iCurrHp = 0;

	return NOERROR;
}

CCrystal * CCrystal::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CCrystal*	pInstance = new CCrystal(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CCrystal Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
