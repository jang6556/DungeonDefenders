#pragma once
#include "SkillIcon.h"

_BEGIN(Client)
class CPoisionFieldIcon :
	public CSkillIcon
{
private:
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();


	explicit CPoisionFieldIcon(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CPoisionFieldIcon(const CPoisionFieldIcon & rhs);
	virtual ~CPoisionFieldIcon() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CPoisionFieldIcon* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
