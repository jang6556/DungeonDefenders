#include "stdafx.h"
#include "..\Header\EmptyPanel.h"


_USING(Client)

HRESULT CEmptyPanel::Initialize()
{
	return NOERROR;
}

HRESULT CEmptyPanel::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	if (pArg == nullptr)
		return E_FAIL;

	DRAGPANEL tDragPanel = *(DRAGPANEL*)pArg;

	m_vMovePanel = tDragPanel.pMovePosition;

	m_iPassNum = 7;
	m_iTexNum = 5;

	m_vScale = { 50,30 };
	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	m_vPosition = tDragPanel.vPosition;	

	m_pTransform->SetPosition(D3DXVECTOR3(m_vPosition.x, m_vPosition.y, 1));

	return NOERROR;
}

HRESULT CEmptyPanel::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CEmptyPanel::AddComponent()
{
	if (FAILED(CStatUI::AddComponent()))
		return E_FAIL;

	return NOERROR;
}

CEmptyPanel::CEmptyPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev) 
	:CStatUI(_m_pGraphicDev)
{
}

CEmptyPanel::CEmptyPanel(const CEmptyPanel & rhs)
	: CStatUI(rhs)
{
}

_int CEmptyPanel::Progress(const _float & fTimeDelta)
{
	

	return _int(CStatUI::Progress(fTimeDelta));
}

_int CEmptyPanel::LateProgress(const _float & fTimeDelta)
{
	D3DXVECTOR2 vPosition = m_vPosition + *m_vMovePanel;

	m_pTransform->SetPosition(D3DXVECTOR3(vPosition.x, vPosition.y, 1));


	return _int(CStatUI::LateProgress(fTimeDelta));
}

HRESULT CEmptyPanel::Render()
{
	return CStatUI::Render();
}

CGameObject * CEmptyPanel::Clone(void * pArg)
{
	CEmptyPanel*	pInstance = new CEmptyPanel(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CEmptyPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CEmptyPanel::Free()
{
	CStatUI::Free();
}

CEmptyPanel * CEmptyPanel::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CEmptyPanel*	pInstance = new CEmptyPanel(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CEmptyPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
