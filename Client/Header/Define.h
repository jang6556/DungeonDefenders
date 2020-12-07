#pragma once

const int iWINCX = 1280;
const int iWINCY = 720;

extern HWND g_hWnd;
extern HINSTANCE g_hInst;

enum SCENEID{SCENESTATIC,INTRO,SCENE_MAGNUS, SCENEIDEND};
enum ADDTIONALOBJ{ LIGHT, CAMERA, ADDTIONALOBJEND};

typedef struct tagSkilInfo
{
	float	fTimeDelta;
	bool	IsCoolTime;
	float	fCoolTime;
	float	fConsumeMp;
	float	fBuildTime;
	float	fCurrBuildTime;

	tagSkilInfo()
	{
		fTimeDelta = 0.f;
		IsCoolTime = false;
		fCoolTime = 0.f;
		fConsumeMp = 0.f;
		fBuildTime = 0.f;
		fCurrBuildTime = 0.f;

	}
}SKILLINFO;

typedef struct tagPosTarget
{
	D3DXVECTOR3 vPosition;
	D3DXVECTOR3 vTarget;
	tagPosTarget() {}

	tagPosTarget(D3DXVECTOR3 _vPosition, D3DXVECTOR3 _vTarget)
		:vPosition(_vPosition ), vTarget(_vTarget)
	{

	}

}POS_TARGET;

typedef struct tagDragPanel
{
	D3DXVECTOR2  vPosition;
	D3DXVECTOR2* pMovePosition;
	D3DXVECTOR3  vColor;
	tagDragPanel() {}

	tagDragPanel(D3DXVECTOR2 _vPosition, D3DXVECTOR2* _pMovePosition)
		:vPosition(_vPosition), pMovePosition(_pMovePosition)
	{
		vColor = { 0,0,0 };
	}

	tagDragPanel(D3DXVECTOR2 _vPosition, D3DXVECTOR2* _pMovePosition, D3DXVECTOR3  _vColor)
		:vPosition(_vPosition), pMovePosition(_pMovePosition), vColor(_vColor)
	{
		
	}

}DRAGPANEL;

typedef struct tagStaticObject
{
	D3DXMATRIX matWorld;
	_uint      iType;
	tagStaticObject() {}

	tagStaticObject(D3DXMATRIX _matWorld, _uint _iType)
		:matWorld(_matWorld), iType(_iType)
	{

	}

}STATICLOAD;






