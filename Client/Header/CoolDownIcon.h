#pragma once
#include "StatUI.h"

_BEGIN(Client)
class CCoolDownIcon :
	public CStatUI
{
private:
	virtual HRESULT Initialize() override;
	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CCoolDownIcon(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CCoolDownIcon(const CCoolDownIcon & rhs);
	virtual ~CCoolDownIcon() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CCoolDownIcon* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
