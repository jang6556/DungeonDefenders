#pragma once
#include "Tower.h"

_BEGIN(Client)
class CShield :
	public CTower
{
private:
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CShield(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CShield(const CShield & rhs);
	virtual ~CShield() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CShield* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
