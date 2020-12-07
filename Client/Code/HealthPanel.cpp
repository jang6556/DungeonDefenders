#include "stdafx.h"
#include "..\Header\HealthPanel.h"


_USING(Client)
HRESULT CHealthPanel::Initialize()
{
	return NOERROR;
}

HRESULT CHealthPanel::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	if (pArg == nullptr)
		return E_FAIL;

	DRAGPANEL tDragPanel = *(DRAGPANEL*)pArg;

	m_vMovePanel = tDragPanel.pMovePosition;

	m_iPassNum = 8;
	m_iTexNum = 11;

	m_vScale = { 118 ,41 };
	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	m_vPosition = tDragPanel.vPosition;

	m_pTransform->SetPosition(D3DXVECTOR3(m_vPosition.x, m_vPosition.y, 1));

	m_vColor = { 1,0.f,0 };

	return NOERROR;
}

HRESULT CHealthPanel::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CHealthPanel::AddComponent()
{
	if (FAILED(CStatUI::AddComponent()))
		return E_FAIL;

	return NOERROR;
}

CHealthPanel::CHealthPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CStatUI(_m_pGraphicDev)
{
}

CHealthPanel::CHealthPanel(const CHealthPanel & rhs)
	: CStatUI(rhs)
{
}

_int CHealthPanel::Progress(const _float & fTimeDelta)
{
	
	return _int(CStatUI::Progress(fTimeDelta));
}

_int CHealthPanel::LateProgress(const _float & fTimeDelta)
{
	D3DXVECTOR2 vPosition = m_vPosition + *m_vMovePanel;

	m_pTransform->SetPosition(D3DXVECTOR3(vPosition.x, vPosition.y, 1));


	return _int(CStatUI::LateProgress(fTimeDelta));
}

HRESULT CHealthPanel::Render()
{
	return CStatUI::Render();
}

CGameObject * CHealthPanel::Clone(void * pArg)
{
	CHealthPanel*	pInstance = new CHealthPanel(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CHealthPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CHealthPanel::Free()
{
	CStatUI::Free();
}

CHealthPanel * CHealthPanel::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CHealthPanel*	pInstance = new CHealthPanel(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CHealthPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
