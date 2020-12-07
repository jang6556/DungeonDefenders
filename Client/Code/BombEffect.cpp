#include "stdafx.h"
#include "..\Header\BombEffect.h"


_USING(Client)

HRESULT CBombEffect::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXVECTOR3 vPosition = *(D3DXVECTOR3*)pArg;

	m_pTransform->SetPosition(vPosition);

	m_iShaderPass = 0;
	m_iTexNum = 0;

	m_vScale = { 7.f,7.f,1 };
	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	m_vColor = { 0,0,0 };

	return NOERROR;
}

HRESULT CBombEffect::Initialize()
{
	return NOERROR;
}

HRESULT CBombEffect::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CBombEffect::AddComponent()
{
	if (FAILED(CEffect::AddComponent()))
		return E_FAIL;


	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"BOMB_EXPLOSION", (CComponent**)&m_pTexture)))
		return E_FAIL;

	return NOERROR;
}

CBombEffect::CBombEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CEffect(_m_pGraphicDev)
{
}

CBombEffect::CBombEffect(const CBombEffect & rhs)
	: CEffect(rhs)
{
}

_int CBombEffect::Progress(const _float & fTimeDelta)
{
	m_iTexNum += fTimeDelta*50;
	if (m_iTexNum >= 16)
		return -1;

	return _int();
}

_int CBombEffect::LateProgress(const _float & fTimeDelta)
{
	CGameObject::ComputeZ(m_pTransform->GetPosition());

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::ALPHA_OBJECT, this)))
		return -1;
	
	return _int();
}

HRESULT CBombEffect::Render()
{
	return CEffect::Render();
}

CGameObject * CBombEffect::Clone(void * pArg)
{
	CBombEffect*	pInstance = new CBombEffect(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CBombEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBombEffect::Free()
{
	CEffect::Free();
}

CBombEffect * CBombEffect::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CBombEffect*	pInstance = new CBombEffect(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CBombEffect Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
