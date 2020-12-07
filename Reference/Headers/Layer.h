#pragma once
#include "Base.h"

_BEGIN(Engine)
class CGameObject;
class CLayer final:
	public CBase
{
private:
	list<CGameObject*>	m_ObjList;
	typedef list<CGameObject*> OBJLIST;

	explicit CLayer();
	virtual ~CLayer() = default;
public:
	HRESULT Initialize();
	_int	Progress(const _float & fTimeDelta);
	_int	LateProgress(const _float & fTimeDelta);
	HRESULT Render();
	HRESULT	AddObject(CGameObject* _pGameObject);

	OBJLIST* GetObjList() { return &m_ObjList; }

	static CLayer*	Create();
	virtual void	Free() override;
};
_END
