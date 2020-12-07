#pragma once
#include "Decal.h"

_BEGIN(Client)
class CBuildPoint :
	public CDecal
{
private:
	CNaviMesh*			m_pNaviMesh = nullptr;
	bool				m_IsInRange = false;
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent() override;

	explicit CBuildPoint(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CBuildPoint(const CBuildPoint & rhs);
	virtual ~CBuildPoint() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render(LPD3DXEFFECT pEffect) override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CBuildPoint* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
