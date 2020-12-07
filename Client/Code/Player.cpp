#include "stdafx.h"
#include "..\Header\Player.h"

_USING(Client)


HRESULT CPlayer::Initialize()
{
	if (FAILED(CGameObject::LoadColliderData(L"Data/Huntress.dat")))
		return E_FAIL;

	if (FAILED(AddComponent()))
		return E_FAIL;

	SetSkillInfo();
	SetLevelUpTable();

	m_pTransform->SetPosition(D3DXVECTOR3( 0, 0, -3.f));
	m_pNaviMesh->SetIndex(m_pTransform->GetPosition());

	return NOERROR;
}

HRESULT CPlayer::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	m_pTransform->Scaling(0.07f, 0.07f, 0.07f);


	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADER", (CComponent**)&m_pShader)))
		return E_FAIL;	

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"HUNTRESS", (CComponent**)&m_pMeshDynamic)))
		return E_FAIL;

	for (int i = 0; i < m_ColliderData.size(); ++i)
	{
		CCollider* pInstance = nullptr;

		switch (m_ColliderData[i]->iColliderType)
		{
		case CCollider::AABB:
			if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"COLLIDER_AABB", (CComponent**)&pInstance)))
				return E_FAIL;
			break;
		case CCollider::OBB:
			if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"COLLIDER_OBB", (CComponent**)&pInstance)))
				return E_FAIL;
			break;
		case CCollider::SPHERE:
			if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"COLLIDER_SPHERE", (CComponent**)&pInstance)))
				return E_FAIL;
			break;
		}

		if (m_pMeshDynamic != nullptr)
			pInstance->SetBoneMatrix(m_pTransform->GetWorldMatrix(), &m_ColliderData[i]->matWorld, m_pMeshDynamic->GetBoneMatrix(m_ColliderData[i]->szBoneName));

		if (pInstance != nullptr)
			m_pCollider.push_back(pInstance);
	}

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"NAVIMESH", (CComponent**)&m_pNaviMesh)))
		return E_FAIL;

	return NOERROR;
}

