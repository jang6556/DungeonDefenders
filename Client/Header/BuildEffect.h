#pragma once
#include "Effect.h"

_BEGIN(Client)
class CBuildEffect :
	public CEffect
{
private:
	float		m_fTimeLimit=0.f;
	int			m_iFlag = 1.f;


	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CBuildEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CBuildEffect(const CBuildEffect & rhs);
	virtual ~CBuildEffect() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CBuildEffect* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
