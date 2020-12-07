#include "stdafx.h"
#include "..\Header\SceneIntro.h"
#include "../Header/Loading.h"
#include "../Header/Scene_Magnus.h"
#include "../Header/BackLogo.h"
#include "../Header/LoadingBarFrame.h"
#include "../Header/LoadingBarContent.h"

_USING(Client)


CSceneIntro::CSceneIntro(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CScene(_m_pGraphicDev)
{
}



HRESULT CSceneIntro::Initialize()
{
	if (FAILED(SetComponentPrototype()))
		return E_FAIL;

	if (FAILED(SetGameObjectPrototype()))
		return E_FAIL;

	if (FAILED(SetGameObject()))
		return E_FAIL;


	m_pLoading = CLoading::Create(m_pGraphicDev, SCENE_MAGNUS);
	if (m_pLoading == nullptr)
		return E_FAIL;
	
	return NOERROR;
}

_int CSceneIntro::Progress(const _float & fTimeDelta)
{	
	m_iComplete = m_pLoading->GetComplete();

	dynamic_cast<CLoadingBarContent*>(CGameObjectMgr::GetInstance()->FindGameObject(INTRO, L"LOADING_BAR"))->SetComplete(m_iComplete, fTimeDelta);
	
	if (GetAsyncKeyState(VK_SPACE) && m_iComplete == 100)
	{		
		CManageMent::GetInstance()->SetCurrScene(CScene_Magnus::Create(m_pGraphicDev), SCENE_MAGNUS);
		return _int();
	}

	return _int(CScene::Progress(fTimeDelta));
}

_int CSceneIntro::LateProgress(const _float & fTimeDelta)
{	
	return _int(CScene::LateProgress(fTimeDelta));
}

HRESULT CSceneIntro::Render()
{	
	return CScene::Render();
}


HRESULT CSceneIntro::SetGameObjectPrototype()
{
	if (FAILED(AddObjectPrototype(INTRO, L"BACKLOGO", CBackLogo::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(AddObjectPrototype(INTRO, L"LOADING_FRAME", CLoadingBarFrame::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(AddObjectPrototype(INTRO, L"LOADING_CONTENT", CLoadingBarContent::Create(m_pGraphicDev))))
		return E_FAIL;

	return NOERROR;
}

HRESULT CSceneIntro::SetComponentPrototype()
{
	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"SHADER_INTRO", CShader::Create(m_pGraphicDev, L"ShaderFile/Shader_Default.fx"), INTRO)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"BACKLOGO", CTexture::Create(m_pGraphicDev, L"Resource/Texture/Logo/Back/Back%d.tga", 18), INTRO)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->AddPrototype(L"LOADINGBAR", CTexture::Create(m_pGraphicDev, L"Resource/Texture/UI/Panel/Panel%d.tga", 11), INTRO)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CSceneIntro::SetGameObject()
{
	if (FAILED(AddObject(INTRO, L"BACKLOGO", INTRO, L"BACKLOGO")))
		return E_FAIL;

	if (FAILED(AddObject(INTRO, L"LOADING_CONTENT", INTRO, L"LOADING_BAR")))
		return E_FAIL;

	if (FAILED(AddObject(INTRO, L"LOADING_FRAME", INTRO, L"LOADING_BAR")))
		return E_FAIL;

	

	return NOERROR;
}

HRESULT CSceneIntro::LoadGameObject()
{
	return NOERROR;
}

CSceneIntro * CSceneIntro::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CSceneIntro* pInstance = new CSceneIntro(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CSceneIntro Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CSceneIntro::Free()
{
	m_pGameObjectMgr->DeleteSceneObject(INTRO);
	m_pComponentMgr->DeleteSceneComponent(INTRO);
	Safe_Release(m_pLoading);
	CScene::Free();
}