void CPlayer::KeyInput(const _float& fTimeDelta)
{
	if (m_ePlayerMode == MODE_BULID)
		return;
	if (m_bIsStatPanelRender == false)
	{
		if (GetAsyncKeyState('W') &&
			!GetAsyncKeyState('A') &&
			!GetAsyncKeyState('S') &&
			!GetAsyncKeyState('D'))
		{
			if (m_pNaviMesh->MoveNavigation(m_pTransform->GetPosition(), m_pTransform->GetLook(), m_tPlayerInfo.fSpeed, fTimeDelta))
				m_pTransform->MoveStraight(m_tPlayerInfo.fSpeed, fTimeDelta);

			m_pMeshDynamic->SetAnimationSet(17);
		}

		if (GetAsyncKeyState('A') /*&&(GetAsyncKeyState('I') || GetAsyncKeyState('K'))*/ && !GetAsyncKeyState('D'))
		{

			if (GetAsyncKeyState('W'))
			{
				if (m_pNaviMesh->MoveNavigation(m_pTransform->GetPosition(), m_pTransform->GetRight(), -sqrt(0.5f)*m_tPlayerInfo.fSpeed, fTimeDelta))
					m_pTransform->MoveSide(-sqrt(0.5f)*m_tPlayerInfo.fSpeed, fTimeDelta);

				if (m_pNaviMesh->MoveNavigation(m_pTransform->GetPosition(), m_pTransform->GetLook(), sqrt(0.5f)*m_tPlayerInfo.fSpeed, fTimeDelta))
					m_pTransform->MoveStraight(sqrt(0.5f)*m_tPlayerInfo.fSpeed, fTimeDelta);
			}
			else if (GetAsyncKeyState('S'))
			{
				if (m_pNaviMesh->MoveNavigation(m_pTransform->GetPosition(), m_pTransform->GetRight(), -sqrt(0.5f)*m_tPlayerInfo.fSpeed, fTimeDelta))
					m_pTransform->MoveSide(-sqrt(0.5f)*m_tPlayerInfo.fSpeed, fTimeDelta);

				if (m_pNaviMesh->MoveNavigation(m_pTransform->GetPosition(), m_pTransform->GetLook(), -sqrt(0.5f)*m_tPlayerInfo.fSpeed, fTimeDelta))
					m_pTransform->MoveStraight(-sqrt(0.5f)*m_tPlayerInfo.fSpeed, fTimeDelta);
			}
			else
			{
				if (m_pNaviMesh->MoveNavigation(m_pTransform->GetPosition(), m_pTransform->GetRight(), -m_tPlayerInfo.fSpeed, fTimeDelta))
					m_pTransform->MoveSide(-m_tPlayerInfo.fSpeed, fTimeDelta);
			}
			m_pMeshDynamic->SetAnimationSet(18);
		}

		if (!GetAsyncKeyState('W') &&
			!GetAsyncKeyState('A') &&
			GetAsyncKeyState('S') &&
			!GetAsyncKeyState('D'))
		{
			if (m_pNaviMesh->MoveNavigation(m_pTransform->GetPosition(), m_pTransform->GetLook(), -m_tPlayerInfo.fSpeed, fTimeDelta))
				m_pTransform->MoveStraight(-m_tPlayerInfo.fSpeed, fTimeDelta);

			m_pMeshDynamic->SetAnimationSet(16);
		}

		if (!GetAsyncKeyState('A') && GetAsyncKeyState('D'))
		{
			if (GetAsyncKeyState('W'))
			{
				if (m_pNaviMesh->MoveNavigation(m_pTransform->GetPosition(), m_pTransform->GetRight(), sqrt(0.5f)*m_tPlayerInfo.fSpeed, fTimeDelta))
					m_pTransform->MoveSide(sqrt(m_tPlayerInfo.fSpeed*1.5f), fTimeDelta);

				if (m_pNaviMesh->MoveNavigation(m_pTransform->GetPosition(), m_pTransform->GetLook(), sqrt(0.5f)*m_tPlayerInfo.fSpeed, fTimeDelta))
					m_pTransform->MoveStraight(sqrt(m_tPlayerInfo.fSpeed*1.5f), fTimeDelta);
			}
			else if (GetAsyncKeyState('S'))
			{
				if (m_pNaviMesh->MoveNavigation(m_pTransform->GetPosition(), m_pTransform->GetRight(), sqrt(0.5f)*m_tPlayerInfo.fSpeed, fTimeDelta))
					m_pTransform->MoveSide(sqrt(m_tPlayerInfo.fSpeed*1.5f), fTimeDelta);

				if (m_pNaviMesh->MoveNavigation(m_pTransform->GetPosition(), m_pTransform->GetLook(), -sqrt(0.5f)*m_tPlayerInfo.fSpeed, fTimeDelta))
					m_pTransform->MoveStraight(-sqrt(m_tPlayerInfo.fSpeed*1.5f), fTimeDelta);
			}
			else
			{
				if (m_pNaviMesh->MoveNavigation(m_pTransform->GetPosition(), m_pTransform->GetRight(), m_tPlayerInfo.fSpeed, fTimeDelta))
					m_pTransform->MoveSide(m_tPlayerInfo.fSpeed, fTimeDelta);
			}

			m_pMeshDynamic->SetAnimationSet(19);
		}


		if (!GetAsyncKeyState('W') && !GetAsyncKeyState('A') && !GetAsyncKeyState('S') && !GetAsyncKeyState('D') && !GetAsyncKeyState(VK_LBUTTON))
		{
			m_pMeshDynamic->SetAnimationSet(0);
		}


		if (GetAsyncKeyState(VK_LBUTTON) && m_tPlayerInfo.bShot == true)
		{
			m_tPlayerInfo.bShot = false;
			FireBullet(m_tPlayerInfo.iBulletType);
		}

		if (m_tPlayerInfo.bShot == false)
		{
			m_tPlayerInfo.fShootCool -= fTimeDelta;
			if (m_tPlayerInfo.fShootCool <= 0)
			{
				m_tPlayerInfo.fShootCool = 0.5f;
				m_tPlayerInfo.bShot = true;
			}
		}

		POINT MousePoint = { iWINCX >> 1,iWINCY >> 1 };
		ClientToScreen(g_hWnd, &MousePoint);
		SetCursorPos(MousePoint.x, MousePoint.y);


		long dwMouseMove = 0;

		if (dwMouseMove = CInputDev::GetInstance()->GetMouseMove(CInputDev::DIMM_X))
		{
			m_pTransform->RotationAxis(D3DXVECTOR3(0.f, 1.f, 0.f), D3DXToRadian(dwMouseMove) * 7.f, fTimeDelta);
		}

	}

	if (GetAsyncKeyState('I') && m_bKeyFlag == false)
	{
		m_bKeyFlag = true;
		m_bIsStatPanelRender = m_bIsStatPanelRender ? false : true;
		CStatPanel* pInstance = (CStatPanel*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"STAT_UI_PANEL");
		if (pInstance != nullptr)
			pInstance->RenderSwitch();
	}

	if (!GetAsyncKeyState('I') && m_bKeyFlag == true)
	{
		m_bKeyFlag = false;
	}
}
	

