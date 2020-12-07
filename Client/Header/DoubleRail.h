#pragma once
#include "StaticMapObject.h"

_BEGIN(Client)
class CDoubleRail :
	public CStaticMapObject
{
private:
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();


	explicit CDoubleRail(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CDoubleRail(const CDoubleRail & rhs);
	virtual ~CDoubleRail() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CDoubleRail* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
