#pragma once
#include "Effect.h"

_BEGIN(Client)
class CFireBulletEffect :
	public CEffect
{
private:
	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CFireBulletEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CFireBulletEffect(const CFireBulletEffect & rhs);
	virtual ~CFireBulletEffect() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CFireBulletEffect* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
