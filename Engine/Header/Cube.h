#pragma once
#include "VIBuffer.h"
_BEGIN(Engine)
class _DLLEXPORTS CCube :
	public CVIBuffer
{
private:
	explicit CCube(LPDIRECT3DDEVICE9	_m_pGraphicDev);
	explicit CCube(const CCube & rhs);
	virtual ~CCube() = default;

public:
	virtual HRESULT Initialize();
	virtual _int	Progress(const _float& fTimeDelta);
	virtual _int	LateProgress(const _float& fTimeDelta);
	virtual HRESULT Render(CTransform* pTransform=nullptr);

	static CCube* Create(LPDIRECT3DDEVICE9	_m_pGraphicDev);
	virtual CComponent* Clone();
	virtual void Free();
};
_END
