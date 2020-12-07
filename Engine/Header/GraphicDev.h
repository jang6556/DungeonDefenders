#pragma once

#include "Base.h"

_BEGIN(Engine)


class _DLLEXPORTS CGraphicDev : public CBase
{

	DECLARE_SINGLETON(CGraphicDev)

private:	// com°´Ã¼
	LPDIRECT3D9			m_pSDK		= nullptr;
	LPDIRECT3DDEVICE9	m_pDevice	= nullptr;
	
public:
	LPDIRECT3DDEVICE9		GetDevice(void) { return m_pDevice; }

public:
	HRESULT		Initialize(HWND _g_hWnd,const _uint iWINCX, const _uint iWINCY, LPDIRECT3DDEVICE9* ppGraphicDev = nullptr);
	
	
	void		Render_Begin(void);
	void		Render_End(void);

	

	virtual void Free();
private:
	explicit CGraphicDev();
	virtual ~CGraphicDev() = default;
};

_END