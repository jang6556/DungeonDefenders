#include "stdafx.h"
#include "..\Header\CoolPanel.h"


_USING(Client)

HRESULT CCoolPanel::Initialize()
{
	return NOERROR;
}

HRESULT CCoolPanel::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	if (pArg == nullptr)
		return E_FAIL;

	DRAGPANEL tDragPanel = *(DRAGPANEL*)pArg;

	m_vMovePanel = tDragPanel.pMovePosition;

	m_iPassNum = 8;
	m_iTexNum = 12;

	m_vScale = { 105,50 };
	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	m_vPosition = tDragPanel.vPosition;

	m_pTransform->SetPosition(D3DXVECTOR3(m_vPosition.x, m_vPosition.y, 1));

	m_vColor = { 0.0f,0.7f,0.f };

	return NOERROR;
}

HRESULT CCoolPanel::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CCoolPanel::AddComponent()
{
	if (FAILED(CStatUI::AddComponent()))
		return E_FAIL;
	return NOERROR;
}

CCoolPanel::CCoolPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CStatUI(_m_pGraphicDev)
{
}

CCoolPanel::CCoolPanel(const CCoolPanel & rhs)
	: CStatUI(rhs)
{
}

_int CCoolPanel::Progress(const _float & fTimeDelta)
{
	
	return _int(CStatUI::Progress(fTimeDelta));
}

_int CCoolPanel::LateProgress(const _float & fTimeDelta)
{
	D3DXVECTOR2 vPosition = m_vPosition + *m_vMovePanel;

	m_pTransform->SetPosition(D3DXVECTOR3(vPosition.x, vPosition.y, 1));


	return _int(CStatUI::LateProgress(fTimeDelta));
}

HRESULT CCoolPanel::Render()
{
	return CStatUI::Render();
}

CGameObject * CCoolPanel::Clone(void * pArg)
{
	CCoolPanel*	pInstance = new CCoolPanel(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CCoolPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCoolPanel::Free()
{
	CStatUI::Free();
}

CCoolPanel * CCoolPanel::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CCoolPanel*	pInstance = new CCoolPanel(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CCoolPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
