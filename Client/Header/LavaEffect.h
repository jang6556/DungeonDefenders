#pragma once
#include "Effect.h"

_BEGIN(Client)
class CLavaEffect :
	public CEffect
{
private:
	float	m_fAlpha = 0.5f;
	
	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CLavaEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CLavaEffect(const CLavaEffect & rhs);
	virtual ~CLavaEffect() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CLavaEffect* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);

};
_END
