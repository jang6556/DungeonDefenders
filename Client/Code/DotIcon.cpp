#include "stdafx.h"
#include "..\Header\DotIcon.h"

_USING(Client)

HRESULT CDotIcon::Initialize()
{
	return NOERROR;
}

HRESULT CDotIcon::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	if (pArg == nullptr)
		return E_FAIL;

	DRAGPANEL tDragPanel = *(DRAGPANEL*)pArg;

	m_vMovePanel = tDragPanel.pMovePosition;

	m_iPassNum = 8;
	m_iTexNum = 9;

	m_vScale = { 44,44 };
	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	m_vPosition = tDragPanel.vPosition;

	m_pTransform->SetPosition(D3DXVECTOR3(m_vPosition.x, m_vPosition.y, 1));

	m_vColor = tDragPanel.vColor;

	return NOERROR;
}

HRESULT CDotIcon::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CDotIcon::AddComponent()
{
	if (FAILED(CStatUI::AddComponent()))
		return E_FAIL;
	return NOERROR;
}

CDotIcon::CDotIcon(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CStatUI(_m_pGraphicDev)
{
}

CDotIcon::CDotIcon(const CDotIcon & rhs)
	: CStatUI(rhs)
{
}

_int CDotIcon::Progress(const _float & fTimeDelta)
{
	
	return _int(CStatUI::Progress(fTimeDelta));
}

_int CDotIcon::LateProgress(const _float & fTimeDelta)
{
	D3DXVECTOR2 vPosition = m_vPosition + *m_vMovePanel;

	m_pTransform->SetPosition(D3DXVECTOR3(vPosition.x, vPosition.y, 1));


	return _int(CStatUI::LateProgress(fTimeDelta));
}

HRESULT CDotIcon::Render()
{
	return CStatUI::Render();
}

CGameObject * CDotIcon::Clone(void * pArg)
{
	CDotIcon*	pInstance = new CDotIcon(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CDotIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CDotIcon::Free()
{
	CStatUI::Free();
}

CDotIcon * CDotIcon::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CDotIcon*	pInstance = new CDotIcon(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CDotIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
