#pragma once
#include "MonsterUI.h"

_BEGIN(Client)
class CMonsterHpCurr :
	public CMonsterUI
{
private:
	int		m_iflag = 1;
	float	m_fCurrUV = 0.f;
	
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();

	explicit CMonsterHpCurr(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CMonsterHpCurr(const CMonsterHpCurr & rhs);
	virtual ~CMonsterHpCurr() = default;

public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CMonsterHpCurr* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
