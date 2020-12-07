#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CWavePanel :
	public CGameObject
{
private:
	CRenderer*				m_pRenderer = nullptr;
	vector<CGameObject*>	m_vPanel;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	Add_UI_Object();


	explicit CWavePanel(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CWavePanel(const CWavePanel & rhs);
	virtual ~CWavePanel() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CWavePanel* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
