#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "Cube.h"
#include "Texture.h"
#include "Renderer.h"
_BEGIN(Client)
class CSkyBox :
	public CGameObject
{
private:
	CCube*		m_Cube = nullptr;
	CTransform* m_Transform = nullptr;
	CTexture*	m_Texture = nullptr;
	CRenderer*  m_Renderer = nullptr;

	explicit CSkyBox(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CSkyBox(const CSkyBox & rhs);
	virtual ~CSkyBox() = default;

	HRESULT SetRenderState();
	HRESULT ResetRenderState();
public:
	virtual HRESULT Initialize() override;
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	HRESULT InitializePrototype();
	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CSkyBox* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
