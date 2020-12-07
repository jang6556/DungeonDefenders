#pragma once
#include "SkillIcon.h"

_BEGIN(Client)
class CLightShot :
	public CSkillIcon
{
private:
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();


	explicit CLightShot(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CLightShot(const CLightShot & rhs);
	virtual ~CLightShot() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CLightShot* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
