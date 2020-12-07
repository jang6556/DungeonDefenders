#pragma once
#include "Base.h"



_BEGIN(Engine)

class CScene;
class _DLLEXPORTS CManageMent final : public CBase
{
	DECLARE_SINGLETON(CManageMent)
	
private:
	CScene* m_pCurrScene = nullptr;
	_uint   m_SceneID;

	explicit CManageMent();
	virtual ~CManageMent() = default;

public:
	HRESULT Initialize(const _uint& _SceneID);
	_int	Progress(const _float& fTimeDelta);	
	HRESULT Render();

	HRESULT SetCurrScene(CScene* _pScene, const _uint& _SceneID);
	_uint	GetCurrSceneID() { return m_SceneID; };
	static HRESULT Release_Engine();


	virtual void Free() override;
};

_END