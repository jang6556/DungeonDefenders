#include "stdafx.h"
#include "..\Header\Intro.h"
#include "..\Header\Define.h"
#include "ComponentMgr.h"

_USING(Client)



//IDirect3DVertexBuffer9* VB = nullptr;
//IDirect3DIndexBuffer9*  IB = nullptr;
//IDirect3DTexture9*		Tex = nullptr;
//ID3DXMesh*				Mesh = nullptr;

CIntro::CIntro(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CIntro::CIntro(const CIntro & rhs)
	: CGameObject(rhs.m_pGraphicDev)  
{
	
}

HRESULT CIntro::Initialize()
{
	if(FAILED(CGameObject::AddComponent(INTRO, L"TRIANGLE",(CComponent**)&m_Triangle)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_Transform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TEXTURE", (CComponent**)&m_Texture)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_Renderer)))
		return E_FAIL;

	/*m_Triangle = (CWall*)(CComponentMgr::GetInstance()->AddComponent(L"TRIANGLE", INTRO));*/
	/*m_Transform = (CTransform*)(CComponentMgr::GetInstance()->AddComponent(L"TRANSFORM", SCENESTATIC));	
	m_Texture = (CTexture*)(CComponentMgr::GetInstance()->AddComponent(L"TEXTURE", SCENESTATIC));
	*/

	return NOERROR;
}

_int CIntro::Progress(const _float & fTimeDelta)
{
	/*if (GetAsyncKeyState('W'))
	{
		m_Transform->Move(0, 0, 0.5f);
	}

	if (GetAsyncKeyState('S'))
	{
		m_Transform->Move(0, 0, -0.5f);
	}

	if (GetAsyncKeyState('A'))
	{
		m_Transform->Move(-0.5f, 0, 0);
	}

	if (GetAsyncKeyState('D'))
	{
		m_Transform->Move(0.5f, 0, 0);
	}

	if (GetAsyncKeyState('E'))
	{
		m_Transform->Move(0, -0.5f, 0);
	}

	if (GetAsyncKeyState('Q'))
	{
		m_Transform->Move(0, 0.5f, 0);
	}*/

	if (GetAsyncKeyState('J'))
	{
		m_Transform->RotationY(D3DXToRadian(60),fTimeDelta);
	}

	if (GetAsyncKeyState('L'))
	{
		m_Transform->RotationY(D3DXToRadian(-60), fTimeDelta);
	}

	if (GetAsyncKeyState('I'))
	{
		m_Transform->RotationX(D3DXToRadian(60), fTimeDelta);
	}

	if (GetAsyncKeyState('K'))
	{
		m_Transform->RotationX(D3DXToRadian(-60), fTimeDelta);
	}



	//D3DXMATRIX Rx, Ry;

	//D3DXMatrixRotationX(&Rx,0.f);
	//static float y = 0.f;
	//D3DXMatrixRotationY(&Ry, y);

	////y += fTimeDelta;

	//if (y >= 3.14f*2.f)
	//	y = 0.f;

	//Res = Rx* Ry;

	

	return _int();
}

_int CIntro::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_Renderer->AddRenderGroup(CRenderer::ALPHA_OBJECT, this)))
		return E_FAIL;

	return _int();
}

HRESULT CIntro::Render()
{
	
	m_Texture->SetTexture(0);
	m_Transform->SetTransform();
	//m_pGraphicDev->SetTransform(D3DTS_WORLD, &Res);
	m_Triangle->Render();
	
	return NOERROR;
}

HRESULT CIntro::InitializePrototype()
{
	return NOERROR;
}

CGameObject * CIntro::Clone(void* pArg)
{
	CIntro*	pInstance = new CIntro(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CIntro Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CIntro::Free()
{
	Safe_Release(m_Transform);
	Safe_Release(m_Triangle);
	Safe_Release(m_Texture);
	Safe_Release(m_Renderer);
	CGameObject::Free();
}

CIntro * CIntro::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CIntro*	pInstance = new CIntro(_m_pGraphicDev);

	if (FAILED(pInstance->InitializePrototype()))
	{
		_MSGBOX("CIntro Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

