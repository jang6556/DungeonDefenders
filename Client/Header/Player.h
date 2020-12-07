#pragma once
#include "GameObject.h"
_BEGIN(Client)
class CPlayer :
	public CGameObject
{
public:
	enum SKILL {SKILL_1, SKILL_2, SKILL_3, SKILL_4, SKILL_5, SKILL_6,SKILL_7,SKILL_8,SKILL_9,SKILL_10, SKILL_END};
	enum MODE  {MODE_DEFAULT,MODE_BULID,MODE_END};
	enum BUILD_STATE { BUILD_READY, BUILD_RUN,BUILD_ING,BUILD_END};
	enum ABILITY { ABILITY_DAMAGE, ABILITY_HEALTH, ABILITY_COOL, ABILITY_MANA, ABILITY_END };
	enum BULLET { DEFAULT, FIRE, SHARP, BOMB, POISION, SHIELD, MISSILE_TOWER, LIGHTNING_TOWER, STRIKE_TOWER, BULLET_END };
public:
	typedef struct tagPlayerInfo
	{
		float	fSpeed;
		int		iCurrHp;
		int		iMaxHp;
		int		iCurrMp;
		int		iMaxMp;
		float	fShootCool;
		BULLET	iBulletType = DEFAULT;
		bool    bShot;
		_uint	iCurrExp;
		_uint	iLevel;
		int		iAttack;
		int		iAbilityPoint;
		int     iAbility[ABILITY_END];

		tagPlayerInfo()
		{
			fSpeed = 5.f;
			
			iMaxHp = 100;
			iMaxMp = 200;

			iCurrHp = iMaxHp;
			iCurrMp = iMaxMp;

			fShootCool = 0.5f;
			bShot = true;

			iCurrExp = 0;
			iLevel = 1;
			iAttack = 10;
			iAbilityPoint = 15;

			iAbility[ABILITY_DAMAGE] = 0;
			iAbility[ABILITY_HEALTH] = 0;
			iAbility[ABILITY_COOL] = 0;
			iAbility[ABILITY_MANA] = 0;			
		}
	}PLAYERINFO;
private:
	PLAYERINFO			m_tPlayerInfo;
	SKILLINFO			m_SkillInfo[SKILL_END];

	MODE				m_ePlayerMode = MODE_DEFAULT;
	BUILD_STATE			m_ePlayerBulidState = BUILD_READY;

	D3DXVECTOR3			m_vBuildTarget;
	vector<D3DXVECTOR4>	m_vecLevelTable; // 경험치 공격력 체력


	CTransform*			m_pTransform = nullptr;
	CShader*			m_pShader = nullptr;
	CRenderer*			m_pRenderer = nullptr;
	CMeshDynamic*		m_pMeshDynamic = nullptr;
	vector<CCollider*>	m_pCollider;
	CNaviMesh*			m_pNaviMesh = nullptr;	

	bool				m_bBuild = false;
	bool				m_bIsStatPanelRender = false;
	bool				m_bKeyFlag = false;


	virtual HRESULT Initialize() override;
	HRESULT	AddComponent();

	void	KeyInput(const _float& fTimeDelta);
	void	FireBullet(BULLET eType);
	void	InputSkill();

	void	BuildKeyInput(const _float& fTimeDelta);	
	void	InputBuildSkill();	
	
	void	RunToBuildTarget(const _float& fTimeDelta);
	void	BuildCasting(const _float& fTimeDelta);
	void	BuildObject();

	void    DefaultMode(const _float& fTimeDelta);
	void    BuildMode(const _float& fTimeDelta);

	void	CoolTimeControl(const _float& fTimeDelta);
	void	SetSkillInfo();

	void	SetLevelUpTable();
	void	LevelUp();

	explicit CPlayer(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CPlayer(const CPlayer & rhs);
	virtual ~CPlayer() = default;
public:	
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;
	virtual HRESULT RenderShadow() override;

	const SKILLINFO*	GetSkillInfo(SKILL eType) const { return &m_SkillInfo[eType]; }
	_uint				GetPlayerMode() { return (_uint)m_ePlayerMode; }
	PLAYERINFO			GetPlayerInfo() const { return m_tPlayerInfo; }

	HRESULT				AddExp(_uint _iExp);
	HRESULT				AddCurrMp(_int _iMp);
	D3DXVECTOR2			GetExp();

	HRESULT				SetHit(_int _iNum);


	MODE				GetMode() { return m_ePlayerMode; }

	BUILD_STATE			GetBuildState() { return m_ePlayerBulidState; }
	float				GetBuildTimeRatio();

	float				GetAbility(ABILITY eType);
	HRESULT				UpAbility(ABILITY eType);

	int					GetLevelExp();

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CPlayer* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
