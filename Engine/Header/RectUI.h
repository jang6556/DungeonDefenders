#pragma once
#include "VIBuffer.h"

_BEGIN(Engine)
class _DLLEXPORTS CRectUI :
	public CVIBuffer
{
private:
	virtual HRESULT Initialize();

	explicit CRectUI(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CRectUI(CRectUI& rhs);
	virtual ~CRectUI() = default;

public:
	virtual HRESULT Render();	
	virtual _int Progress(const _float& fTimeDelta);
	virtual _int LateProgress(const _float& fTimeDelta);

	static CRectUI* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	virtual CComponent* Clone();
	virtual void Free();
};
_END