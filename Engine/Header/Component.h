#pragma once
#include "Base.h"

_BEGIN(Engine)
class _DLLEXPORTS CComponent :
	public CBase
{
protected:
	LPDIRECT3DDEVICE9	m_pGraphicDev = nullptr;
	bool				m_IsClone = false;

	explicit CComponent(LPDIRECT3DDEVICE9	_m_pGraphicDev);
	explicit CComponent(const CComponent& rhs);
	virtual ~CComponent() = default;

public:
	virtual HRESULT Initialize();
	virtual CComponent* Clone() PURE;
	virtual void Free();

};
_END
