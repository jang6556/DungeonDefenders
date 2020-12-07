#pragma once
#include "Tower.h"

_BEGIN(Client)
class CGlowBall;
class CMissilTower :
	public CTower
{
private:
	CGlowBall*		m_pGlowBall = nullptr;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CMissilTower(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CMissilTower(const CMissilTower & rhs);
	virtual ~CMissilTower() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CMissilTower* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
