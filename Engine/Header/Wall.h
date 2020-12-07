#pragma once
#include "VIBuffer.h"

_BEGIN(Engine)
class _DLLEXPORTS CWall :
	public CVIBuffer
{
private:

	explicit CWall(LPDIRECT3DDEVICE9	_m_pGraphicDev);
	explicit CWall(const CWall& rhs);
	virtual ~CWall() = default;

public:
	virtual HRESULT Initialize();
	virtual _int	Progress(const _float& fTimeDelta);
	virtual _int	LateProgress(const _float& fTimeDelta);
	virtual HRESULT Render(CTransform* pTransform=nullptr);

	static CWall* Create(LPDIRECT3DDEVICE9	_m_pGraphicDev);
	virtual CComponent* Clone();
	virtual void Free();
};
_END
