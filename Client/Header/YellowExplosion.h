#pragma once
#include "Effect.h"

_BEGIN(Client)
class CYellowExplosion :
	public CEffect
{
private:
	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CYellowExplosion(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CYellowExplosion(const CYellowExplosion & rhs);
	virtual ~CYellowExplosion() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CYellowExplosion* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
