#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CMonsterUI;
class CMonster;
class CMonsterHpBar :
	public CGameObject
{
private:
	CRenderer*				m_pRenderer = nullptr;
	CMonster*				m_pMonster = nullptr;
	list<CMonsterUI*>	m_pMonsterUI_List;
	bool				m_IsDie = false;

	float				m_fTimeDelta = 100.f;
	
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	

	explicit CMonsterHpBar(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CMonsterHpBar(const CMonsterHpBar & rhs);
	virtual ~CMonsterHpBar() = default;

public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	void	SetIsDie(bool IsDie) { m_IsDie = IsDie; }
	void	SetRender() { m_fTimeDelta = 0.f; }


	virtual void Free() override;

	static CMonsterHpBar* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
