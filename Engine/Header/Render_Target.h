#pragma once
#include "Base.h"

_BEGIN(Engine)
class CScreenTex_Buffer;
class CRender_Target :
	public CBase
{
#ifdef _DEBUG
private:
	CScreenTex_Buffer*	m_pBuffer = nullptr;

public:
	HRESULT Initialize_Buffer(_float _fStartX, _float _fStartY, _float _fSizeX, _float _fSizeY);
	HRESULT Render_Buffer();

#endif // DEBUG


private:
	LPDIRECT3DDEVICE9	m_pGraphicDev	= nullptr;
	LPDIRECT3DTEXTURE9  m_pTexture		= nullptr;
	LPDIRECT3DSURFACE9  m_pCurrSurface  = nullptr;
	LPDIRECT3DSURFACE9	m_pOldSurface   = nullptr;

	D3DXCOLOR			m_BackColor;

	HRESULT Initialize(_uint iWidth, _uint iHeight, D3DFORMAT eFormat, D3DXCOLOR Back_Color);


	explicit CRender_Target(LPDIRECT3DDEVICE9	_m_pGraphicDev);
	virtual ~CRender_Target() = default;

public:
	HRESULT SetTexture(LPD3DXEFFECT pEffect, const char* ShaderTexName);
	HRESULT	SetRenderTarget(const int& iIndex);
	HRESULT	ReleaseRenderTarget(const int& iIndex);
	HRESULT	ClearRenderTarget();

	static CRender_Target* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev,_uint iWidth,_uint iHeight,D3DFORMAT eFormat,D3DXCOLOR Back_Color);
	virtual void Free();
};
_END
