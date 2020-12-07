#include "stdafx.h"
#include "..\Header\MonsterHpBar.h"
#include "../Header/MonsterHpNum.h"

_USING(Client)

HRESULT CMonsterHpBar::Initialize()
{
	return NOERROR;
}

HRESULT CMonsterHpBar::Initialize(void * pArg)
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	m_pMonster = (CMonster*)pArg;

	m_pMonsterUI_List.push_back((CMonsterUI*)CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"MONSTER_HP_FRAME", pArg));
	m_pMonsterUI_List.push_back((CMonsterUI*)CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"MONSTER_HP_CURR", pArg));
	
	return NOERROR;
}

HRESULT CMonsterHpBar::Initialize_Prototype()
{
	return NOERROR;
}

CMonsterHpBar::CMonsterHpBar(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CMonsterHpBar::CMonsterHpBar(const CMonsterHpBar & rhs)
	: CGameObject(rhs)
{
}

_int CMonsterHpBar::Progress(const _float & fTimeDelta)
{
	if (m_IsDie == true)
		return -1;

	for (auto& iter : m_pMonsterUI_List)
		iter->Progress(fTimeDelta);

	if(m_fTimeDelta<=0.5f)
		m_fTimeDelta += fTimeDelta;



	return _int();
}

_int CMonsterHpBar::LateProgress(const _float & fTimeDelta)
{
	if (m_IsDie == true)
		return -1;

	for (auto& iter : m_pMonsterUI_List)
		iter->LateProgress(fTimeDelta);

	if (m_fTimeDelta <= 0.5f)
	{
		if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::UI, this)))
			return -1;
	}

	return _int();
}

HRESULT CMonsterHpBar::Render()
{
	if (m_IsDie == true)
		return NOERROR;
	
	for (auto& iter : m_pMonsterUI_List)
		iter->Render();

	return NOERROR;
}

CGameObject * CMonsterHpBar::Clone(void * pArg)
{
	CMonsterHpBar*	pInstance = new CMonsterHpBar(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CMonsterHpBar Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMonsterHpBar::Free()
{
	Safe_Release(m_pRenderer);

	for (auto& iter : m_pMonsterUI_List)
		Safe_Release(iter);

	m_pMonsterUI_List.clear();

	CGameObject::Free();
}

CMonsterHpBar * CMonsterHpBar::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CMonsterHpBar*	pInstance = new CMonsterHpBar(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CMonsterHpBar Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
