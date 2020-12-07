#pragma once
#include "Engine_Define.h"

_BEGIN(Engine)
class _DLLEXPORTS CBase
{
private:
	_ulong m_dwRefCount = 0;

protected:

	explicit CBase();
	virtual ~CBase() = default;

public:	
	virtual void Free() PURE;
	_ulong	GetRefCount() { return m_dwRefCount; }

	_ulong Release();
	_ulong AddRef();
};

_END