void CPlayer::BuildKeyInput(const _float& fTimeDelta)
{
	if (GetAsyncKeyState(VK_RBUTTON))
	{
		((CDecal*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER_DECAL", 0))->SetRelease();
		((CDecal*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER_DECAL", 1))->SetRelease();

		m_tPlayerInfo.iBulletType = DEFAULT;
		m_ePlayerMode = MODE_DEFAULT;
	}

	if (GetAsyncKeyState(VK_LBUTTON) && m_bBuild == false)
	{
		m_bBuild = true;

		POINT		ptMouse;
		GetCursorPos(&ptMouse);
		ScreenToClient(g_hWnd, &ptMouse);

		D3DXVECTOR3 vPoisition;

		if (m_pNaviMesh->NaviMeshPicking(ptMouse, &vPoisition) == true)
		{
			m_vBuildTarget = vPoisition;

			D3DXVECTOR3 vDir = m_vBuildTarget - m_pTransform->GetPosition();

			if (D3DXVec3Length(&vDir) < 6.f)
			{
				m_ePlayerBulidState = BUILD_ING;

				((CDecal*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER_DECAL", 0))->SetRelease();
				((CDecal*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER_DECAL", 1))->SetRelease();

				
				if (FAILED(CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"BUILD_EFFECT", SCENESTATIC, L"EFFECT", &D3DXVECTOR4(vPoisition, m_SkillInfo[m_tPlayerInfo.iBulletType].fBuildTime))))
					return;
			}			

			if (!CSoundMgr::GetSceneInst()->IsPlayingCheck(CSoundMgr::BUILD_ING))
				CSoundMgr::GetSceneInst()->PlaySound("Building.mp3", CSoundMgr::BUILD_ING);
		}
	}

	if (!GetAsyncKeyState(VK_LBUTTON) && m_bBuild == true)
		m_bBuild = false;




	long dwMouseMove = 0;

	if (dwMouseMove = CInputDev::GetInstance()->GetMouseMove(CInputDev::DIMM_X))
	{
		m_pTransform->RotationAxis(D3DXVECTOR3(0.f, 1.f, 0.f), D3DXToRadian(dwMouseMove) * 7.f, fTimeDelta);
	}
}

void CPlayer::FireBullet(BULLET eType)
{
	switch (eType)
	{
	case CPlayer::DEFAULT:
		CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"CROSSBOWARROW", SCENESTATIC, L"BULLET");

		if (!CSoundMgr::GetSceneInst()->IsPlayingCheck(CSoundMgr::BULLET))
			CSoundMgr::GetSceneInst()->PlaySound("Arrow.wav", CSoundMgr::BULLET);

		break;
	case CPlayer::FIRE:
		for(int i=0;i<10;++i)
			CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"FIREBULLET", SCENESTATIC, L"BULLET");

		if (!CSoundMgr::GetSceneInst()->IsPlayingCheck(CSoundMgr::BULLET))
			CSoundMgr::GetSceneInst()->PlaySound("DefaultBullet.wav", CSoundMgr::BULLET);
				
		m_tPlayerInfo.iBulletType = DEFAULT;
		break;
	case CPlayer::SHARP:
		CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"SHARPBULLET", SCENESTATIC, L"BULLET");

		if (!CSoundMgr::GetSceneInst()->IsPlayingCheck(CSoundMgr::BULLET))
			CSoundMgr::GetSceneInst()->PlaySound("SharpBullet.mp3", CSoundMgr::BULLET);

		m_tPlayerInfo.iBulletType = DEFAULT;
		break;
	}
}

void CPlayer::InputSkill()
{

	if (GetAsyncKeyState('1') && m_SkillInfo[SKILL_1].IsCoolTime==false && m_tPlayerInfo.iCurrMp>=m_SkillInfo[SKILL_1].fConsumeMp*GetAbility(ABILITY_MANA))
	{
		if (m_tPlayerInfo.iBulletType != FIRE)
			m_tPlayerInfo.iBulletType = FIRE;

		m_SkillInfo[SKILL_1].IsCoolTime = true;

		m_tPlayerInfo.iCurrMp -= m_SkillInfo[SKILL_1].fConsumeMp*GetAbility(ABILITY_MANA);
	}

	if (GetAsyncKeyState('2') && m_SkillInfo[SKILL_2].IsCoolTime == false && m_tPlayerInfo.iCurrMp >= m_SkillInfo[SKILL_2].fConsumeMp*GetAbility(ABILITY_MANA))
	{
		if (m_tPlayerInfo.iBulletType != SHARP)
			m_tPlayerInfo.iBulletType = SHARP;

		m_SkillInfo[SKILL_2].IsCoolTime = true;
		m_tPlayerInfo.iCurrMp -= m_SkillInfo[SKILL_2].fConsumeMp*GetAbility(ABILITY_MANA);
	}

	if (GetAsyncKeyState('3') && m_SkillInfo[SKILL_3].IsCoolTime == false && m_tPlayerInfo.iCurrMp >= m_SkillInfo[SKILL_3].fConsumeMp*GetAbility(ABILITY_MANA))
	{
		m_ePlayerMode = MODE_BULID;
		m_pMeshDynamic->SetAnimationSet(22);
		m_SkillInfo[SKILL_3].IsCoolTime = true;
	
		m_ePlayerBulidState = BUILD_READY;

		if (FAILED(CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"RANGEDECAL", SCENESTATIC, L"PLAYER_DECAL", &m_pTransform->GetPosition())))
			return;

		if (FAILED(CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"BUILDPOINT", SCENESTATIC, L"PLAYER_DECAL")))
			return;


		m_tPlayerInfo.iCurrMp -= m_SkillInfo[SKILL_3].fConsumeMp*GetAbility(ABILITY_MANA);
	}

	if (GetAsyncKeyState('0') && m_SkillInfo[SKILL_10].IsCoolTime == false && m_tPlayerInfo.iCurrMp >= m_SkillInfo[SKILL_10].fConsumeMp*GetAbility(ABILITY_MANA))
	{
		m_SkillInfo[SKILL_10].IsCoolTime = true;		

		m_tPlayerInfo.iCurrHp += m_tPlayerInfo.iMaxHp*0.2f;
		if (m_tPlayerInfo.iCurrHp >= m_tPlayerInfo.iMaxHp)
			m_tPlayerInfo.iCurrHp = m_tPlayerInfo.iMaxHp;

		m_tPlayerInfo.iCurrMp -= m_SkillInfo[SKILL_10].fConsumeMp*GetAbility(ABILITY_MANA);
	}

	
}

void CPlayer::InputBuildSkill()
{
	if (m_ePlayerMode == MODE_BULID && GetAsyncKeyState('4') && m_SkillInfo[SKILL_4].IsCoolTime == false && m_tPlayerInfo.iCurrMp >= m_SkillInfo[SKILL_4].fConsumeMp*GetAbility(ABILITY_MANA))
	{
		if (m_tPlayerInfo.iBulletType != BOMB)
			m_tPlayerInfo.iBulletType = BOMB;


		m_pMeshDynamic->SetAnimationSet(22);
		m_SkillInfo[SKILL_4].IsCoolTime = true;

		m_tPlayerInfo.iCurrMp -= m_SkillInfo[SKILL_4].fConsumeMp*GetAbility(ABILITY_MANA);
	}

	if (m_ePlayerMode == MODE_BULID && GetAsyncKeyState('5') && m_SkillInfo[SKILL_5].IsCoolTime == false && m_tPlayerInfo.iCurrMp >= m_SkillInfo[SKILL_5].fConsumeMp*GetAbility(ABILITY_MANA))
	{
		if (m_tPlayerInfo.iBulletType != POISION)
			m_tPlayerInfo.iBulletType = POISION;


		m_pMeshDynamic->SetAnimationSet(22);
		m_SkillInfo[SKILL_5].IsCoolTime = true;
		m_tPlayerInfo.iCurrMp -= m_SkillInfo[SKILL_5].fConsumeMp*GetAbility(ABILITY_MANA)*GetAbility(ABILITY_MANA);
	}

	if (m_ePlayerMode == MODE_BULID && GetAsyncKeyState('6') && m_SkillInfo[SKILL_6].IsCoolTime == false && m_tPlayerInfo.iCurrMp >= m_SkillInfo[SKILL_6].fConsumeMp*GetAbility(ABILITY_MANA)*GetAbility(ABILITY_MANA))
	{
		if (m_tPlayerInfo.iBulletType != SHIELD)
			m_tPlayerInfo.iBulletType = SHIELD;

		m_pMeshDynamic->SetAnimationSet(22);
		m_SkillInfo[SKILL_6].IsCoolTime = true;
		m_tPlayerInfo.iCurrMp -= m_SkillInfo[SKILL_6].fConsumeMp*GetAbility(ABILITY_MANA)*GetAbility(ABILITY_MANA);
	}

	if (m_ePlayerMode == MODE_BULID && GetAsyncKeyState('7') && m_SkillInfo[SKILL_7].IsCoolTime == false && m_tPlayerInfo.iCurrMp >= m_SkillInfo[SKILL_7].fConsumeMp*GetAbility(ABILITY_MANA))
	{
		if (m_tPlayerInfo.iBulletType !=MISSILE_TOWER)
			m_tPlayerInfo.iBulletType = MISSILE_TOWER;


		m_pMeshDynamic->SetAnimationSet(22);
		m_SkillInfo[SKILL_7].IsCoolTime = true;
		m_tPlayerInfo.iCurrMp -= m_SkillInfo[SKILL_7].fConsumeMp*GetAbility(ABILITY_MANA);
	}

	if (m_ePlayerMode == MODE_BULID && GetAsyncKeyState('8') && m_SkillInfo[SKILL_8].IsCoolTime == false && m_tPlayerInfo.iCurrMp >= m_SkillInfo[SKILL_8].fConsumeMp*GetAbility(ABILITY_MANA))
	{
		if (m_tPlayerInfo.iBulletType != LIGHTNING_TOWER)
			m_tPlayerInfo.iBulletType = LIGHTNING_TOWER;


		m_pMeshDynamic->SetAnimationSet(22);
		m_SkillInfo[SKILL_8].IsCoolTime = true;
		m_tPlayerInfo.iCurrMp -= m_SkillInfo[SKILL_8].fConsumeMp*GetAbility(ABILITY_MANA);
	}

	if (m_ePlayerMode == MODE_BULID && GetAsyncKeyState('9') && m_SkillInfo[SKILL_9].IsCoolTime == false && m_tPlayerInfo.iCurrMp >= m_SkillInfo[SKILL_9].fConsumeMp*GetAbility(ABILITY_MANA))
	{
		if (m_tPlayerInfo.iBulletType != STRIKE_TOWER)
			m_tPlayerInfo.iBulletType = STRIKE_TOWER;


		m_pMeshDynamic->SetAnimationSet(22);
		m_SkillInfo[SKILL_9].IsCoolTime = true;
		m_tPlayerInfo.iCurrMp -= m_SkillInfo[SKILL_9].fConsumeMp*GetAbility(ABILITY_MANA);
	}


}

void CPlayer::SetSkillInfo()
{
	m_SkillInfo[SKILL_1].fCoolTime = 3;
	m_SkillInfo[SKILL_1].fConsumeMp = 20;

	m_SkillInfo[SKILL_2].fCoolTime = 5;
	m_SkillInfo[SKILL_2].fConsumeMp = 30;

	m_SkillInfo[SKILL_3].fCoolTime = 1;
	m_SkillInfo[SKILL_3].fConsumeMp = 0;

	m_SkillInfo[SKILL_4].fCoolTime = 10;
	m_SkillInfo[SKILL_4].fConsumeMp = 30;
	m_SkillInfo[SKILL_4].fBuildTime = 2;

	m_SkillInfo[SKILL_5].fCoolTime = 5;
	m_SkillInfo[SKILL_5].fConsumeMp = 30;
	m_SkillInfo[SKILL_5].fBuildTime = 2;

	m_SkillInfo[SKILL_6].fCoolTime = 7;
	m_SkillInfo[SKILL_6].fConsumeMp = 30;
	m_SkillInfo[SKILL_6].fBuildTime = 2;

	m_SkillInfo[SKILL_7].fCoolTime = 10;
	m_SkillInfo[SKILL_7].fConsumeMp = 40;
	m_SkillInfo[SKILL_7].fBuildTime = 2.5f;

	m_SkillInfo[SKILL_8].fCoolTime = 13;
	m_SkillInfo[SKILL_8].fConsumeMp = 40;
	m_SkillInfo[SKILL_8].fBuildTime = 3;

	m_SkillInfo[SKILL_9].fCoolTime = 15;
	m_SkillInfo[SKILL_9].fConsumeMp = 50;
	m_SkillInfo[SKILL_9].fBuildTime = 4;

	m_SkillInfo[SKILL_10].fCoolTime = 10;
	m_SkillInfo[SKILL_10].fConsumeMp = 30;
	m_SkillInfo[SKILL_10].fBuildTime = 0;
}

void CPlayer::SetLevelUpTable()
{	
	//경험치,공격력,체력,마나
	m_vecLevelTable.push_back(D3DXVECTOR4(50,10, 200,300));
	m_vecLevelTable.push_back(D3DXVECTOR4(100,17,310,410));
	m_vecLevelTable.push_back(D3DXVECTOR4(180,24,430,515));
	m_vecLevelTable.push_back(D3DXVECTOR4(300,31,580,620));
	m_vecLevelTable.push_back(D3DXVECTOR4(450,38,720,730));
	m_vecLevelTable.push_back(D3DXVECTOR4(560, 46, 850, 800));
	m_vecLevelTable.push_back(D3DXVECTOR4(660, 56, 960, 910));
	m_vecLevelTable.push_back(D3DXVECTOR4(660, 56, 960, 910));
	m_vecLevelTable.push_back(D3DXVECTOR4(660, 56, 960, 910));
	m_vecLevelTable.push_back(D3DXVECTOR4(660, 56, 960, 910));

}

void CPlayer::LevelUp()
{
	if (!CSoundMgr::GetSceneInst()->IsPlayingCheck(CSoundMgr::LEVELUP))
		CSoundMgr::GetSceneInst()->PlaySound("LevelUp.ogg", CSoundMgr::LEVELUP);

	m_tPlayerInfo.iCurrExp = m_tPlayerInfo.iCurrExp- m_vecLevelTable[m_tPlayerInfo.iLevel-1].x;

	++m_tPlayerInfo.iLevel;

	m_tPlayerInfo.iAttack = m_vecLevelTable[m_tPlayerInfo.iLevel - 1].y;
	m_tPlayerInfo.iMaxHp= m_vecLevelTable[m_tPlayerInfo.iLevel - 1].z*GetAbility(ABILITY_HEALTH);
	m_tPlayerInfo.iCurrHp = m_tPlayerInfo.iMaxHp;
	m_tPlayerInfo.iMaxMp = m_vecLevelTable[m_tPlayerInfo.iLevel - 1].w;
	m_tPlayerInfo.iCurrMp = m_tPlayerInfo.iMaxMp;
	m_tPlayerInfo.iAbilityPoint += 5;	
}

void CPlayer::CoolTimeControl(const _float& fTimeDelta)
{
	for (int i = 0; i<SKILL_END; ++i)
	{
		if (m_SkillInfo[i].IsCoolTime == true)
		{
			m_SkillInfo[i].fTimeDelta += fTimeDelta;
			if (m_SkillInfo[i].fTimeDelta >= m_SkillInfo[i].fCoolTime*GetAbility(CPlayer::ABILITY_COOL))
			{
				m_SkillInfo[i].fTimeDelta = 0.f;
				m_SkillInfo[i].IsCoolTime = false;
			}
		}
	}
}

void CPlayer::BuildObject()
{
	CSoundMgr::GetSceneInst()->StopSound(CSoundMgr::BUILD_ING);
	if (!CSoundMgr::GetSceneInst()->IsPlayingCheck(CSoundMgr::BUILD_COMPLETE))
		CSoundMgr::GetSceneInst()->PlaySound("Complete.wav", CSoundMgr::BUILD_COMPLETE);

	switch (m_tPlayerInfo.iBulletType)
	{
	
	case BOMB:
		if (FAILED(CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"PRESENT_BOMB", SCENESTATIC, L"BUILD_ITEM", &m_vBuildTarget)))
			return;
		break;
	case POISION:
		if (FAILED(CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"POISION_FIELD", SCENESTATIC, L"BUILD_ITEM", &m_vBuildTarget)))
			return;
		break;		
	case SHIELD:
		if (FAILED(CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"SHIELD", SCENESTATIC, L"BUILD_OBJECT", &m_vBuildTarget)))
			return;
		break;

	case MISSILE_TOWER:
		if (FAILED(CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"MISSILE_TOWER", SCENESTATIC, L"BUILD_OBJECT", &m_vBuildTarget)))
			return;
		break;

	case LIGHTNING_TOWER:
		if (FAILED(CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"LIGHTNING_TOWER", SCENESTATIC, L"BUILD_OBJECT", &m_vBuildTarget)))
			return;
		break;

	case STRIKE_TOWER:
		if (FAILED(CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"STRIKE_TOWER", SCENESTATIC, L"BUILD_OBJECT", &m_vBuildTarget)))
			return;
		break;
	}		
}

