#pragma once
#include "StaticMapObject.h"

_BEGIN(Client)
class CLongRail :
	public CStaticMapObject
{
private:
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();


	explicit CLongRail(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CLongRail(const CLongRail & rhs);
	virtual ~CLongRail() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CLongRail* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
