#pragma once
#include "Effect.h"

_BEGIN(Client)
class CItemEffect :
	public CEffect
{
public:
	enum COLOR { COLOR_BLUE = 1, COLOR_RED = 5, COLOR_GREEN = 10, COLOR_PURPLE = 50, COLOR_SKY = 500, COLOR_YELLOW = 2000, COLOR_END };
private:
	float	m_fAlpha=1.f;

	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	HRESULT SeletColor(COLOR eType);

	explicit CItemEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CItemEffect(const CItemEffect & rhs);
	virtual ~CItemEffect() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CItemEffect* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
