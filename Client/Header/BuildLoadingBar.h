#pragma once
#include "PlayerUI.h"

_BEGIN(Client)
class CBuildLoadingBar :
	public CPlayerUI
{
private:
	float					m_fAlpha = 0;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	explicit CBuildLoadingBar(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CBuildLoadingBar(const CBuildLoadingBar & rhs);
	virtual ~CBuildLoadingBar() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CBuildLoadingBar* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END