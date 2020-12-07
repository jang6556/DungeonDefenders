#pragma once
#include "Effect.h"

_BEGIN(Client)
class CPoisonFieldEffect :
	public CEffect
{
private:
	float	m_fAlpha = 1.f;

	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();	

	explicit CPoisonFieldEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CPoisonFieldEffect(const CPoisonFieldEffect & rhs);
	virtual ~CPoisonFieldEffect() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CPoisonFieldEffect* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
