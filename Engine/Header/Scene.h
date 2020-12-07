#pragma once
#include "Base.h"
#include "GameObjectMgr.h"
#include "ComponentMgr.h"

_BEGIN(Engine)
class CGameObject;
class _DLLEXPORTS CScene :
	public CBase
{
protected:
	LPDIRECT3DDEVICE9 m_pGraphicDev = nullptr;
	CGameObjectMgr*	  m_pGameObjectMgr = nullptr;
	CComponentMgr*    m_pComponentMgr = nullptr;

	HRESULT AddObjectPrototype(const _uint& _SceneID, const _tchar* _szTag, CGameObject* _pGameObject);
	HRESULT AddObject(const _uint& _SceneProtoID, const _tchar* _szProtoTag,const _uint& _SceneID, const _tchar* _szTag, void* pArg = nullptr);

	virtual HRESULT SetComponentPrototype() PURE;
	virtual HRESULT SetGameObjectPrototype() PURE;	
	virtual HRESULT SetGameObject() PURE;
	virtual HRESULT LoadGameObject() PURE;


	CScene(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	~CScene() = default;

public:
	virtual HRESULT Initialize();
	virtual _int	Progress(const _float& fTimeDelta);
	virtual _int	LateProgress(const _float& fTimeDelta);
	virtual HRESULT Render();

	virtual void Free() override;
};

_END