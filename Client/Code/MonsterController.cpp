#include "stdafx.h"
#include "..\Header\MonsterController.h"


_USING(Client)

_int CMonsterController::Progress(const _float & fTimeDelta)
{
	switch (m_eCurrWaveState)
	{
	case WAVE_BUILD:
		WaveBuild(fTimeDelta);
		break;
	case WAVE_COMBAT:
		WaveCombat(fTimeDelta);
		break;
	case WAVE_VICTORY:
		WaveVictory(fTimeDelta);
		break;	
	}
	return _int();
}

_int CMonsterController::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CMonsterController::Render()
{
	return NOERROR;
}

HRESULT CMonsterController::CreateMonster(D3DXVECTOR3 vPosition, list<int>& _Path)
{
	return NOERROR;
}

HRESULT CMonsterController::AddLinkNum()
{
	if (m_iMonsterList == nullptr)
		return E_FAIL;

	m_iMaxMonsterNum += m_iMonsterList[m_iWaveNum].size();

	++m_iLinkNum;
	return NOERROR;
}

HRESULT CMonsterController::KillMonsterNum()
{
	if (m_iMonsterList == nullptr)
		return E_FAIL;

	++m_iKillMonsterNum;
	++m_iDefenseNum;
	return NOERROR;
}

CGameObject * CMonsterController::Clone(void * pArg)
{
	return nullptr;
}

void CMonsterController::Free()
{
	
	Safe_Delete_Arr(m_iMonsterList);

	CGameObject::Free();
}

HRESULT CMonsterController::Initialize()
{
	m_iMonsterList = new MONSTER_LIST[m_iMaxWaveNum];
	if (m_iMonsterList == nullptr)
		return E_FAIL;




	return NOERROR;
}

HRESULT CMonsterController::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CMonsterController::Initialize(void * pArg)
{
	return NOERROR;
}

HRESULT CMonsterController::MakeMonsterWave()
{
	return NOERROR;
}

HRESULT CMonsterController::WaveBuild(const _float& fTimeDelta)
{
	m_fTimeDelta += fTimeDelta;
	
	if (m_bWaveNumFlag == false && m_fTimeDelta >= 0.f)
	{
		CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"WAVE_NUM", SCENESTATIC, L"NOTICE", &m_iWaveNum);

		m_bWaveNumFlag = true;
	}

	if (m_bWaveBuildFlag == false && m_fTimeDelta >= 5.f)
	{
		CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"PHASE", SCENESTATIC, L"NOTICE", &m_eCurrWaveState);

		m_bWaveBuildFlag = true;
	}


	if (m_fTimeDelta >= 35.f && GetAsyncKeyState('B'))
	{
		m_fTimeDelta = 0.f;
		m_eCurrWaveState = WAVE_COMBAT;

		m_bWaveBuildFlag = false;
		m_bWaveNumFlag = false;
	}

	return NOERROR;
}

HRESULT CMonsterController::WaveCombat(const _float& fTimeDelta)
{
	if (m_bWaveCombatFlag == false && m_fTimeDelta >= 0.f)
	{
		CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"PHASE", SCENESTATIC, L"NOTICE", &m_eCurrWaveState);

		m_bWaveCombatFlag = true;
	}

	if (m_iKillMonsterNum >= m_iMaxMonsterNum)
	{
		m_eCurrWaveState = WAVE_VICTORY;
		m_bWaveCombatFlag = false;
	}

	return NOERROR;
}

HRESULT CMonsterController::WaveVictory(const _float& fTimeDelta)
{
	m_fTimeDelta += fTimeDelta;

	if (m_bWaveCompleteFlag == false && m_fTimeDelta >= 1.f)
	{
		CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"PHASE", SCENESTATIC, L"NOTICE", &m_eCurrWaveState);

		m_bWaveCompleteFlag = true;
	}

	if (m_fTimeDelta >= 5.f)
	{
		m_fTimeDelta = 0.f;
		m_eCurrWaveState = WAVE_BUILD;

		++m_iWaveNum;

		m_iMaxMonsterNum = m_iMonsterList[m_iWaveNum].size()*m_iLinkNum;
		m_iKillMonsterNum = 0.f;
		m_bWaveCompleteFlag = false;
	}
	return NOERROR;
}


CMonsterController::CMonsterController(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CMonsterController::CMonsterController(const CMonsterController & rhs)
	: CGameObject(rhs)
{
}
