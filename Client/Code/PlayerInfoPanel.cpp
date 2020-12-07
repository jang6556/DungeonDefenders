#include "stdafx.h"
#include "..\Header\PlayerInfoPanel.h"


_USING(Client)
HRESULT CPlayerInfoPanel::Initialize()
{
	return NOERROR;
}

HRESULT CPlayerInfoPanel::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	if (pArg == nullptr)
		return E_FAIL;

	m_vMovePanel = (D3DXVECTOR2*)pArg;

	m_iPassNum = 7;
	m_iTexNum = 6;

	m_vScale = { 340,117 };
	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	m_vPosition = { 0,180 };
	m_pTransform->SetPosition(D3DXVECTOR3(m_vPosition.x, m_vPosition.y, 1));

	return NOERROR;
}

HRESULT CPlayerInfoPanel::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CPlayerInfoPanel::AddComponent()
{
	if (FAILED(CStatUI::AddComponent()))
		return E_FAIL;

	return NOERROR;
}

CPlayerInfoPanel::CPlayerInfoPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CStatUI(_m_pGraphicDev)
{
}

CPlayerInfoPanel::CPlayerInfoPanel(const CPlayerInfoPanel & rhs)
	: CStatUI(rhs)
{
}

_int CPlayerInfoPanel::Progress(const _float & fTimeDelta)
{
	

	return _int(CStatUI::Progress(fTimeDelta));
}

_int CPlayerInfoPanel::LateProgress(const _float & fTimeDelta)
{
	D3DXVECTOR2 vPosition = m_vPosition + *m_vMovePanel;

	m_pTransform->SetPosition(D3DXVECTOR3(vPosition.x, vPosition.y, 1));


	return _int(CStatUI::LateProgress(fTimeDelta));
}

HRESULT CPlayerInfoPanel::Render()
{
	return CStatUI::Render();
}

CGameObject * CPlayerInfoPanel::Clone(void * pArg)
{
	CPlayerInfoPanel*	pInstance = new CPlayerInfoPanel(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CPlayerInfoPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CPlayerInfoPanel::Free()
{
	CStatUI::Free();
}

CPlayerInfoPanel * CPlayerInfoPanel::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CPlayerInfoPanel*	pInstance = new CPlayerInfoPanel(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CPlayerInfoPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
