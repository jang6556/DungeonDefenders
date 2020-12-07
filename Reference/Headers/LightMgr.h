#pragma once
#include "Base.h"

_BEGIN(Engine)
class CLight;
class _DLLEXPORTS CLightMgr :
	public CBase
{
	DECLARE_SINGLETON(CLightMgr)
private:
	list<CLight*>*		m_pLight_List = nullptr;
	typedef list<CLight*>	LIGHTLIST;

	_uint				m_iMaxScene;

	explicit CLightMgr();
	virtual ~CLightMgr() = default;

public:
	HRESULT ReserveMaxScene(const _uint& SceneNum);
	HRESULT AddLight(const _uint& SceneID, LPDIRECT3DDEVICE9 _m_pGraphicDev, const D3DLIGHT9* LightInfo);
	HRESULT Render(LPD3DXEFFECT pEffect);
	HRESULT DeleteSceneLight(const _uint& SceneID);
	HRESULT	GetDirectionalLight(const _uint& SceneID,D3DXVECTOR3* _vEye,D3DXVECTOR3* _vAt, D3DXVECTOR3* _vUp, const int& _iNum=0);
	
	virtual void Free();
};
_END