void CPlayer::RunToBuildTarget(const _float & fTimeDelta)
{	

	D3DXVECTOR3 vDir = m_vBuildTarget - m_pTransform->GetPosition();
	if (D3DXVec3Length(&vDir) < 6.f)
	{
		m_ePlayerBulidState = BUILD_ING;
		return;
	}
	D3DXVec3Normalize(&vDir, &vDir);

	D3DXVECTOR3 vLook = m_pTransform->GetLook();
	D3DXVECTOR3 vRight = m_pTransform->GetRight();
	D3DXVec3Normalize(&vLook, &vLook);
	D3DXVec3Normalize(&vRight, &vRight);

	float fCos = D3DXVec3Dot(&vDir, &vLook);
	fCos = acos(fCos);

	float fCosRight = D3DXVec3Dot(&vDir, &vRight);

	if (fCosRight >= 0)
		m_pTransform->RotationAxis(m_pTransform->GetUp(), fCos, fTimeDelta);
	else
		m_pTransform->RotationAxis(m_pTransform->GetUp(), -fCos, fTimeDelta);


	m_pTransform->Move(vDir.x, vDir.y, vDir.z, m_tPlayerInfo.fSpeed, fTimeDelta*0.5f);
}

void CPlayer::BuildCasting(const _float & fTimeDelta)
{
	m_SkillInfo[m_tPlayerInfo.iBulletType].fCurrBuildTime += fTimeDelta;
	if (m_SkillInfo[m_tPlayerInfo.iBulletType].fCurrBuildTime >= m_SkillInfo[m_tPlayerInfo.iBulletType].fBuildTime)
	{
		BuildObject();
		m_SkillInfo[m_tPlayerInfo.iBulletType].fCurrBuildTime = 0.f;

		m_ePlayerBulidState = BUILD_READY;
		m_tPlayerInfo.iBulletType = DEFAULT;
		m_ePlayerMode = MODE_DEFAULT;
	}


}

