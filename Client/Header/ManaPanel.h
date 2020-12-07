#pragma once
#include "StatUI.h"

_BEGIN(Client)
class CManaPanel :
	public CStatUI
{
private:
	virtual HRESULT Initialize() override;
	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CManaPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CManaPanel(const CManaPanel & rhs);
	virtual ~CManaPanel() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CManaPanel* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
