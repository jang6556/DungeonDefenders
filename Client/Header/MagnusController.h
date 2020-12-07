#pragma once
#include "MonsterController.h"

_BEGIN(Client)
class CMagnusController :
	public CMonsterController
{
public:
	enum MONSTER { MONSTER_GOBLIN, MONSTER_ARCHER, MONSTER_KOBOLD,MONSTER_ORCBRUISER, MONSTER_END };
private:
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT Initialize(void* pArg);

	virtual HRESULT	MakeMonsterWave();

	explicit CMagnusController(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CMagnusController(const CMagnusController & rhs);
	virtual ~CMagnusController() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual HRESULT CreateMonster(D3DXVECTOR3 vPosition, list<int>& _Path);

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CMagnusController* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
