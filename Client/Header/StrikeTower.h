#pragma once
#include "Tower.h"

_BEGIN(Client)
class CMonster;
class CStrikeBeam;
class CGlowBall;
class CStrikeTower :
	public CTower
{
private:
	CMonster*		m_pTargetMonster = nullptr;
	float			m_fRange = 0.f;
	float			m_fDamage = 1.f;

	CGlowBall*		m_pGlowBall = nullptr;
	CStrikeBeam*	m_pStrikeBeam = nullptr;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	HRESULT	FindMonster();
	HRESULT Roatation(const _float & fTimeDelta);

	explicit CStrikeTower(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CStrikeTower(const CStrikeTower & rhs);
	virtual ~CStrikeTower() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CStrikeTower* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
