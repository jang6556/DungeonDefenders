#pragma once
#include "Effect.h"


_BEGIN(Client)
class CLightningSphere :
	public CEffect
{
private:

	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CLightningSphere(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CLightningSphere(const CLightningSphere & rhs);
	virtual ~CLightningSphere() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CLightningSphere* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
