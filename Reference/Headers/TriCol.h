#pragma once
#include "VIBuffer.h"

_BEGIN(Engine)
class _DLLEXPORTS CTriCol :
	public CVIBuffer
{
private:
	explicit CTriCol(LPDIRECT3DDEVICE9	_m_pGraphicDev);
	explicit CTriCol(const CTriCol& rhs);
	virtual ~CTriCol() = default;

public:
	virtual HRESULT Initialize();
	virtual _int	Progress(const _float& fTimeDelta);
	virtual _int	LateProgress(const _float& fTimeDelta);
	virtual HRESULT Render(CTransform* pTransform=nullptr);

	static CTriCol* Create(LPDIRECT3DDEVICE9	_m_pGraphicDev);
	virtual CComponent* Clone();
	virtual void Free();
};
_END
