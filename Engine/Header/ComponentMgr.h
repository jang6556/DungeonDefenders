#pragma once
#include "Base.h"
#include "RectUI.h"
#include "Triangle.h"
#include "TriCol.h"
#include "Transform.h"
#include "Texture.h"
#include "Terrain.h"
#include "Renderer.h"
#include "Shader.h"
#include "MeshStatic.h"
#include "MeshDynamic.h"
#include "Collider.h"
#include "NaviMesh.h"
#include "MonSphere.h"
#include "ScreenTex_Buffer.h"
#include "Frustum.h"

_BEGIN(Engine)

class _DLLEXPORTS CComponentMgr :
	public CBase
{
	DECLARE_SINGLETON(CComponentMgr)
private:
	_uint	iMaxSceneNum = 0;
	map<const TCHAR*, CComponent*>*		m_pMapComponent = nullptr;
	typedef map<const TCHAR*, CComponent*> MAPCOMPONENT;

	CComponent* FindPrototype(const TCHAR* szTag, _uint SceneNum);

	explicit CComponentMgr();
	virtual ~CComponentMgr() = default;
public:
	HRESULT AddPrototype(const TCHAR* szTag, CComponent* pComponent,_uint SceneNum);	
	HRESULT ReserveMapComponent(const _uint& SceneNum);
	CComponent* AddComponent(const TCHAR* szTag, _uint SceneNum);

	HRESULT DeleteSceneComponent(const _uint& SceneNum);

	virtual void Free() override;
};

_END