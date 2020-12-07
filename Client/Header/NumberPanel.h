#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CNumberUI;
class CNumberPanel :
	public CGameObject
{
private:
	vector<CNumberUI*>	m_vNumIcon;

	virtual HRESULT Initialize() override;	
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	Add_UI_Object();

	HRESULT SetPlayerInfo();
	HRESULT SetSkillMana();	
	HRESULT SetWaveInfo();
	HRESULT SetDefenseNum();

	explicit CNumberPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CNumberPanel(const CNumberPanel & rhs);
	virtual ~CNumberPanel() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CNumberPanel* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
