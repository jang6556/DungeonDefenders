#pragma once
#include "VIBuffer.h"
_BEGIN(Engine)
class _DLLEXPORTS CRectangle :
	public CVIBuffer
{
private:
	explicit CRectangle(LPDIRECT3DDEVICE9	_m_pGraphicDev);
	explicit CRectangle(const CRectangle& rhs);
	virtual ~CRectangle() = default;

public:
	virtual HRESULT Initialize();
	virtual _int	Progress(const _float& fTimeDelta);
	virtual _int	LateProgress(const _float& fTimeDelta);
	virtual HRESULT Render(CTransform* pTransform=nullptr);

	static CRectangle* Create(LPDIRECT3DDEVICE9	_m_pGraphicDev);
	virtual CComponent* Clone();
	virtual void Free();
};

_END