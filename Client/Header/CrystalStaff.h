#pragma once
#include "LightObject.h"
_BEGIN(Client)
class CCrystalStaff :
	public CLightObject
{
private:
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();

	explicit CCrystalStaff(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CCrystalStaff(const CCrystalStaff & rhs);
	virtual ~CCrystalStaff() = default;

public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CCrystalStaff* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
