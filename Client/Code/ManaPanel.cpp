#include "stdafx.h"
#include "..\Header\ManaPanel.h"


_USING(Client)
HRESULT CManaPanel::Initialize()
{
	return NOERROR;
}

HRESULT CManaPanel::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	if (pArg == nullptr)
		return E_FAIL;

	DRAGPANEL tDragPanel = *(DRAGPANEL*)pArg;

	m_vMovePanel = tDragPanel.pMovePosition;

	m_iPassNum = 8;
	m_iTexNum = 13;

	m_vScale = { 103,50 };
	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	m_vPosition = tDragPanel.vPosition;

	m_pTransform->SetPosition(D3DXVECTOR3(m_vPosition.x, m_vPosition.y, 1));

	m_vColor = { 0.f,0.3f,1.f };

	return NOERROR;
}

HRESULT CManaPanel::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CManaPanel::AddComponent()
{
	if (FAILED(CStatUI::AddComponent()))
		return E_FAIL;
	return NOERROR;
}

CManaPanel::CManaPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CStatUI(_m_pGraphicDev)
{
}

CManaPanel::CManaPanel(const CManaPanel & rhs)
	: CStatUI(rhs)
{
}

_int CManaPanel::Progress(const _float & fTimeDelta)
{
	
	return _int(CStatUI::Progress(fTimeDelta));
}

_int CManaPanel::LateProgress(const _float & fTimeDelta)
{
	D3DXVECTOR2 vPosition = m_vPosition + *m_vMovePanel;

	m_pTransform->SetPosition(D3DXVECTOR3(vPosition.x, vPosition.y, 1));


	return _int(CStatUI::LateProgress(fTimeDelta));
}

HRESULT CManaPanel::Render()
{
	return CStatUI::Render();
}

CGameObject * CManaPanel::Clone(void * pArg)
{
	CManaPanel*	pInstance = new CManaPanel(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CManaPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CManaPanel::Free()
{
	CStatUI::Free();
}

CManaPanel * CManaPanel::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CManaPanel*	pInstance = new CManaPanel(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CManaPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
