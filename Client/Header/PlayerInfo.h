#pragma once
#include "PlayerUI.h"

_BEGIN(Client)
class CPlayerInfo :
	public CPlayerUI
{
private:
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	explicit CPlayerInfo(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CPlayerInfo(const CPlayerInfo & rhs);
	virtual ~CPlayerInfo() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CPlayerInfo* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
