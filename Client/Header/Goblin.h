#pragma once
#include "Monster.h"

_BEGIN(Client)
class CGoblin :
	public CMonster
{


private:
	float		m_fAttackCool = 0.f;
	

	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	
	

	explicit CGoblin(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CGoblin(const CGoblin & rhs);
	virtual ~CGoblin() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CGoblin* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END

