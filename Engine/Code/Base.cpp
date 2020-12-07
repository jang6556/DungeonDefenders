#include "..\Header\Base.h"

_USING(Engine)

CBase::CBase()
{

}

_ulong CBase::Release()
{
	if (m_dwRefCount == 0)
	{
		Free();
		delete this;

		return 0;
	}
	else
		return m_dwRefCount--;
}

_ulong CBase::AddRef()
{
	return (_ulong)++m_dwRefCount;
}
