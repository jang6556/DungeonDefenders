#pragma once
#include "TowerBullet.h"
#include "Projectile.h"

_BEGIN(Client)
class CMissileTowerBullet :
	public CTowerBullet
{
private:
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	explicit CMissileTowerBullet(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CMissileTowerBullet(const CMissileTowerBullet & rhs);
	virtual ~CMissileTowerBullet() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CMissileTowerBullet* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
