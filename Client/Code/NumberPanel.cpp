#include "stdafx.h"
#include "..\Header\NumberPanel.h"
#include "../Header/NumberUI.h"

_USING(Client)

HRESULT CNumberPanel::Initialize()
{
	if (FAILED(Add_UI_Object()))
		return E_FAIL;

	return NOERROR;
}


HRESULT CNumberPanel::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CNumberPanel::Add_UI_Object()
{
	//MaxHP																																									
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-621.f, -313), nullptr, D3DXVECTOR3(1.0f, 0.75f, 0.8f)))));
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-611.f, -313), nullptr, D3DXVECTOR3(1.0f, 0.75f, 0.8f)))));
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-601.f, -313), nullptr, D3DXVECTOR3(1.0f, 0.75f, 0.8f)))));

	//CurHP
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-621.f, -209), nullptr, D3DXVECTOR3(1.0f, 0.75f, 0.8f)))));
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-611.f, -209), nullptr, D3DXVECTOR3(1.0f, 0.75f, 0.8f)))));
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-601.f, -209), nullptr, D3DXVECTOR3(1.0f, 0.75f, 0.8f)))));
	
	//CurMP
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-545.5f, -209), nullptr, D3DXVECTOR3(0.56f, 0.785f, 1.f)))));
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-535.5f, -209), nullptr, D3DXVECTOR3(0.56f, 0.785f, 1.f)))));
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-525.5f, -209), nullptr, D3DXVECTOR3(0.56f, 0.785f, 1.f)))));
																																									
	//MaxMP																																								 
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-545.5f, -313), nullptr, D3DXVECTOR3(0.56f, 0.785f, 1.f)))));
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-535.5f, -313), nullptr, D3DXVECTOR3(0.56f, 0.785f, 1.f)))));
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-525.5f, -313), nullptr, D3DXVECTOR3(0.56f, 0.785f, 1.f)))));
	//

	///////////////////////////////////스킬 아이콘
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-492, -312.5f), nullptr, D3DXVECTOR3(0.785f, 0.785f, 0.785f)))));
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-482,-312.5f), nullptr, D3DXVECTOR3(0.785f, 0.785f, 0.785f)))));
	
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-439.f, -312.5f), nullptr, D3DXVECTOR3(0.785f, 0.785f, 0.785f)))));
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-429.f, -312.5f), nullptr, D3DXVECTOR3(0.785f, 0.785f, 0.785f)))));

	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-386, -312.5f), nullptr, D3DXVECTOR3(0.785f, 0.785f, 0.785f)))));
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-376, -312.5f), nullptr, D3DXVECTOR3(0.785f, 0.785f, 0.785f)))));

	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-333, -312.5f), nullptr, D3DXVECTOR3(0.785f, 0.785f, 0.785f)))));
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-323, -312.5f), nullptr, D3DXVECTOR3(0.785f, 0.785f, 0.785f)))));

	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-281, -312.5f), nullptr, D3DXVECTOR3(0.785f, 0.785f, 0.785f)))));
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-271, -312.5f), nullptr, D3DXVECTOR3(0.785f, 0.785f, 0.785f)))));
	
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-492, -270), nullptr, D3DXVECTOR3(0.785f, 0.785f, 0.785f)))));
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-482, -270), nullptr, D3DXVECTOR3(0.785f, 0.785f, 0.785f)))));

	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-439.f, -270), nullptr, D3DXVECTOR3(0.785f, 0.785f, 0.785f)))));
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-429.f, -270), nullptr, D3DXVECTOR3(0.785f, 0.785f, 0.785f)))));

	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-386, -270), nullptr, D3DXVECTOR3(0.785f, 0.785f, 0.785f)))));
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-376, -270), nullptr, D3DXVECTOR3(0.785f, 0.785f, 0.785f)))));
																																									  
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-333, -270), nullptr, D3DXVECTOR3(0.785f, 0.785f, 0.785f)))));
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-323, -270), nullptr, D3DXVECTOR3(0.785f, 0.785f, 0.785f)))));
	
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-281, -270), nullptr, D3DXVECTOR3(0.785f, 0.785f, 0.785f)))));
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-271, -270), nullptr, D3DXVECTOR3(0.785f, 0.785f, 0.785f)))));
	////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////경험치
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-487.f, -347), nullptr, D3DXVECTOR3(1.f, 0.78f, 0.564f)))));
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-477.f, -347), nullptr, D3DXVECTOR3(1.f, 0.78f, 0.564f)))));
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-467.f, -347), nullptr, D3DXVECTOR3(1.f, 0.78f, 0.564f)))));
																																												
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-440.f, -347), nullptr, D3DXVECTOR3(1.f, 0.78f, 0.564f)))));
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-430.f, -347), nullptr, D3DXVECTOR3(1.f, 0.78f, 0.564f)))));
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-420.f, -347), nullptr, D3DXVECTOR3(1.f, 0.78f, 0.564f)))));
	///////////////////////////////////////////////////////////////9
	for (auto&iter : m_vNumIcon)
		iter->SetScale(20);
	//웨이브 스테이지
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(540.f, 299.f), nullptr, D3DXVECTOR3(0.7f, 0.7f, 0.7f)))));
	m_vNumIcon.back()->SetScale(25);
	
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(570.f, 299.f), nullptr, D3DXVECTOR3(0.7f, 0.7f, 0.7f)))));
	m_vNumIcon.back()->SetScale(25);

	////////////////////////////////////
	

	///////////////////////////////////////////// 킬수
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(548.f, 180.f), nullptr, D3DXVECTOR3(0.604f, 0.914f, 1.f)))));
	m_vNumIcon.back()->SetScale(25);																																	 
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(562.f, 180.f), nullptr, D3DXVECTOR3(0.604f, 0.914f, 1.f)))));
	m_vNumIcon.back()->SetScale(25);

	
	

	////////////////////////////////////////////////////////////웨이브 크기 36
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(290.f, 320), nullptr, D3DXVECTOR3(1.f, 0.78f, 0.564f)))));
	m_vNumIcon.back()->SetScale(36);																																  
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(307.f, 320), nullptr, D3DXVECTOR3(1.f, 0.78f, 0.564f)))));
	m_vNumIcon.back()->SetScale(36);																																 
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(324.f, 320), nullptr, D3DXVECTOR3(1.f, 0.78f, 0.564f)))));
	m_vNumIcon.back()->SetScale(36);																																  
																																									  
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(211.f, 320), nullptr, D3DXVECTOR3(1.f, 0.78f, 0.564f)))));
	m_vNumIcon.back()->SetScale(36);																																   
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(228.f, 320), nullptr, D3DXVECTOR3(1.f, 0.78f, 0.564f)))));
	m_vNumIcon.back()->SetScale(36);																																  
	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(245.f, 320), nullptr, D3DXVECTOR3(1.f, 0.78f, 0.564f)))));
	m_vNumIcon.back()->SetScale(36);

	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(266.f, 320), nullptr, D3DXVECTOR3(1.f, 0.78f, 0.564f)))));
	m_vNumIcon.back()->SetScale(36);
	m_vNumIcon.back()->SetTextureNum(11);

	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(-453.f, -347), nullptr, D3DXVECTOR3(1.f, 0.78f, 0.564f)))));
	m_vNumIcon.back()->SetScale(20);
	m_vNumIcon.back()->SetTextureNum(11);

	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(554.f, 299.f), nullptr, D3DXVECTOR3(0.7f, 0.7f, 0.7f)))));
	m_vNumIcon.back()->SetScale(25);
	m_vNumIcon.back()->SetTextureNum(11);

	//////////////////////////////////////////////

	m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(565.f, -284.f), nullptr, D3DXVECTOR3(1.f, 0.5f, 0.25f)))));
	m_vNumIcon.back()->SetScale(30);

	
	//m_vNumIcon.push_back((CNumberUI*)(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"NUMBER_UI", &DRAGPANEL(D3DXVECTOR2(565.f, -284.f), nullptr, D3DXVECTOR3(1.f, 0.5f, 0.25f)))));

	


	return NOERROR;
}

