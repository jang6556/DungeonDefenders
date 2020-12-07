#pragma once
#include "GameObject.h"


_BEGIN(Client)
class CMonsterHpBar;
class CMonster :
	public CGameObject
{
public:
	enum STATE { STATE_IDLE, STATE_HIT, STATE_ATTACK, STATE_WALK, STATE_RUN, STATE_DIE, END };
	enum COLLIDER {COLLIDER_BODY,COLLIDER_WEAPON0, COLLIDER_WEAPON1, COLLIDER_END};

	typedef struct tagMonsterInfo 
	{
		STATE m_State;
		float m_fCurrHP;
		float m_fMaxHP;
		float m_fDropItemNum;
		int	  m_iDamge;
		float m_fSpeed;
		_uint m_iExp;
		D3DXVECTOR3	m_vBloodColor;
	}MONSTERINFO;

protected:
	MONSTERINFO				m_MonsterInfo;
	CTransform*				m_pTransform = nullptr;
	CShader*				m_pShader = nullptr;
	CRenderer*				m_pRenderer = nullptr;
	CMeshDynamic*			m_pMeshDynamic = nullptr;
	vector<CCollider*>		m_pCollider;
	CMonsterHpBar*			m_pMonsterHpBar = nullptr;
	CNaviMesh*				m_pNaviMesh = nullptr;
	list<int>				m_Path;
	bool					m_bAttack = false;

	float					m_fTimeDelta = 0.f;
	float					m_fScale = 0.f;
	list<CGameObject*>		m_HitList;
	D3DXVECTOR3				m_vTarget;
	
		
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();


	HRESULT AttackCheck(float fDegree,float fRange,bool bTargetPlayer = true);
	HRESULT RotateToTarget(const _float& fTimeDelta);
	HRESULT RunToTarget(const _float& fTimeDelta);
	float   ComputeTargetDistance();

	HRESULT Move(const float fTimeDelta);
	HRESULT Dead();
	_int    DropItem();

	bool    CheckCollision_MeleeWeapon(CCollider* pCollider);
	bool    CheckExplosion(CCollider* pCollider);

	bool    CheckCollision(CCollider* pCollider,CCollider::COLLIDER eType);

	explicit CMonster(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CMonster(const CMonster & rhs);
	virtual ~CMonster() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;
	virtual HRESULT RenderShadow() override;

	D3DXVECTOR3	GetPosition() { return m_pTransform->GetPosition(); }
	const MONSTERINFO* GetMonsterInfo() const { return &m_MonsterInfo; }
	float GetHpRatio() { return m_MonsterInfo.m_fCurrHP / m_MonsterInfo.m_fMaxHP; }
	void  SetPath(list<int>& _Path) { m_Path = _Path; }


	HRESULT SetHp(float _fInput);

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;
};
_END
