#pragma once
#include "Scene.h"
#include "..\Header\Define.h"

_BEGIN(Client)
class CLoading;
class CSceneIntro final : public CScene
{
private:
	CLoading*		m_pLoading = nullptr;
	_uint			m_iComplete = 0;
	
	virtual HRESULT SetGameObjectPrototype() override;
	virtual HRESULT SetComponentPrototype() override;
	virtual HRESULT SetGameObject()  override;
	virtual HRESULT LoadGameObject() override;


	explicit CSceneIntro(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	virtual ~CSceneIntro() = default;
public:
	virtual HRESULT Initialize() override;
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual	_int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	static CSceneIntro* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);

	void Free() override;
};

_END