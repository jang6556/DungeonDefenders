#pragma once
#include "Bullet.h"

_BEGIN(Client)
class CFireBullet :
	public CBullet
{
private:
	float	fBulletSpeed;
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CFireBullet(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CFireBullet(const CFireBullet & rhs);
	virtual ~CFireBullet() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CFireBullet* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
