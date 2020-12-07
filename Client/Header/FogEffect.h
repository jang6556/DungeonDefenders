#pragma once
#include "Effect.h"

_BEGIN(Client)
class CFogEffect :
	public CEffect
{
private:
	float	m_fAlpha = 0.5f;
	int		m_iFlag = 1.f;
	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CFogEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CFogEffect(const CFogEffect & rhs);
	virtual ~CFogEffect() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CFogEffect* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