void CPlayer::DefaultMode(const _float& fTimeDelta)
{
	KeyInput(fTimeDelta);
	InputSkill();
}

void CPlayer::BuildMode(const _float& fTimeDelta)
{
	switch (m_ePlayerBulidState)
	{
	case BUILD_READY:
	{	InputBuildSkill();
		BuildKeyInput(fTimeDelta);
		break;
	}
	case BUILD_RUN:
		RunToBuildTarget(fTimeDelta);
		break;
	case BUILD_ING:
		BuildCasting(fTimeDelta);
		break;	
	}

	if (m_ePlayerBulidState == BUILD_READY)
	{
		m_pMeshDynamic->SetAnimationSet(22);
	}

	if (m_ePlayerBulidState == BUILD_RUN)
	{
		m_pMeshDynamic->SetAnimationSet(17);
	}

	if (m_ePlayerBulidState == BUILD_ING)
	{
		m_pMeshDynamic->SetAnimationSet(22);
	}
}

CPlayer::CPlayer(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{

}

CPlayer::CPlayer(const CPlayer & rhs)
	: CGameObject(rhs),
	m_pTransform(rhs.m_pTransform),
	m_pRenderer(rhs.m_pRenderer),
	m_pShader(rhs.m_pShader),	
	m_pMeshDynamic(rhs.m_pMeshDynamic),
	m_pCollider(rhs.m_pCollider),
	m_pNaviMesh(rhs.m_pNaviMesh),
	m_vecLevelTable(rhs.m_vecLevelTable)
{	
	m_pRenderer->AddRef();
	m_pRenderer->AddRef();
	memcpy(&m_SkillInfo, &rhs.m_SkillInfo, sizeof(SKILLINFO)*SKILL_END);
}

_int CPlayer::Progress(const _float & fTimeDelta)
{
	switch (m_ePlayerMode)
	{
	case MODE_DEFAULT:
		DefaultMode(fTimeDelta);
		break;
	case MODE_BULID:
		BuildMode(fTimeDelta);
		break;	
	}		

	CoolTimeControl(fTimeDelta);

	if (GetAsyncKeyState(VK_SPACE))
		m_pTransform->SetPosition(D3DXVECTOR3( 0, 0, -3.f));
			
	return _int();
}

_int CPlayer::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::NONALPHA, this)))
		return -1;

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::DEPTH_SHADOW, this)))
		return -1;

	if (m_pMeshDynamic != nullptr)
		m_pMeshDynamic->PlayAnimation(fTimeDelta);

	
	float fHeight = m_pNaviMesh->ComputeHeight(m_pTransform->GetPosition());
	
	D3DXVECTOR3 vPosition = m_pTransform->GetPosition();
	
	vPosition.y = fHeight;
	m_pTransform->SetPosition(vPosition);

	m_pNaviMesh->SetIndex(vPosition);

	return _int();
}

