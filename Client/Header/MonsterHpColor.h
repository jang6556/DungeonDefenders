#pragma once
#include "MonsterUI.h"

_BEGIN(Client)
class CMonsterHpColor :
	public CMonsterUI
{
private:
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();

	explicit CMonsterHpColor(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CMonsterHpColor(const CMonsterHpColor & rhs);
	virtual ~CMonsterHpColor() = default;

public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CMonsterHpColor* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
