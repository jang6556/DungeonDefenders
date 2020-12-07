#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CTextUI;
class CTextPanel :
	public CGameObject
{
private:
	vector<CTextUI*>	m_vTextIcon;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	Add_UI_Object();

	explicit CTextPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CTextPanel(const CTextPanel & rhs);
	virtual ~CTextPanel() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CTextPanel* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
