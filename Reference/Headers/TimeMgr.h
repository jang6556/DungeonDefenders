#pragma once
#include "Base.h"

_BEGIN(Engine)
class CTimer;

class _DLLEXPORTS CTimeMgr final :
	public CBase
{
	DECLARE_SINGLETON(CTimeMgr)
private:
	explicit CTimeMgr();
	virtual ~CTimeMgr() = default;
public:
	HRESULT Add_Timer(const _tchar* pTimerTag);
	_float	Compute_TimeDelta(const _tchar* pTimerTag);
private:
	map<const _tchar*, CTimer*>			m_mapTimers;
	typedef map<const _tchar*, CTimer*>	MAPTIMERS;
private:
	CTimer* Find_Timer(const _tchar* pTimerTag);
public:
	virtual void Free();
};
_END
