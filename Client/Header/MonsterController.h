#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CMonsterController :
	public CGameObject
{
public:
	enum WAVE_STATE {WAVE_BUILD,WAVE_COMBAT,WAVE_VICTORY,WAVE_END};
protected:
	list<_uint>*		m_iMonsterList = nullptr;
	typedef list<_uint> MONSTER_LIST;

	float		m_fTimeDelta = 0.f;

	_uint		m_iWaveNum = 0;
	_uint		m_iMaxWaveNum = 0;

	_uint		m_iLinkNum = 0;
	_uint		m_iPopCount = 0;

	_uint		m_iMaxMonsterNum = 0.f;
	_uint		m_iKillMonsterNum = 0.f;
	_uint		m_iDefenseNum = 0.f;

	bool		m_bWaveNumFlag = false;
	bool		m_bWaveBuildFlag = false;
	bool		m_bWaveCombatFlag = false;
	bool		m_bWaveCompleteFlag = false;

	WAVE_STATE  m_eCurrWaveState = WAVE_BUILD;
		 
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT Initialize(void* pArg);	

	virtual HRESULT	MakeMonsterWave();

	HRESULT	WaveBuild(const _float& fTimeDelta);
	HRESULT	WaveCombat(const _float& fTimeDelta);
	HRESULT	WaveVictory(const _float& fTimeDelta);

	explicit CMonsterController(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CMonsterController(const CMonsterController & rhs);
	virtual ~CMonsterController() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual HRESULT CreateMonster(D3DXVECTOR3 vPosition, list<int>& _Path);

	HRESULT AddLinkNum();
	HRESULT KillMonsterNum();

	D3DXVECTOR4	GetWaveInfo() { return D3DXVECTOR4(m_iWaveNum, m_iMaxWaveNum, m_iDefenseNum, m_eCurrWaveState); } //현재 웨이브 번호,최대 웨이브 번호, 해당씬 킬수,현재 웨이브 상태
	D3DXVECTOR2	GetKillWave() { return D3DXVECTOR2(m_iKillMonsterNum, m_iMaxMonsterNum); }

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;	
};
_END

