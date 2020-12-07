#include "stdafx.h"
#include "..\Header\BlueExplosion.h"


_USING(Client)

HRESULT CBlueExplosion::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXVECTOR3 vPosition = *(D3DXVECTOR3*)pArg;

	m_pTransform->SetPosition(vPosition);

	m_iShaderPass = 6;
	m_iTexNum = 0;

	m_vScale = { 3.5f,3.5f,1 };
	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	m_vColor = { 0,0,0 };
	return NOERROR;
}

HRESULT CBlueExplosion::Initialize()
{
	return NOERROR;
}

HRESULT CBlueExplosion::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CBlueExplosion::AddComponent()
{
	if (FAILED(CEffect::AddComponent()))
		return E_FAIL;


	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"BOMB_EXPLOSION", (CComponent**)&m_pTexture)))
		return E_FAIL;

	return NOERROR;
}

CBlueExplosion::CBlueExplosion(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CEffect(_m_pGraphicDev)
{
}

CBlueExplosion::CBlueExplosion(const CBlueExplosion & rhs)
	: CEffect(rhs)
{
}

_int CBlueExplosion::Progress(const _float & fTimeDelta)
{
	m_iTexNum += fTimeDelta * 50;
	if (m_iTexNum >= 16)
		return -1;

	return _int();
}

_int CBlueExplosion::LateProgress(const _float & fTimeDelta)
{
	CGameObject::ComputeZ(m_pTransform->GetPosition());

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::ALPHA_OBJECT, this)))
		return -1;

	return _int();
}

HRESULT CBlueExplosion::Render()
{
	return CEffect::Render();
}

CGameObject * CBlueExplosion::Clone(void * pArg)
{
	CBlueExplosion*	pInstance = new CBlueExplosion(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CBlueExplosion Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBlueExplosion::Free()
{
	CEffect::Free();
}

CBlueExplosion * CBlueExplosion::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CBlueExplosion*	pInstance = new CBlueExplosion(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CBlueExplosion Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
