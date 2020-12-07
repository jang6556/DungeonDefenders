#include "stdafx.h"
#include "..\Header\MagnusController.h"


_USING(Client)
HRESULT CMagnusController::Initialize()
{
	m_iMaxWaveNum = 3;

	if (FAILED(CMonsterController::Initialize()))
		return E_FAIL;

	if (FAILED(MakeMonsterWave()))
		return E_FAIL;

	

	return NOERROR;
}

HRESULT CMagnusController::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CMagnusController::Initialize(void * pArg)
{
	return NOERROR;
}

HRESULT CMagnusController::MakeMonsterWave()
{
	if (m_iMonsterList == nullptr)
		return E_FAIL;

	m_iMonsterList[0].push_back(MONSTER_GOBLIN);
	m_iMonsterList[0].push_back(MONSTER_GOBLIN);
	m_iMonsterList[0].push_back(MONSTER_GOBLIN);

	m_iMonsterList[1].push_back(MONSTER_KOBOLD);
	m_iMonsterList[1].push_back(MONSTER_ARCHER);
	m_iMonsterList[1].push_back(MONSTER_GOBLIN);

	m_iMonsterList[2].push_back(MONSTER_GOBLIN);
	m_iMonsterList[2].push_back(MONSTER_ORCBRUISER);
	m_iMonsterList[2].push_back(MONSTER_KOBOLD);
	m_iMonsterList[2].push_back(MONSTER_ARCHER);



	return NOERROR;
}

CMagnusController::CMagnusController(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CMonsterController(_m_pGraphicDev)
{
}

CMagnusController::CMagnusController(const CMagnusController & rhs)
	: CMonsterController(rhs)
{
}

_int CMagnusController::Progress(const _float & fTimeDelta)
{
	
	return CMonsterController::Progress(fTimeDelta);
}

_int CMagnusController::LateProgress(const _float & fTimeDelta)
{

	
	return _int();
}

HRESULT CMagnusController::Render()
{
	return NOERROR;
}

HRESULT CMagnusController::CreateMonster(D3DXVECTOR3 vPosition, list<int>& _Path)
{
	
	if (m_iMonsterList == nullptr)
		return E_FAIL;

	if (m_eCurrWaveState != WAVE_COMBAT || m_iMonsterList[m_iWaveNum].size() == 0)
		return NOERROR;

	CGameObjectMgr* Objmgr = CGameObjectMgr::GetInstance();

	Objmgr->AddRef();

	switch (m_iMonsterList[m_iWaveNum].front())
	{
	case MONSTER_GOBLIN:
		Objmgr->AddObejct(SCENE_MAGNUS, L"GOBLIN", SCENE_MAGNUS, L"MONSTER", vPosition);
		break;

	case MONSTER_ARCHER:
		Objmgr->AddObejct(SCENE_MAGNUS, L"DARKELFARCHER", SCENE_MAGNUS, L"MONSTER", vPosition);
		break;

	case MONSTER_KOBOLD:
		Objmgr->AddObejct(SCENE_MAGNUS, L"KOBOLD", SCENE_MAGNUS, L"MONSTER", vPosition);
		break;

	case MONSTER_ORCBRUISER:
		Objmgr->AddObejct(SCENE_MAGNUS, L"ORCBRUISER", SCENE_MAGNUS, L"MONSTER", vPosition);
		break;
	}
	CMonster*	pInstance = (CMonster*)Objmgr->FindGameObject(SCENE_MAGNUS, L"MONSTER", -1);
	pInstance->SetPath(_Path);

	++m_iPopCount;

	if (m_iPopCount >= m_iLinkNum)
	{
		m_iPopCount = 0.f;
		m_iMonsterList[m_iWaveNum].pop_front();
	}

	Safe_Release(Objmgr);

	return NOERROR;
}

CGameObject * CMagnusController::Clone(void * pArg)
{
	CMagnusController*	pInstance = new CMagnusController(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CMagnusController Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMagnusController::Free()
{
	CMonsterController::Free();
}

CMagnusController * CMagnusController::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CMagnusController*	pInstance = new CMagnusController(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CMagnusController Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
