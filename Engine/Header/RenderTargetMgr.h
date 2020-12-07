#pragma once
#include "Base.h"

_BEGIN(Engine)
class CRender_Target;
class _DLLEXPORTS CRenderTargetMgr :
	public CBase
{
	DECLARE_SINGLETON(CRenderTargetMgr)
private:
	map<const TCHAR*, CRender_Target*>	m_MapTarget; //RenderTarget 하나 하나 저장
	typedef map<const TCHAR*, CRender_Target*> MAPTARGET;

	map<const TCHAR*,list<CRender_Target*>>	m_MapMultiTarget;
	typedef map<const TCHAR*, list<CRender_Target*>> MAPMULTITARGET;


	CRender_Target*			FindTarget(const TCHAR* szTagName);
	list<CRender_Target*>*   FindMultiTarget(const TCHAR* szTagName);

	explicit CRenderTargetMgr();
	virtual ~CRenderTargetMgr() = default;
public:

	HRESULT	AddRenderTarget(LPDIRECT3DDEVICE9 _m_pGraphicDev, const TCHAR* szTargetTag, _uint iWidth, _uint iHeight, D3DFORMAT eFormat, D3DXCOLOR Back_Color);
	HRESULT	AddMultiTarget(const TCHAR* szMultiTargetTag,const TCHAR* szTargetTag);
	HRESULT	MultiTarget_Begin(const TCHAR* szMultiTargetTag);
	HRESULT	MultiTarget_End(const TCHAR* szMultiTargetTag);
	HRESULT SetTexture(LPD3DXEFFECT pEffect, const TCHAR* szTargetTag, const char* ShaderTexName);

	virtual void Free();

#ifdef _DEBUG

public:
	HRESULT Render_Buffer(const TCHAR* szMultiTargetTag);
	HRESULT Initialize_Buffer(const TCHAR* szTargetTag, _float _fStartX, _float _fStartY, _float _fSizeX, _float _fSizeY);
#endif 
};
_END