HRESULT CNumberPanel::SetPlayerInfo()
{
	CPlayer* pPlayer = (CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
	if (pPlayer == nullptr)
		return E_FAIL;

	int iMaxHP, iMaxMP, iCurrHP, iCurrMP;

	iMaxHP = pPlayer->GetPlayerInfo().iMaxHp;
	iMaxMP = pPlayer->GetPlayerInfo().iMaxMp;

	iCurrHP = pPlayer->GetPlayerInfo().iCurrHp;
	iCurrMP = pPlayer->GetPlayerInfo().iCurrMp;


	m_vNumIcon[3]->SetTextureNum(iCurrHP / 100);
	m_vNumIcon[4]->SetTextureNum(iCurrHP % 100 / 10);
	m_vNumIcon[5]->SetTextureNum(iCurrHP % 10);

	m_vNumIcon[0]->SetTextureNum(iMaxHP / 100);
	m_vNumIcon[1]->SetTextureNum(iMaxHP % 100 / 10);
	m_vNumIcon[2]->SetTextureNum(iMaxHP % 10);

	m_vNumIcon[9]->SetTextureNum(iMaxMP / 100);
	m_vNumIcon[10]->SetTextureNum(iMaxMP % 100 / 10);
	m_vNumIcon[11]->SetTextureNum(iMaxMP % 10);

	m_vNumIcon[6]->SetTextureNum(iCurrMP / 100);
	m_vNumIcon[7]->SetTextureNum(iCurrMP % 100 / 10);
	m_vNumIcon[8]->SetTextureNum(iCurrMP % 10);

	int iCurrExp, iNextExp;

	iCurrExp = pPlayer->GetPlayerInfo().iCurrExp;
	iNextExp = pPlayer->GetLevelExp();

	m_vNumIcon[32]->SetTextureNum(iMaxMP / 100);
	m_vNumIcon[33]->SetTextureNum(iMaxMP % 100 / 10);
	m_vNumIcon[34]->SetTextureNum(iMaxMP % 10);

	if (iCurrExp < 100)
	{
		if (iCurrExp < 10)
		{
			m_vNumIcon[32]->SetTextureNum(10);
			m_vNumIcon[33]->SetTextureNum(10);
			m_vNumIcon[34]->SetTextureNum(iCurrExp);
		}
		else
		{
			m_vNumIcon[32]->SetTextureNum(10);
			m_vNumIcon[33]->SetTextureNum(iCurrExp / 10);
			m_vNumIcon[34]->SetTextureNum(iCurrExp % 10);
		}
	}
	else
	{
		m_vNumIcon[32]->SetTextureNum(iCurrExp / 100);
		m_vNumIcon[33]->SetTextureNum(iCurrExp % 100 / 10);
		m_vNumIcon[34]->SetTextureNum(iCurrExp % 10);
	}



	if (iNextExp < 100)
	{
		m_vNumIcon[35]->SetTextureNum(iNextExp/10);
		m_vNumIcon[36]->SetTextureNum(iNextExp%10);
		m_vNumIcon[37]->SetTextureNum(10);
	}
	else
	{
		m_vNumIcon[35]->SetTextureNum(iNextExp / 100);
		m_vNumIcon[36]->SetTextureNum(iNextExp % 100 /10);
		m_vNumIcon[37]->SetTextureNum(iNextExp%10);
	}

	m_vNumIcon.back()->SetTextureNum(pPlayer->GetPlayerInfo().iLevel);

	return NOERROR;
}

HRESULT CNumberPanel::SetSkillMana()
{
	CPlayer* pPlayer = (CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
	if (pPlayer == nullptr)
		return E_FAIL;

	vector<int> iSkillInfo;

	for (int i = 0; i < 10; ++i)
	{
		int iMana = pPlayer->GetSkillInfo((CPlayer::SKILL)i)->fConsumeMp*(1-pPlayer->GetPlayerInfo().iAbility[CPlayer::ABILITY_MANA] * 0.03f);
		iSkillInfo.push_back(iMana);
	}

	for (int i = 0; i < 20; i += 2)
	{
		m_vNumIcon[i + 12]->SetTextureNum(iSkillInfo[i / 2] / 10);
		m_vNumIcon[i + 13]->SetTextureNum(iSkillInfo[i / 2] % 10);
	}

	return NOERROR;
}

HRESULT CNumberPanel::SetWaveInfo()
{
	CMonsterController* pMonsterController = (CMonsterController*)CGameObjectMgr::GetInstance()->FindGameObject(CManageMent::GetInstance()->GetCurrSceneID(), L"CONTROLLER");
	if (pMonsterController == nullptr)
		return E_FAIL;

	D3DXVECTOR2 vKillWave= pMonsterController->GetKillWave();
	D3DXVECTOR4 vWaveInfo = pMonsterController->GetWaveInfo();

	if (vKillWave.x < 100)
	{
		if (vKillWave.x < 10)
		{
			m_vNumIcon[45]->SetTextureNum(10);
			m_vNumIcon[46]->SetTextureNum(10);
			m_vNumIcon[47]->SetTextureNum(vKillWave.x);
		}
		else
		{
			m_vNumIcon[45]->SetTextureNum(10);
			m_vNumIcon[46]->SetTextureNum(vKillWave.x / 10);
			m_vNumIcon[47]->SetTextureNum((int)vKillWave.x % 10);
		}
	}
	else
	{
		m_vNumIcon[45]->SetTextureNum(vKillWave.x / 100);
		m_vNumIcon[46]->SetTextureNum((int)vKillWave.x % 100 / 10);
		m_vNumIcon[47]->SetTextureNum((int)vKillWave.x % 10);
	}

	if (vKillWave.y < 100)
	{
		if (vKillWave.y < 10)
		{
			m_vNumIcon[42]->SetTextureNum(vKillWave.y);
			m_vNumIcon[43]->SetTextureNum(10);
			m_vNumIcon[44]->SetTextureNum(10);
		}
		else
		{
			m_vNumIcon[42]->SetTextureNum(vKillWave.y / 10);
			m_vNumIcon[43]->SetTextureNum((int)vKillWave.y % 10);
			m_vNumIcon[44]->SetTextureNum(10);
		}
	}
	else
	{
		m_vNumIcon[42]->SetTextureNum(vKillWave.y / 100);
		m_vNumIcon[43]->SetTextureNum((int)vKillWave.y % 100 / 10);
		m_vNumIcon[44]->SetTextureNum((int)vKillWave.y % 10);
	}

	m_vNumIcon[38]->SetTextureNum((vWaveInfo.x+1));
	m_vNumIcon[39]->SetTextureNum(vWaveInfo.y);
	

	m_vNumIcon[40]->SetTextureNum(vWaveInfo.z/10);
	m_vNumIcon[41]->SetTextureNum((int)vWaveInfo.z % 10);
	



	return NOERROR;
}

HRESULT CNumberPanel::SetDefenseNum()
{
	

	return NOERROR;
}

CNumberPanel::CNumberPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CNumberPanel::CNumberPanel(const CNumberPanel & rhs)
	: CGameObject(rhs)
{
}

_int CNumberPanel::Progress(const _float & fTimeDelta)
{
	for (auto& iter : m_vNumIcon)
		iter->Progress(fTimeDelta);

	return _int();
}

_int CNumberPanel::LateProgress(const _float & fTimeDelta)
{
	for (auto& iter : m_vNumIcon)
		iter->LateProgress(fTimeDelta);

	return _int();
}

HRESULT CNumberPanel::Render()
{
	if (FAILED(SetPlayerInfo()))
		return E_FAIL;

	if (FAILED(SetSkillMana()))
		return E_FAIL;

	if (FAILED(SetWaveInfo()))
		return E_FAIL;

	for (auto& iter : m_vNumIcon)
		iter->Render();

	return NOERROR;
}

CGameObject * CNumberPanel::Clone(void * pArg)
{
	CNumberPanel*	pInstance = new CNumberPanel(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CNumberPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CNumberPanel::Free()
{
	for (auto& iter : m_vNumIcon)
		Safe_Release(iter);

	m_vNumIcon.clear();
	CGameObject::Free();
}

CNumberPanel * CNumberPanel::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CNumberPanel*	pInstance = new CNumberPanel(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CNumberPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
