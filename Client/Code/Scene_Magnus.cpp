#include "stdafx.h"
#include "..\Header\Scene_Magnus.h"
#include "..\Header\SceneIntro.h"
#include "..\Header\Intro.h"
#include "../Header/StageTerrain.h"
#include "Wall.h"
#include "CameraObject.h"
#include "Terrain.h"
#include "../Header/SkyBox.h"
#include "Cube.h"

#include "../Header/CrossBowArrow.h"
#include "../Header/TresureChest.h"
#include "../Header/DarkElfArrow.h"

#include "../Header/Monster_Magnus_Header.h"
#include "../Header/MagnusQuater_Header.h"


_USING(Client)

HRESULT CScene_Magnus::SetGameObjectPrototype()
{
	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"MAGNUSQUARTER", CMagnusQuarter::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"CROSSSTAIR", CCrossStair::Create(m_pGraphicDev))))
		return E_FAIL;			  

	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"LONGSTAIR", CLongStair::Create(m_pGraphicDev))))
		return E_FAIL;			  
								  
	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"SHORTSTAIR", CShortStair::Create(m_pGraphicDev))))
		return E_FAIL;			  
								  
	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"DEMON", CDemon::Create(m_pGraphicDev))))
		return E_FAIL;			  
								  
	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"DARKELFARCHER", CDarkElfArcher::Create(m_pGraphicDev))))
		return E_FAIL;			  
								  
	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"DARKELFARROW", CDarkElfArrow::Create(m_pGraphicDev))))
		return E_FAIL;			  
								  
	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"TRESURECHEST", CTresureChest::Create(m_pGraphicDev))))
		return E_FAIL;			  
								  
	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"ARCANEPAD", CArcanePad::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"GOBLIN", CGoblin::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"KOBOLD", CKobold::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"ORCBRUISER", COrcBruiser::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"MAGNUS_CONTROLLER", CMagnusController::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"CENTER_ARCH", CCenterArch::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"CENTER_WALL", CCenterWall::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"BRIDGE_WALL", CBridgeWall::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"SET_RAIL", CRailSet::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"LONG_RAIL", CLongRail::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"DOUBLE_RAIL", CDoubleRail::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"CRYSTAL_STAFF", CCrystalStaff::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"WALLTORCH_ANGLE", CWallTorchAngle::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"WALLTORCH_DOUBLE", CWallTorchDouble::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"WALLTORCH_HEIGHT", CWallTorchHeight::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"WALLTORCH_LONG", CWallTorchLong::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"WALLTORCH_SINGLE", CWallTorchSingle::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"WALLTORCH_TRIPLE", CWallTorchTriple::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"STATIC_LOAD", CStaticLoadObject::Create(m_pGraphicDev))))
		return E_FAIL;

	if (FAILED(AddObjectPrototype(SCENE_MAGNUS, L"LARGE_CRYSTALSTAFF", CLargeCrystalStaff::Create(m_pGraphicDev))))
		return E_FAIL;

	return NOERROR;
}

HRESULT CScene_Magnus::SetComponentPrototype()
{
	return NOERROR;
}

