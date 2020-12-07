#pragma once
#include "Component.h"

_BEGIN(Engine)
class _DLLEXPORTS CTexture :
	public CComponent
{
public:
	enum TEXTYPE { GENERIC, CUBE };
private:
	vector<IDirect3DBaseTexture9*>			m_vecTexture;
	
	HRESULT Initialize(const _tchar* szFileName, const _uint& iFileNum, TEXTYPE eType);
	

	explicit CTexture(LPDIRECT3DDEVICE9	_m_pGraphicDev);
	explicit CTexture(const CTexture& rhs);
	virtual ~CTexture() = default;


public:
	
	HRESULT SetTexture(const _uint& iIndex);
	HRESULT SetTexture(LPD3DXEFFECT pEffect, const char* ShaderTexName, const int& iIndex);

	static CTexture* Create(LPDIRECT3DDEVICE9	_m_pGraphicDev,const _tchar* szFileName,const _uint& iFileNum = 1,TEXTYPE eType=GENERIC );
	virtual CComponent* Clone();
	virtual void Free();
};
_END
