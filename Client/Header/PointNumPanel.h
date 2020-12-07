#pragma once
#include "StatUI.h"

_BEGIN(Client)
class CNumIcon;
class CPointNumPanel :
	public CStatUI
{
private:	
	vector<CNumIcon*>	m_vNumIcon;

	virtual HRESULT Initialize() override;
	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	Add_UI_Object(void * pArg);

	explicit CPointNumPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CPointNumPanel(const CPointNumPanel & rhs);
	virtual ~CPointNumPanel() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CPointNumPanel* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
