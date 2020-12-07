#pragma once
#include "VIBuffer.h"

_BEGIN(Engine)
class _DLLEXPORTS CTriangle final :
	public CVIBuffer
{
private:
	explicit CTriangle(LPDIRECT3DDEVICE9	_m_pGraphicDev);
	explicit CTriangle(const CTriangle& rhs);
	virtual ~CTriangle() = default;
public:
	virtual HRESULT Initialize();
	virtual _int	Progress(const _float& fTimeDelta);
	virtual _int	LateProgress(const _float& fTimeDelta);
	virtual HRESULT Render(CTransform* pTransform=nullptr);

	static CTriangle* Create(LPDIRECT3DDEVICE9	_m_pGraphicDev);
	virtual CComponent* Clone();
	virtual void Free();
};
_END
