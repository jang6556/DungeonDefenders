#pragma once
#include "Base.h"
#include "Define.h"


_BEGIN(Engine)
class CManageMent;
class CRenderer;
_END


_BEGIN(Client)

class CMainApp : public CBase
{
private:
	CManageMent* m_pManageMent = nullptr;
	CRenderer*	 m_pRenderer = nullptr;
	LPDIRECT3DDEVICE9 m_pGraphicDev = nullptr;

	int fps;
	DWORD dwTimer;
	TCHAR szFps[128];

	explicit CMainApp();
	virtual ~CMainApp() = default;

	HRESULT SetScene(SCENEID _ID);
	HRESULT SetStaticPrototype();
	HRESULT SetObjectPrototype();
public:
	static CMainApp* Create();
	void Free();

	HRESULT Initilize();
	_int Progress(const _float& fTimeDelta);
	HRESULT Render();
};

_END