HRESULT CPlayer::Render()
{
	if (GetAsyncKeyState('C'))
	{
		for(auto& iter : m_pCollider)
			iter->Render();
	}

	LPD3DXEFFECT pEffect = m_pShader->GetEffect();
	if (pEffect == nullptr)
		return E_FAIL;
	D3DXMATRIX  matView, matProj;
	
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matWorld", m_pTransform->GetWorldMatrix());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);
	
	pEffect->Begin(nullptr, 0);
	for (int j = 0; j < 1; ++j)
	{
		if (FAILED(m_pMeshDynamic->UpdateSkinnedMesh(j)))
			break;

		for (int i = 0; i < m_pMeshDynamic->GetMaterialNum(j); ++i)
		{
			if (FAILED(m_pMeshDynamic->SetShaderMeshTex(pEffect, j, i, "g_Texture", MESHTEXTURE::MESH_DIFFUSE)))
				break;

			pEffect->CommitChanges(); 
			pEffect->BeginPass(0);


			m_pMeshDynamic->Render(j, i);
			pEffect->EndPass();

		}
	}
	pEffect->End();

	if (GetAsyncKeyState('X'))
	{
		m_pNaviMesh->Render();
	}
	
	return NOERROR;
}

HRESULT CPlayer::RenderShadow()
{
	LPD3DXEFFECT pEffect = m_pShader->GetEffect();
	if (pEffect == nullptr)
		return E_FAIL;
	D3DXMATRIX  matView, matProj;

	D3DXVECTOR3 vLightPosition, vLightDirection,vLightUp;

	if (FAILED(CLightMgr::GetInstance()->GetDirectionalLight(CManageMent::GetInstance()->GetCurrSceneID(), &vLightPosition, &vLightDirection,&vLightUp)))
		return E_FAIL;

	D3DXMatrixIdentity(&matView);

	D3DXMatrixLookAtLH(&matView, &vLightPosition, &vLightDirection, &vLightUp);
	//D3DXMatrixInverse(&matView, nullptr, &matView);

	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matWorld", m_pTransform->GetWorldMatrix());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);

	pEffect->Begin(nullptr, 0);
	for (int j = 0; j < 1; ++j)
	{
		if (FAILED(m_pMeshDynamic->UpdateSkinnedMesh(j)))
			break;

		for (int i = 0; i < m_pMeshDynamic->GetMaterialNum(j); ++i)
		{
			if (FAILED(m_pMeshDynamic->SetShaderMeshTex(pEffect, j, i, "g_Texture", MESHTEXTURE::MESH_DIFFUSE)))
				break;

			pEffect->CommitChanges();
			pEffect->BeginPass(7);


			m_pMeshDynamic->Render(j, i);
			pEffect->EndPass();

		}
	}
	pEffect->End();

	return NOERROR;
}

