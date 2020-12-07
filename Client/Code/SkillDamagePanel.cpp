#include "stdafx.h"
#include "..\Header\SkillDamagePanel.h"


_USING(Client)

HRESULT CSkillDamagePanel::Initialize()
{
	return NOERROR;
}

HRESULT CSkillDamagePanel::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	if (pArg == nullptr)
		return E_FAIL;

	DRAGPANEL tDragPanel = *(DRAGPANEL*)pArg;

	m_vMovePanel = tDragPanel.pMovePosition;

	m_iPassNum = 8;
	m_iTexNum = 14;

	m_vScale = { 93,46 };
	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	m_vPosition = tDragPanel.vPosition;

	m_pTransform->SetPosition(D3DXVECTOR3(m_vPosition.x, m_vPosition.y, 1));

	m_vColor = { 1.f,0.8f,0.1f };

	return NOERROR;
}

HRESULT CSkillDamagePanel::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CSkillDamagePanel::AddComponent()
{
	if (FAILED(CStatUI::AddComponent()))
		return E_FAIL;
	return NOERROR;
}

CSkillDamagePanel::CSkillDamagePanel(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CStatUI(_m_pGraphicDev)
{
}

CSkillDamagePanel::CSkillDamagePanel(const CSkillDamagePanel & rhs)
	: CStatUI(rhs)
{
}

_int CSkillDamagePanel::Progress(const _float & fTimeDelta)
{
	return _int(CStatUI::Progress(fTimeDelta));
}

_int CSkillDamagePanel::LateProgress(const _float & fTimeDelta)
{
	D3DXVECTOR2 vPosition = m_vPosition + *m_vMovePanel;

	m_pTransform->SetPosition(D3DXVECTOR3(vPosition.x, vPosition.y, 1));


	return _int(CStatUI::LateProgress(fTimeDelta));
}

HRESULT CSkillDamagePanel::Render()
{
	return CStatUI::Render();
}

CGameObject * CSkillDamagePanel::Clone(void * pArg)
{
	CSkillDamagePanel*	pInstance = new CSkillDamagePanel(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CSkillDamagePanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CSkillDamagePanel::Free()
{
	CStatUI::Free();
}

CSkillDamagePanel * CSkillDamagePanel::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CSkillDamagePanel*	pInstance = new CSkillDamagePanel(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CSkillDamagePanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
