#pragma once
#include "PlayerUI.h"

_BEGIN(Client)
class CWaveBarContents :
	public CPlayerUI
{
private:
	float					m_fTimeDelta = 0;
	D3DXVECTOR2				m_vCurrWave = D3DXVECTOR2(0.f, 0.f);

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	explicit CWaveBarContents(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CWaveBarContents(const CWaveBarContents & rhs);
	virtual ~CWaveBarContents() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CWaveBarContents* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END