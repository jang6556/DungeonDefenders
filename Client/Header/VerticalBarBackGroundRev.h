#pragma once
#include "PlayerUI.h"

_BEGIN(Client)
class CVerticalBarBackGroundRev :
	public CPlayerUI
{
private:
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CVerticalBarBackGroundRev(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CVerticalBarBackGroundRev(const CVerticalBarBackGroundRev & rhs);
	virtual ~CVerticalBarBackGroundRev() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CVerticalBarBackGroundRev* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
