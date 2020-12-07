#include "stdafx.h"
#include "..\Header\Shield.h"


_USING(Client)

HRESULT CShield::Initialize()
{
	return NOERROR;
}

HRESULT CShield::Initialize(void * pArg)
{
	if (FAILED(CTower::Initialize()))
		return E_FAIL;

	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXVECTOR3	vPosition = *(D3DXVECTOR3*)pArg;	

	m_pTransform->SetPosition(vPosition);
	m_pTransform->Scaling(0.01f, 0.01f, 0.01f);
	m_pTransform->RotationAxis(m_pTransform->GetUp(), D3DXToRadian(-90), 1.f);

	CTransform* pTransform = (CTransform*)CGameObjectMgr::GetInstance()->FindComponent(SCENESTATIC, L"PLAYER", L"TRANSFORM");
	
	D3DXVECTOR3 vDir = vPosition-pTransform->GetPosition();
	D3DXVec3Normalize(&vDir, &vDir);

	D3DXVECTOR3 vLook = m_pTransform->GetLook();
	D3DXVECTOR3 vRight = m_pTransform->GetRight();
	D3DXVec3Normalize(&vLook, &vLook);
	D3DXVec3Normalize(&vRight, &vRight);

	float fCos = D3DXVec3Dot(&vDir, &vLook);
	fCos = acos(fCos);

	float fCosRight = D3DXVec3Dot(&vDir, &vRight);


	if (fCosRight >= 0)
		m_pTransform->RotationAxis(m_pTransform->GetUp(), fCos, 1.f);
	else
		m_pTransform->RotationAxis(m_pTransform->GetUp(), -fCos, 1.f);

	
	

	m_iMaxHp = 600.f;
	m_iCurrHp = m_iMaxHp;

	return NOERROR;
}

HRESULT CShield::Initialize_Prototype()
{
	if (FAILED(CGameObject::LoadColliderData(L"Data/Shield.dat")))
		return E_FAIL;

	return NOERROR;
}

HRESULT CShield::AddComponent()
{
	if (FAILED(CTower::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHIELD", (CComponent**)&m_pMeshDynamic)))
		return E_FAIL;

	if (FAILED(SetColliderData()))
		return E_FAIL;
	

	

	return NOERROR;
}

CShield::CShield(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CTower(_m_pGraphicDev)
{
}

CShield::CShield(const CShield & rhs)
	: CTower(rhs)
{
}

_int CShield::Progress(const _float & fTimeDelta)
{
	return _int(CTower::Progress(fTimeDelta));
}

_int CShield::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::NONALPHA, this)))
		return -1;

	return _int(CTower::LateProgress(fTimeDelta));
}

HRESULT CShield::Render()
{

	if (FAILED(CTower::Render()))
		return E_FAIL;

	return NOERROR;
}

CGameObject * CShield::Clone(void * pArg)
{
	CShield*	pInstance = new CShield(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CShield Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CShield::Free()
{
	CTower::Free();
}

CShield * CShield::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CShield*	pInstance = new CShield(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CShield Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
