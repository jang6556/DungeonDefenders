#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CStatPanel :
	public CGameObject
{
private:
	CRenderer*				m_pRenderer = nullptr;
	vector<CGameObject*>	m_vStatUI;

	D3DXVECTOR2				m_vMovePanel = { -350,70 };

	bool					m_IsRender = false;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	Add_UI_Object();


	explicit CStatPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CStatPanel(const CStatPanel & rhs);
	virtual ~CStatPanel() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	HRESULT	RenderSwitch();

	virtual void Free() override;

	static CStatPanel* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
