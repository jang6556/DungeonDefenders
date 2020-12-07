#pragma once
#include "VIBuffer.h"

_BEGIN(Engine)
class _DLLEXPORTS CScreenTex_Buffer :
	public CVIBuffer
{
private:
	virtual HRESULT Initialize();
	virtual HRESULT Initialize(_float _fStartX, _float _fStartY, _float _fSizeX, _float _fSizeY);

	explicit CScreenTex_Buffer(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CScreenTex_Buffer(CScreenTex_Buffer& rhs);
	virtual ~CScreenTex_Buffer() = default;

public:
	virtual HRESULT Render();
	virtual _int Progress(const _float& fTimeDelta);
	virtual _int LateProgress(const _float& fTimeDelta);

	static CScreenTex_Buffer* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	static CScreenTex_Buffer* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev,_float _fStartX, _float _fStartY, _float _fSizeX, _float _fSizeY);
	virtual CComponent* Clone();
	virtual void Free();
};
_END
