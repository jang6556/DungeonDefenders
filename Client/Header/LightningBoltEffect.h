#pragma once
#include "Effect.h"

_BEGIN(Client)
class CLightningBoltEffect :
	public CEffect
{
private:

	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CLightningBoltEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CLightningBoltEffect(const CLightningBoltEffect & rhs);
	virtual ~CLightningBoltEffect() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CLightningBoltEffect* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
