#pragma once
#include "PlayerUI.h"

_BEGIN(Client)
class CPhase :
	public CPlayerUI
{
private:
	CRenderer*				m_pRenderer = nullptr;

	float					m_fTimeDelta = 0.f;

	float					m_fAlpha = 0.f;
	float					m_fFlag = 1.f;

	virtual HRESULT Initialize() override;
	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	explicit CPhase(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CPhase(const CPhase & rhs);
	virtual ~CPhase() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CPhase* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
