#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "Terrain.h"
#include "Renderer.h"
#include "Texture.h"

_BEGIN(Client)
class CStageTerrain :
	public CGameObject
{
private:
	CTerrain* m_Terrain = nullptr;
	CTransform* m_Transform = nullptr;
	CTexture*	m_Texture = nullptr;
	CRenderer*  m_Renderer = nullptr;

	explicit CStageTerrain(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CStageTerrain(const CStageTerrain& rhs);
	virtual ~CStageTerrain() = default;

	HRESULT AddComponent();
	HRESULT SetRenderState();
	HRESULT ResetRenderState();
public:
	virtual HRESULT Initialize() override;
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CStageTerrain* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
