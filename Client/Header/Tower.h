#pragma once
#include "GameObject.h"
#include "TowerBullet.h"

_BEGIN(Client)
class CMonster;
class CHpBarContent;
class CHpBarUI;
class CTower :
	public CGameObject
{
public:
	enum TOWER_STATE { STATE_IDLE, STATE_ATTACK, STATE_END };
protected:
	CTransform*			m_pTransform = nullptr;
	CShader*			m_pShader = nullptr;
	CRenderer*			m_pRenderer = nullptr;	
	CMeshDynamic*		m_pMeshDynamic = nullptr;	
	vector<CCollider*>	m_pCollider;

	D3DXVECTOR3		m_vTargetPos;

	TOWER_STATE		m_TowerState;
	float			m_fTimeDelta = 0.f;
	float			m_fCoolTime=0.f;
	float			m_fCurrCoolTime = 0.f;
	int				m_iCurrHp = 0.f;
	int				m_iMaxHp = 0.f;

	bool			m_bAttackFlag = false;
	float			m_fHpBarTimeDelta = 1.f;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	HRESULT AttackMonster(_float _fRange);
	HRESULT SetPosition(void* pArg);
	_int	RotationToMonster(const _float& fTimeDelta);
	HRESULT SetColliderData();

	explicit CTower(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CTower(const CTower & rhs);
	virtual ~CTower() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;
	virtual HRESULT RenderShadow() override;

	void	SetHp(int iInput) { m_iCurrHp += iInput; m_fHpBarTimeDelta = 0.f; }

	virtual void Free() override;
};
_END
