#include "stdafx.h"
#include "../Header/MainApp.h"
#include "GraphicDev.h"
#include "ManageMent.h"
#include "../Header/SceneIntro.h"
#include "../Header/Camera.h"
#include "Texture.h"
#include "../Header/CameraDynamic.h"
#include "InputDev.h"
#include "Renderer.h"
#include "../Header/Player.h"
#include "../Header/UI_Header.h"
#include "../Header/Effect_Header.h"
#include "../Header/FireBullet.h"
#include "../Header/CrossBowArrow.h"
#include "../Header/SharpBullet.h"

_USING(Client)

CMainApp::CMainApp()
	:m_pManageMent(CManageMent::GetInstance())
{
	m_pManageMent->AddRef();
}

HRESULT CMainApp::Initilize()
{
	srand(unsigned(time(NULL)));

	if (m_pManageMent == nullptr)
		return E_FAIL;

	if (FAILED(CGraphicDev::GetInstance()->Initialize(g_hWnd, iWINCX, iWINCY, &m_pGraphicDev)))
		return E_FAIL;

	if (FAILED(CInputDev::GetInstance()->Initialize(g_hInst, g_hWnd)))
		return E_FAIL;

	CSoundMgr::GetSceneInst()->Initialize();

	if (FAILED(m_pManageMent->Initialize(SCENEIDEND)))
		return E_FAIL;

	if (FAILED(SetStaticPrototype()))
		return E_FAIL;

	if (FAILED(SetObjectPrototype()))
		return E_FAIL;

	m_pRenderer = (CRenderer*)(CComponentMgr::GetInstance()->AddComponent(L"RENDERER", SCENESTATIC));
	if (m_pRenderer == nullptr)
		return E_FAIL;


	if (FAILED(SetScene(INTRO)))
		return E_FAIL;	

	fps = 0;
	dwTimer = GetTickCount();
	ZeroMemory(szFps, sizeof(szFps));

	return NOERROR;
}

_int CMainApp::Progress(const _float& fTimeDelta)
{
	if (FAILED(m_pManageMent->Progress(fTimeDelta)))
		return -1;

	if (FAILED(CInputDev::GetInstance()->SetInputDev()))
		return -1;

	CSoundMgr::GetSceneInst()->Update();

	return _int();
}

HRESULT CMainApp::Render()
{
	++fps;
	if (GetTickCount() - dwTimer >= 1000)
	{
		dwTimer = GetTickCount();
		wsprintf(szFps, L"FPS: %d", fps);
		fps = 0;
	}

	CGraphicDev::GetInstance()->Render_Begin();

	m_pRenderer->Render();

	//if (FAILED(m_pManageMent->Render()))
	//	return E_FAIL;

	CGraphicDev::GetInstance()->Render_End();

	SetWindowText(g_hWnd, szFps);


	return NOERROR;
}

HRESULT CMainApp::SetScene(SCENEID _ID)
{
	if (m_pManageMent == nullptr)
		return E_FAIL;

	CScene* pScene = nullptr;

	switch (_ID)
	{
	case INTRO:
		pScene = CSceneIntro::Create(m_pGraphicDev);
		break;
	case SCENE_MAGNUS:
		break;
	
	}

	if (pScene == nullptr)
		return E_FAIL;

	if (FAILED(m_pManageMent->SetCurrScene(pScene, INTRO)))
		return E_FAIL;	


	return NOERROR;
}

HRESULT CMainApp::SetStaticPrototype()
{
	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"TRANSFORM", CTransform::Create(m_pGraphicDev), SCENESTATIC)))
		return E_FAIL;	

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"RENDERER", CRenderer::Create(m_pGraphicDev), SCENESTATIC)))
		return E_FAIL;	

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"COLLIDER_AABB", CCollider::Create(m_pGraphicDev, CCollider::AABB), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"COLLIDER_OBB", CCollider::Create(m_pGraphicDev, CCollider::OBB), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"COLLIDER_SPHERE", CCollider::Create(m_pGraphicDev, CCollider::SPHERE), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"RECT_UI", CRectUI::Create(m_pGraphicDev), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"NAVIMESH", CNaviMesh::Create(m_pGraphicDev, L"Data/NaviCell.dat", L"Data/NaviCell_Mon.dat"), SCENESTATIC)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"FRUSTUM", CFrustum::Create(m_pGraphicDev), SCENESTATIC)))
		return E_FAIL;

	


	return NOERROR;
}

HRESULT CMainApp::SetObjectPrototype()
{
	return NOERROR;
}

CMainApp * CMainApp::Create()
{
	CMainApp* pInstance = new CMainApp;

	if (FAILED(pInstance->Initilize()))
	{
		_MSGBOX("CMainApp Created Failed");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CMainApp::Free()
{
	Safe_Release(m_pManageMent);
	Safe_Release(m_pGraphicDev); 
	Safe_Release(m_pRenderer);
	
	CSoundMgr::GetSceneInst()->DestroyInst();

	if (FAILED(CManageMent::Release_Engine()))
		return;
	
}