HRESULT CPlayer::AddExp(_uint _iExp)
{
	if (_iExp < 0)
		return E_FAIL;

	m_tPlayerInfo.iCurrExp += _iExp;
	while (m_vecLevelTable[m_tPlayerInfo.iLevel - 1].x <= m_tPlayerInfo.iCurrExp)
	{
		LevelUp();
	} 
	
	return NOERROR;
}

HRESULT CPlayer::AddCurrMp(_int _iMp)
{
	if (_iMp < 0)
		return E_FAIL;

	m_tPlayerInfo.iCurrMp += _iMp;
	if (m_tPlayerInfo.iCurrMp >= m_tPlayerInfo.iMaxMp)
		m_tPlayerInfo.iCurrMp = m_tPlayerInfo.iMaxMp;

	return NOERROR;
}

D3DXVECTOR2 CPlayer::GetExp()
{
	return D3DXVECTOR2(m_tPlayerInfo.iCurrExp, m_vecLevelTable[m_tPlayerInfo.iLevel-1].x);
}

HRESULT CPlayer::SetHit(_int _iNum)
{	
	m_tPlayerInfo.iCurrHp += _iNum;
	if (m_tPlayerInfo.iCurrHp <= 0)
		m_tPlayerInfo.iCurrHp = 0;
	
	CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"BLOODEFFECT", SCENESTATIC, L"EFFECT", &POS_TARGET(*(D3DXVECTOR3*)&m_pCollider[0]->GetWorldMatrix()->m[3][0], D3DXVECTOR3(0.6392f,0,0)));


	if (m_ePlayerMode== MODE_BULID)
	{
		m_SkillInfo[m_tPlayerInfo.iBulletType].fCurrBuildTime = 0.f;

		CDecal*	pRangeDecal = (CDecal*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER_DECAL", 0);
		CDecal*	pPointDecal = (CDecal*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER_DECAL", 1);
		
		if (pRangeDecal != nullptr && pPointDecal != nullptr)
		{
			pRangeDecal->SetRelease();
			pPointDecal->SetRelease();
		}

		m_ePlayerBulidState = BUILD_READY;
		m_tPlayerInfo.iBulletType = DEFAULT;
		m_ePlayerMode = MODE_DEFAULT;
	}

	return NOERROR;
}

float CPlayer::GetBuildTimeRatio()
{	
	return m_SkillInfo[m_tPlayerInfo.iBulletType].fCurrBuildTime / m_SkillInfo[m_tPlayerInfo.iBulletType].fBuildTime;;
}

float CPlayer::GetAbility(ABILITY eType)
{
	float fPercent = 1.f;

	switch (eType)
	{
	case ABILITY_DAMAGE:
		fPercent += m_tPlayerInfo.iAbility[eType] * 0.02f;
		break;
	case ABILITY_HEALTH:
		fPercent += m_tPlayerInfo.iAbility[eType] * 0.02f;
		break;
	case ABILITY_COOL:
		fPercent -= m_tPlayerInfo.iAbility[eType] * 0.02f;
		break;
	case ABILITY_MANA:
		fPercent -= m_tPlayerInfo.iAbility[eType] * 0.03f;
		break;	
	}

	return fPercent;
}

HRESULT CPlayer::UpAbility(ABILITY eType)
{
	if (eType >= ABILITY_END)
		return E_FAIL;

	if (m_tPlayerInfo.iAbilityPoint <= 0)
		return NOERROR;

	++m_tPlayerInfo.iAbility[eType];
	--m_tPlayerInfo.iAbilityPoint;

	return NOERROR;
}

int CPlayer::GetLevelExp()
{
	return m_vecLevelTable[m_tPlayerInfo.iLevel-1].x;
}

CGameObject * CPlayer::Clone(void * pArg)
{
	return new CPlayer(*this);
}

void CPlayer::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pShader);	
	Safe_Release(m_pMeshDynamic);
	Safe_Release(m_pNaviMesh);

	for (auto& iter : m_pCollider)
		Safe_Release(iter);

	m_pCollider.clear();

	CGameObject::Free();
}

CPlayer * CPlayer::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CPlayer*	pInstance = new CPlayer(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CPlayer Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
