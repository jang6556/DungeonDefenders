#include "stdafx.h"
#include "..\Header\YellowExplosion.h"


_USING(Client)
HRESULT CYellowExplosion::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXVECTOR3 vPosition = *(D3DXVECTOR3*)pArg;

	m_pTransform->SetPosition(vPosition);

	m_iShaderPass = 7;
	m_iTexNum = 0;

	m_vScale = { 3.5f,3.5f,1 };
	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	m_vColor = { 0,0,0 };
	return NOERROR;
}

HRESULT CYellowExplosion::Initialize()
{
	return NOERROR;
}

HRESULT CYellowExplosion::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CYellowExplosion::AddComponent()
{
	if (FAILED(CEffect::AddComponent()))
		return E_FAIL;


	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"BOMB_EXPLOSION", (CComponent**)&m_pTexture)))
		return E_FAIL;
	return NOERROR;
}

CYellowExplosion::CYellowExplosion(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CEffect(_m_pGraphicDev)
{
}

CYellowExplosion::CYellowExplosion(const CYellowExplosion & rhs)
	: CEffect(rhs)
{
}

_int CYellowExplosion::Progress(const _float & fTimeDelta)
{
	m_iTexNum += fTimeDelta * 50;
	if (m_iTexNum >= 16)
		return -1;

	return _int();	
}

_int CYellowExplosion::LateProgress(const _float & fTimeDelta)
{
	CGameObject::ComputeZ(m_pTransform->GetPosition());

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::ALPHA_OBJECT, this)))
		return -1;
	return _int();
}

HRESULT CYellowExplosion::Render()
{
	return CEffect::Render();
}

CGameObject * CYellowExplosion::Clone(void * pArg)
{
	CYellowExplosion*	pInstance = new CYellowExplosion(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CYellowExplosion Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CYellowExplosion::Free()
{
	CEffect::Free();
}

CYellowExplosion * CYellowExplosion::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CYellowExplosion*	pInstance = new CYellowExplosion(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CYellowExplosion Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
