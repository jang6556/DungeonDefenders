#pragma once
#include "Decal.h"

_BEGIN(Client)
class CSummonDecal :
	public CDecal
{
private:
	bool	m_bFlag = false;
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent() override;

	explicit CSummonDecal(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CSummonDecal(const CSummonDecal & rhs);
	virtual ~CSummonDecal() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render(LPD3DXEFFECT pEffect) override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CSummonDecal* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
