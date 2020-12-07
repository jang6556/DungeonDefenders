#pragma once
#include "StatUI.h"

_BEGIN(Client)
class CSkillDamagePanel :
	public CStatUI
{
private:
	virtual HRESULT Initialize() override;
	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CSkillDamagePanel(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CSkillDamagePanel(const CSkillDamagePanel & rhs);
	virtual ~CSkillDamagePanel() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CSkillDamagePanel* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
