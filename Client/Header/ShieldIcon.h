#pragma once
#include "SkillIcon.h"

_BEGIN(Client)
class CShieldIcon :
	public CSkillIcon
{
private:
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();


	explicit CShieldIcon(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CShieldIcon(const CShieldIcon & rhs);
	virtual ~CShieldIcon() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CShieldIcon* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);

};
_END
