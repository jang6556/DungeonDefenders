#pragma once
#include "PlayerUI.h"

_BEGIN(Client)
class CBuildLoadingContent :
	public CPlayerUI
{
private:
	float					m_fTimeDelta = 0;
	float					m_fAlpha = 0;
	float					m_fRatio = 0.f;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	explicit CBuildLoadingContent(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CBuildLoadingContent(const CBuildLoadingContent & rhs);
	virtual ~CBuildLoadingContent() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CBuildLoadingContent* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
