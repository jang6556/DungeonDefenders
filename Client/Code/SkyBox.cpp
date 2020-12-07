#include "stdafx.h"
#include "..\Header\SkyBox.h"
#include "ComponentMgr.h"
#include "../Header/Define.h"
#include "GameObjectMgr.h"
_USING(Client)


CSkyBox::CSkyBox(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CSkyBox::CSkyBox(const CSkyBox & rhs)
	:CGameObject(rhs)
{
}

HRESULT CSkyBox::SetRenderState()
{
	if (m_pGraphicDev == nullptr)
		return E_FAIL;

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	return NOERROR;
}

HRESULT CSkyBox::ResetRenderState()
{
	if (m_pGraphicDev == nullptr)
		return E_FAIL;

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	return NOERROR;
}

HRESULT CSkyBox::Initialize()
{
	if (FAILED(CGameObject::AddComponent(INTRO, L"CUBE", (CComponent**)&m_Cube)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_Transform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SKYBOXTEX", (CComponent**)&m_Texture)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_Renderer)))
		return E_FAIL;

	return NOERROR;
}

_int CSkyBox::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CSkyBox::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_Renderer->AddRenderGroup(CRenderer::PRIORITY, this)))
		return E_FAIL;
	return _int();
}

HRESULT CSkyBox::Render()
{
	CGameObject* pCamera = CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"CAMERA");
	CTransform* pCameraWorld = nullptr;

	if (pCamera != nullptr)
	{
		pCameraWorld= (CTransform*)pCamera->GetComponent(L"TRANSFORM");		
	}

	SetRenderState();

	m_Texture->SetTexture(0);
	m_Transform->SetTransform();
	//m_pGraphicDev->SetTransform(D3DTS_WORLD, &Res);
	m_Cube->Render(pCameraWorld);


	ResetRenderState();
	return NOERROR;
}

HRESULT CSkyBox::InitializePrototype()
{
	

	return NOERROR;
}

CGameObject * CSkyBox::Clone(void * pArg)
{
	CSkyBox*	pInstance = new CSkyBox(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CSkyBox Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CSkyBox::Free()
{	
	Safe_Release(m_Transform);
	Safe_Release(m_Cube);
	Safe_Release(m_Texture);
	Safe_Release(m_Renderer);

	CGameObject::Free();
}

CSkyBox * CSkyBox::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CSkyBox*	pInstance = new CSkyBox(_m_pGraphicDev);

	if (FAILED(pInstance->InitializePrototype()))
	{
		_MSGBOX("CSkyBox Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
