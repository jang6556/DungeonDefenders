#pragma once
#include "Effect.h"

_BEGIN(Client)
class CLavaFogEffect :
	public CEffect
{
private:
	D3DXVECTOR3 m_vPosition;
	float	m_fAlpha = 0.5f;
	D3DXVECTOR2 m_vUV = { 0,0 };


	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CLavaFogEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CLavaFogEffect(const CLavaFogEffect & rhs);
	virtual ~CLavaFogEffect() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CLavaFogEffect* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
