#include "stdafx.h"
#include "..\Header\PercentIcon.h"


_USING(Client)

HRESULT CPercentIcon::Initialize()
{
	return NOERROR;
}

HRESULT CPercentIcon::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	if (pArg == nullptr)
		return E_FAIL;

	DRAGPANEL tDragPanel = *(DRAGPANEL*)pArg;

	m_vMovePanel = tDragPanel.pMovePosition;

	m_iPassNum = 8;
	m_iTexNum = 25;

	m_vScale = { 44,44 };
	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	m_vPosition = tDragPanel.vPosition;

	m_pTransform->SetPosition(D3DXVECTOR3(m_vPosition.x, m_vPosition.y, 1));

	m_vColor = tDragPanel.vColor;

	return NOERROR;
}

HRESULT CPercentIcon::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CPercentIcon::AddComponent()
{
	if (FAILED(CStatUI::AddComponent()))
		return E_FAIL;
	return NOERROR;
}

CPercentIcon::CPercentIcon(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CStatUI(_m_pGraphicDev)
{
}

CPercentIcon::CPercentIcon(const CPercentIcon & rhs)
	: CStatUI(rhs)
{
}

_int CPercentIcon::Progress(const _float & fTimeDelta)
{	
	return _int(CStatUI::Progress(fTimeDelta));
}

_int CPercentIcon::LateProgress(const _float & fTimeDelta)
{
	D3DXVECTOR2 vPosition = m_vPosition + *m_vMovePanel;

	m_pTransform->SetPosition(D3DXVECTOR3(vPosition.x, vPosition.y, 1));


	return _int(CStatUI::LateProgress(fTimeDelta));
}

HRESULT CPercentIcon::Render()
{
	return CStatUI::Render();
}

CGameObject * CPercentIcon::Clone(void * pArg)
{
	CPercentIcon*	pInstance = new CPercentIcon(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CPercentIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CPercentIcon::Free()
{
	CStatUI::Free();
}

CPercentIcon * CPercentIcon::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CPercentIcon*	pInstance = new CPercentIcon(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CPercentIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