HRESULT CScene_Magnus::SetGameObject()
{
	if (FAILED(AddObject(SCENESTATIC, L"PLAYER", SCENESTATIC, L"PLAYER")))
		return E_FAIL;

	if (FAILED(AddObject(SCENESTATIC, L"CROSSBOW", SCENESTATIC, L"CROSSBOW")))
		return E_FAIL;

	if (FAILED(AddObject(SCENESTATIC, L"CRYSTAL", SCENESTATIC, L"CRYSTAL")))
		return E_FAIL;

	if (FAILED(AddObject(SCENESTATIC, L"CAMERA", SCENESTATIC, L"CAMERA", &CCameraObject::CAMERAINFO(D3DXVECTOR3(0.f, 5.f, -5.f), D3DXVECTOR3(0.f, 0.f, 0.f), D3DXVECTOR3(0.f, 1.f, 0.f), D3DXToRadian(90), (float)iWINCX / (float)iWINCY, 0.1f, 1000.f))))
		return E_FAIL;		

	if (FAILED(AddObject(SCENESTATIC, L"STAT_UI_PANEL", SCENESTATIC, L"STAT_UI_PANEL")))
		return E_FAIL;

	if (FAILED(AddObject(SCENESTATIC, L"WAVE_PANEL", SCENESTATIC, L"PANEL")))
		return E_FAIL;

	if (FAILED(AddObject(SCENESTATIC, L"PANEL", SCENESTATIC, L"PANEL")))
		return E_FAIL;	

	if (FAILED(AddObject(SCENESTATIC, L"MOUSE_POINT", SCENESTATIC, L"MOUSE_POINT")))
		return E_FAIL;
	
	if (FAILED(AddObject(SCENE_MAGNUS, L"MAGNUS_CONTROLLER", SCENE_MAGNUS, L"CONTROLLER")))
		return E_FAIL;

	if (FAILED(AddObject(SCENESTATIC, L"LAVA_EFFECT", SCENESTATIC, L"LAVA_EFFECT",&D3DXVECTOR3(0,0,6))))
		return E_FAIL;

	if (FAILED(AddObject(SCENESTATIC, L"LAVA_FOG_EFFECT", SCENESTATIC, L"LAVA_FOG_EFFECT", &D3DXVECTOR3(0, 0, -6))))
		return E_FAIL;

	D3DLIGHT9 Light;

	ZeroMemory(&Light, sizeof(D3DLIGHT9));

	Light.Type = D3DLIGHT_DIRECTIONAL;
	Light.Direction = D3DXVECTOR3(0.0f, -1.f, -0.1f);

	Light.Diffuse	= D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.f);
	Light.Ambient	= D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.f);
	Light.Specular  = Light.Diffuse;

	if (FAILED(CLightMgr::GetInstance()->AddLight(SCENE_MAGNUS, m_pGraphicDev, &Light)))
		return E_FAIL;

	ZeroMemory(&Light, sizeof(D3DLIGHT9));

	Light.Type = D3DLIGHT_POINT;
	Light.Position = D3DXVECTOR3(0.f, 0.f, 0.f);
	Light.Range = 10.f;

	Light.Diffuse = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	Light.Ambient = D3DXCOLOR(0.5f, 0.1f, 0.1f, 1.f);
	Light.Specular = Light.Diffuse;

	if (FAILED(CLightMgr::GetInstance()->AddLight(SCENE_MAGNUS, m_pGraphicDev, &Light)))
		return E_FAIL;

	ZeroMemory(&Light, sizeof(D3DLIGHT9));

	Light.Type = D3DLIGHT_POINT;
	Light.Position = D3DXVECTOR3(0.f, 0.f, 0.f);
	Light.Range = 5.f;

	Light.Diffuse = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);
	Light.Ambient = D3DXCOLOR(0.1f, 0.5f, 0.1f, 1.f);
	Light.Specular = Light.Diffuse;

	if (FAILED(CLightMgr::GetInstance()->AddLight(SCENE_MAGNUS, m_pGraphicDev, &Light)))
		return E_FAIL;
	
	return NOERROR;
}

