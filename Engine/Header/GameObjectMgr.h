#pragma once
#include "Base.h"

_BEGIN(Engine)
class CLayer;
class CGameObject;
class CComponent;
class _DLLEXPORTS CGameObjectMgr :
	public CBase
{
	DECLARE_SINGLETON(CGameObjectMgr)
private:
	_uint	iMaxSceneNum = 0;
	map<const _tchar*, CGameObject*>*		m_pMapPrototype = nullptr;
	typedef map<const _tchar*, CGameObject*> MAPPROTOTYPE;

	map<const _tchar*, CLayer*>*		m_pMapObject= nullptr;
	typedef map<const _tchar*, CLayer*> MAPOBJECT;

	CGameObject* FindPrototype(const _uint SceneID, const _tchar* _szTag);
	CLayer*		 FindLayer(const _uint SceneID, const _tchar* _szTag);



	explicit CGameObjectMgr();
	virtual ~CGameObjectMgr() = default;
public:
	HRESULT ReserveMaxScene(const _uint& SceneNum);
	HRESULT AddObejct_Prototype(const _uint& SceneID, const _tchar* _szTag,CGameObject* _GameObject);
	HRESULT AddObejct(const _uint& SceneProtoID, const _tchar* _szProtoTag,const _uint& SceneID, const _tchar* _szTag, void* pArg=nullptr);
	CGameObject* GetGameObject(const _uint& SceneProtoID, const _tchar* _szProtoTag,void* pArg = nullptr);
	CGameObject* FindGameObject(const _uint& SceneProtoID, const _tchar* _szProtoTag,int iNum=0);
	CComponent* FindComponent(const _uint& SceneProtoID, const _tchar* _szProtoTag, const _tchar* _szProtoComponentTag, int iNum = 0);
	list<CGameObject*>*		GetLayer(const _uint& SceneProtoID, const _tchar* _szTag);
	HRESULT DeleteSceneObject(const _uint& SceneNum);


	_int	Progress(const _float & fTimeDelta);
	_int	LateProgress(const _float & fTimeDelta);
	virtual HRESULT Render();

	virtual void Free();
};

_END
