#pragma once
#include "Effect.h"

_BEGIN(Client)
class CBombEffect :
	public CEffect
{
private:
	
	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CBombEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CBombEffect(const CBombEffect & rhs);
	virtual ~CBombEffect() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CBombEffect* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
