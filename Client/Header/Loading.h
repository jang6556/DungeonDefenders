#pragma once
#include "Base.h"

_BEGIN(Client)
class CLoading :
	public CBase
{
private:
	LPDIRECT3DDEVICE9 m_pGraphicDev = nullptr;
	SCENEID	 m_eSceneID;
	HANDLE	 m_hThread;
	CRITICAL_SECTION m_CS;
	CComponentMgr*	m_pComponentMgr = nullptr;
	_uint		m_iComplete = 0.f;

	HRESULT Load_Static();
	HRESULT	Load_StaticObject();

	HRESULT Load_Static_Texture();
	HRESULT Load_Static_Shader();
	HRESULT Load_Static_StaticMesh();
	HRESULT Load_Static_DynamicMesh();

	explicit CLoading(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	virtual ~CLoading() = default;

public:
	HRESULT Initialize(SCENEID eSceneID);

	static _uint APIENTRY Thread_Main(void* Arg);

	_uint GetComplete() { return m_iComplete; }

	static CLoading* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev, SCENEID eSceneID);
	virtual void Free();


};
_END
