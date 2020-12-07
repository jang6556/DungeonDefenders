#pragma once
#include "StatUI.h"

_BEGIN(Client)
class CCoolPanel :
	public CStatUI
{
private:
	virtual HRESULT Initialize() override;
	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CCoolPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CCoolPanel(const CCoolPanel & rhs);
	virtual ~CCoolPanel() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CCoolPanel* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
