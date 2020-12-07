#pragma once
#include "SkillIcon.h"

_BEGIN(Client)
class CMissileTowerIcon :
	public CSkillIcon
{
private:
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();


	explicit CMissileTowerIcon(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CMissileTowerIcon(const CMissileTowerIcon & rhs);
	virtual ~CMissileTowerIcon() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CMissileTowerIcon* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END