HRESULT CScene_Magnus::LoadGameObject()
{
	HANDLE	hFile = CreateFile(L"Data/MapObject.dat",
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	DWORD		dwByte;

	while (1)
	{
		OBJSAVEDATA SaveData;
		CTransform* pTransform;
		ReadFile(hFile, &SaveData, sizeof(OBJSAVEDATA), &dwByte, NULL);
		if (dwByte == 0)
			break;

		switch (SaveData.ObjectType)
		{
		case MAGUNUSSQUARTER:
			if (FAILED(AddObject(SCENE_MAGNUS, L"MAGNUSQUARTER", SCENE_MAGNUS, L"MAGNUSQUARTER")))
				return E_FAIL;
			pTransform = (CTransform*)CGameObjectMgr::GetInstance()->FindComponent(SCENE_MAGNUS, L"MAGNUSQUARTER", L"TRANSFORM", -1);
			pTransform->SetWorldMatrix(SaveData.matWorld);
			break;
		case CROSSSTAIR:
			if (FAILED(AddObject(SCENE_MAGNUS, L"CROSSSTAIR", SCENE_MAGNUS, L"CROSSSTAIR")))
				return E_FAIL;
			pTransform = (CTransform*)CGameObjectMgr::GetInstance()->FindComponent(SCENE_MAGNUS, L"CROSSSTAIR", L"TRANSFORM", -1);
			pTransform->SetWorldMatrix(SaveData.matWorld);
			break;
		case LONGSTAIR:
			if (FAILED(AddObject(SCENE_MAGNUS, L"LONGSTAIR", SCENE_MAGNUS, L"LONGSTAIR")))
				return E_FAIL;
			pTransform = (CTransform*)CGameObjectMgr::GetInstance()->FindComponent(SCENE_MAGNUS, L"LONGSTAIR", L"TRANSFORM", -1);
			pTransform->SetWorldMatrix(SaveData.matWorld);
			break;
		case SIDESTAIR:
			if (FAILED(AddObject(SCENE_MAGNUS, L"STATIC_LOAD", SCENE_MAGNUS, L"MAGNUS_MAP_OBJECT", &STATICLOAD(SaveData.matWorld, SaveData.ObjectType))))
				return E_FAIL;
			break;
		case SHORTSTAIR:
			if (FAILED(AddObject(SCENE_MAGNUS, L"SHORTSTAIR", SCENE_MAGNUS, L"SHORTSTAIR")))
				return E_FAIL;
			pTransform = (CTransform*)CGameObjectMgr::GetInstance()->FindComponent(SCENE_MAGNUS, L"SHORTSTAIR", L"TRANSFORM", -1);
			pTransform->SetWorldMatrix(SaveData.matWorld);
			break;
		case TRESURECHEST:
			if (FAILED(AddObject(SCENE_MAGNUS, L"TRESURECHEST", SCENE_MAGNUS, L"TRESURECHEST", &SaveData.matWorld)))
				return E_FAIL;			
			break;

		case ARCANEPAD:
			if (FAILED(AddObject(SCENE_MAGNUS, L"ARCANEPAD", SCENE_MAGNUS, L"ARCANEPAD",&SaveData.matWorld)))
				return E_FAIL;			
			break;

		case CENTER_ARCH:
			if (FAILED(AddObject(SCENE_MAGNUS, L"CENTER_ARCH", SCENE_MAGNUS, L"MAGNUS_MAP_OBJECT", &SaveData.matWorld)))
				return E_FAIL;
			break;

		case CENTER_UP:			
			break;

		case CENTER_WALL:
			if (FAILED(AddObject(SCENE_MAGNUS, L"CENTER_WALL", SCENE_MAGNUS, L"MAGNUS_MAP_OBJECT", &SaveData.matWorld)))
				return E_FAIL;
			break;

		case SET_RAIL:
			if (FAILED(AddObject(SCENE_MAGNUS, L"SET_RAIL", SCENE_MAGNUS, L"MAGNUS_MAP_OBJECT", &SaveData.matWorld)))
				return E_FAIL;
			break;

		case LONG_RAIL:
			if (FAILED(AddObject(SCENE_MAGNUS, L"LONG_RAIL", SCENE_MAGNUS, L"MAGNUS_MAP_OBJECT", &SaveData.matWorld)))
				return E_FAIL;
			break;

		case DOUBLE_RAIL:
			if (FAILED(AddObject(SCENE_MAGNUS, L"DOUBLE_RAIL", SCENE_MAGNUS, L"MAGNUS_MAP_OBJECT", &SaveData.matWorld)))
				return E_FAIL;
			break;

		case BRIDGE_WALL:
			if (FAILED(AddObject(SCENE_MAGNUS, L"BRIDGE_WALL", SCENE_MAGNUS, L"MAGNUS_MAP_OBJECT", &SaveData.matWorld)))
				return E_FAIL;
			break;

		case CRYSTAL_STAFF:
			if (FAILED(AddObject(SCENE_MAGNUS, L"CRYSTAL_STAFF", SCENE_MAGNUS, L"MAGNUS_MAP_OBJECT", &SaveData.matWorld)))
				return E_FAIL;
			break;

		case WALLTORCH_DOUBLE:
			if (FAILED(AddObject(SCENE_MAGNUS, L"WALLTORCH_DOUBLE", SCENE_MAGNUS, L"MAGNUS_MAP_OBJECT", &SaveData.matWorld)))
				return E_FAIL;
			break;

		case WALLTORCH_TRIPLE:
			if (FAILED(AddObject(SCENE_MAGNUS, L"WALLTORCH_TRIPLE", SCENE_MAGNUS, L"MAGNUS_MAP_OBJECT", &SaveData.matWorld)))
				return E_FAIL;
			break;

		case WALLTORCH_ANGLE:
			if (FAILED(AddObject(SCENE_MAGNUS, L"WALLTORCH_ANGLE", SCENE_MAGNUS, L"MAGNUS_MAP_OBJECT", &SaveData.matWorld)))
				return E_FAIL;
			break;

		case WALLTORCH_HEIGHT:
			if (FAILED(AddObject(SCENE_MAGNUS, L"WALLTORCH_HEIGHT", SCENE_MAGNUS, L"MAGNUS_MAP_OBJECT", &SaveData.matWorld)))
				return E_FAIL;
			break;

		case WALLTORCH_SINGLE:
			if (FAILED(AddObject(SCENE_MAGNUS, L"WALLTORCH_SINGLE", SCENE_MAGNUS, L"MAGNUS_MAP_OBJECT", &SaveData.matWorld)))
				return E_FAIL;
			break;

		case WALLTORCH_LONG:
			if (FAILED(AddObject(SCENE_MAGNUS, L"WALLTORCH_LONG", SCENE_MAGNUS, L"MAGNUS_MAP_OBJECT", &SaveData.matWorld)))
				return E_FAIL;
			break;

		case SHORT_RAIL:			
		case ROOF:		
		case SINGLE_BRIDGE:		
		case WALL_BANNER_0:		
		case WALL_BANNER_1:		
		case WALL_BANNER_2:			
		case WALL_BANNER_3:
		case WALL_BANNER_4:			
		case WALL_BANNER_5:			
		case WALL_BANNER_6:
		case BARREL_0:
		case BARREL_1:
		case BARREL_2:
		case BARREL_3:
		case TABLE_0:
		case TABLE_1:
		case DOOR:
			if (FAILED(AddObject(SCENE_MAGNUS, L"STATIC_LOAD", SCENE_MAGNUS, L"MAGNUS_MAP_OBJECT", &STATICLOAD(SaveData.matWorld,SaveData.ObjectType))))
				return E_FAIL;
			break;	
		case LARGE_CRYSTALSTAFF:
			if (FAILED(AddObject(SCENE_MAGNUS, L"LARGE_CRYSTALSTAFF", SCENE_MAGNUS, L"MAGNUS_MAP_OBJECT", &SaveData.matWorld)))
				return E_FAIL;
			break;
		case LAVA_EFFECT_0:
			if (FAILED(AddObject(SCENESTATIC, L"LAVA_EFFECT", SCENE_MAGNUS, L"MAGNUS_MAP_OBJECT", &SaveData.matWorld)))
				return E_FAIL;
			break;
		case LAVA_EFFECT_1:			 
			if (FAILED(AddObject(SCENESTATIC, L"LAVA_FOG_EFFECT", SCENE_MAGNUS, L"MAGNUS_MAP_OBJECT", &SaveData.matWorld)))
				return E_FAIL;
			
			SaveData.matWorld.m[3][2] *= -1.f;

			if (FAILED(AddObject(SCENESTATIC, L"LAVA_FOG_EFFECT", SCENE_MAGNUS, L"MAGNUS_MAP_OBJECT", &SaveData.matWorld)))
				return E_FAIL;
			break;
		}
	}
	CloseHandle(hFile);

	

	return NOERROR;
}

CScene_Magnus::CScene_Magnus(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CScene(_m_pGraphicDev)
{
}

HRESULT CScene_Magnus::Initialize()
{
	if (FAILED(SetComponentPrototype()))
		return E_FAIL;

	if (FAILED(SetGameObjectPrototype()))
		return E_FAIL;

	if (FAILED(SetGameObject()))
		return E_FAIL;

	if (FAILED(LoadGameObject()))
		return E_FAIL;


	CSoundMgr::GetSceneInst()->PlayBGM("kurastsewer.mp3");

	return NOERROR;
}

_int CScene_Magnus::Progress(const _float & fTimeDelta)
{
	m_pGameObjectMgr->Progress(fTimeDelta);

	return _int();
}

_int CScene_Magnus::LateProgress(const _float & fTimeDelta)
{
	m_pGameObjectMgr->LateProgress(fTimeDelta);

	return _int();
}

HRESULT CScene_Magnus::Render()
{
	return NOERROR;
}

CScene_Magnus * CScene_Magnus::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CScene_Magnus* pInstance = new CScene_Magnus(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CScene_Magnus Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CScene_Magnus::Free()
{
	CLightMgr::GetInstance()->DeleteSceneLight(SCENE_MAGNUS);
	CSoundMgr::GetSceneInst()->StopAll();
	CScene::Free();
}
