#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CPlayerAbility :
	public CGameObject
{
public:
	enum ABILITY { ABILITY_DAMAGE, ABILITY_HEALTH, ABILITY_COOL, ABILITY_MANA, ABILITY_END};
	typedef struct tagPlayerAbility
	{
		int m_iAbility[ABILITY_END];

	};
private:
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;

	explicit CPlayerAbility(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CPlayerAbility(const CPlayerAbility & rhs);
	virtual ~CPlayerAbility() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CPlayerAbility* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END

