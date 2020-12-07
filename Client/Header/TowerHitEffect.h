#pragma once
#include "Effect.h"

_BEGIN(Client)
class CTowerHitEffect :
	public CEffect
{
private:
	float	m_fAlpha = 1.f;

	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();	

	explicit CTowerHitEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CTowerHitEffect(const CTowerHitEffect & rhs);
	virtual ~CTowerHitEffect() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CTowerHitEffect* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
