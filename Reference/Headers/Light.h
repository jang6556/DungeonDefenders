#pragma once
#include "Base.h"

_BEGIN(Engine)
class CScreenTex_Buffer;
class CFrustum;
class CLight :
	public CBase
{
private:
	LPDIRECT3DDEVICE9	m_pGraphicDev = nullptr;
	CScreenTex_Buffer*	m_pBuffer = nullptr;
	CFrustum*			m_pFrustum = nullptr;
	D3DLIGHT9			m_LightInfo;

	HRESULT Initialize(const D3DLIGHT9* LightInfo);

	explicit CLight(LPDIRECT3DDEVICE9	_m_pGraphicDev);
	virtual ~CLight() = default;
public:
	HRESULT Render(LPD3DXEFFECT pEffect);

	D3DLIGHT9	GetLightInfo() { return m_LightInfo; }

	static CLight* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev,const D3DLIGHT9* LightInfo);
	virtual void Free();
};
_END
