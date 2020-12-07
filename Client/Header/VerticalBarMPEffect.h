#pragma once
#include "PlayerUI.h"

_BEGIN(Client)
class CPlayer;
class CVerticalBarMPEffect :
	public CPlayerUI
{
private:
	
	CPlayer*				m_pPlayer = nullptr;

	float					m_fHP = 0.f;
	float					m_fTimeDelta = 1.f;
	float					m_fGlare = 0.f;
	int						m_iGlare = 1.f;


	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CVerticalBarMPEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CVerticalBarMPEffect(const CVerticalBarMPEffect & rhs);
	virtual ~CVerticalBarMPEffect() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CVerticalBarMPEffect* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
