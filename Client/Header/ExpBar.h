#pragma once
#include "PlayerUI.h"

_BEGIN(Client)
class CExpBar :
	public CPlayerUI
{
private:
	float					m_fTimeDelta = 0;
	D3DXVECTOR2				m_fExpRatio = D3DXVECTOR2(0,0);

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	explicit CExpBar(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CExpBar(const CExpBar & rhs);
	virtual ~CExpBar() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CExpBar* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END

