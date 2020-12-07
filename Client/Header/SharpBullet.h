#pragma once
#include "Bullet.h"

_BEGIN(Client)
class CSharpBulletEffect;
class CSharpBullet :
	public CBullet
{
private:
	CSharpBulletEffect* m_pSharpBulletEffect = nullptr;
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CSharpBullet(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CSharpBullet(const CSharpBullet & rhs);
	virtual ~CSharpBullet() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CSharpBullet* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
