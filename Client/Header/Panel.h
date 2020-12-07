#pragma once
#include "GameObject.h"

_BEGIN(Client)

class CPanel :
	public CGameObject
{
private:
	CRenderer*				m_pRenderer = nullptr;
	vector<CGameObject*>	m_vPanel;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	Add_UI_Object();


	explicit CPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CPanel(const CPanel & rhs);
	virtual ~CPanel() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CPanel* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
