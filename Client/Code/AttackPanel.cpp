#include "stdafx.h"
#include "..\Header\AttackPanel.h"


_USING(Client)
HRESULT CAttackPanel::Initialize()
{
	return NOERROR;
}

HRESULT CAttackPanel::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	if (pArg == nullptr)
		return E_FAIL;

	DRAGPANEL tDragPanel = *(DRAGPANEL*)pArg;

	m_vMovePanel = tDragPanel.pMovePosition;

	m_iPassNum = 8;
	m_iTexNum = 10;

	m_vScale = { 117,50.5f };
	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	m_vPosition = tDragPanel.vPosition;

	m_pTransform->SetPosition(D3DXVECTOR3(m_vPosition.x, m_vPosition.y, 1));

	m_vColor = { 1.f,1.f,1.f };

	return NOERROR;
}

HRESULT CAttackPanel::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CAttackPanel::AddComponent()
{
	if (FAILED(CStatUI::AddComponent()))
		return E_FAIL;
	return NOERROR;
}

CAttackPanel::CAttackPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CStatUI(_m_pGraphicDev)
{
}

CAttackPanel::CAttackPanel(const CAttackPanel & rhs)
	: CStatUI(rhs)
{
}

_int CAttackPanel::Progress(const _float & fTimeDelta)
{

	return _int(CStatUI::Progress(fTimeDelta));
}

_int CAttackPanel::LateProgress(const _float & fTimeDelta)
{
	D3DXVECTOR2 vPosition = m_vPosition + *m_vMovePanel;

	m_pTransform->SetPosition(D3DXVECTOR3(vPosition.x, vPosition.y, 1));


	return _int(CStatUI::LateProgress(fTimeDelta));
}

HRESULT CAttackPanel::Render()
{
	return CStatUI::Render();
}

CGameObject * CAttackPanel::Clone(void * pArg)
{
	CAttackPanel*	pInstance = new CAttackPanel(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CAttackPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CAttackPanel::Free()
{
	CStatUI::Free();
}

CAttackPanel * CAttackPanel::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CAttackPanel*	pInstance = new CAttackPanel(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CAttackPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
