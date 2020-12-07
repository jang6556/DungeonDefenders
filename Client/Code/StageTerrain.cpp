#include "stdafx.h"
#include "../Header/StageTerrain.h"
#include "ComponentMgr.h"
#include "../Header/Define.h"

_USING(Client)
CStageTerrain::CStageTerrain(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{

}

CStageTerrain::CStageTerrain(const CStageTerrain & rhs)
	:CGameObject(rhs),m_Transform(rhs.m_Transform),m_Terrain(rhs.m_Terrain),m_Renderer(rhs.m_Renderer), m_Texture(rhs.m_Texture)
{
	m_Renderer->AddRef();
}

HRESULT CStageTerrain::AddComponent()
{
	m_Transform = (CTransform*)(CComponentMgr::GetInstance()->AddComponent(L"TRANSFORM", SCENESTATIC));
	m_Terrain	= (CTerrain*)(CComponentMgr::GetInstance()->AddComponent(L"TERRAIN", INTRO));

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_Renderer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TERRAINTEXTURE", (CComponent**)&m_Texture)))
		return E_FAIL;

	if (m_Terrain == nullptr || m_Transform == nullptr)
		return E_FAIL;

	return NOERROR;
}

HRESULT CStageTerrain::SetRenderState()
{
	if (m_pGraphicDev == nullptr)
		return E_FAIL;

	m_pGraphicDev->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pGraphicDev->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	m_pGraphicDev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pGraphicDev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pGraphicDev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	return NOERROR;
}

HRESULT CStageTerrain::ResetRenderState()
{
	if (m_pGraphicDev == nullptr)
		return E_FAIL;

	m_pGraphicDev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_NONE);
	m_pGraphicDev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_NONE);
	m_pGraphicDev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

	return NOERROR;
}
 
HRESULT CStageTerrain::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	return NOERROR;
}

_int CStageTerrain::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CStageTerrain::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_Renderer->AddRenderGroup(CRenderer::ALPHA_OBJECT, this)))
		return E_FAIL;

	return _int();
}

HRESULT CStageTerrain::Render()
{
	SetRenderState();

	m_Texture->SetTexture(0);
	m_Transform->SetTransform();
	//m_pGraphicDev->SetTransform(D3DTS_WORLD, &Res);
	m_Terrain->Render();

	ResetRenderState();

	return NOERROR;
}

CGameObject * CStageTerrain::Clone(void * pArg)
{
	return new CStageTerrain(*this);
}

void CStageTerrain::Free()
{
	Safe_Release(m_Terrain);
	Safe_Release(m_Transform);
	Safe_Release(m_Renderer);
	Safe_Release(m_Texture);
	CGameObject::Free();
}

CStageTerrain * CStageTerrain::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CStageTerrain*	pInstance = new CStageTerrain(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CStageTerrain Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
