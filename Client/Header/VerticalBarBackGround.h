#pragma once
#include "PlayerUI.h"

_BEGIN(Client)
class CVerticalBarBackGround :
	public CPlayerUI
{
private:
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	explicit CVerticalBarBackGround(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CVerticalBarBackGround(const CVerticalBarBackGround & rhs);
	virtual ~CVerticalBarBackGround() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CVerticalBarBackGround* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
