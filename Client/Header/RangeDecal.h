#pragma once
#include "Decal.h"

_BEGIN(Client)
class CRangeDecal :
	public CDecal
{
private:
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent() override;

	explicit CRangeDecal(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CRangeDecal(const CRangeDecal & rhs);
	virtual ~CRangeDecal() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render(LPD3DXEFFECT pEffect) override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CRangeDecal* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END

