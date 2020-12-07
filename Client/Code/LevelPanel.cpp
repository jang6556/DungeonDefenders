#include "stdafx.h"
#include "..\Header\LevelPanel.h"


_USING(Client)
HRESULT CLevelPanel::Initialize()
{
	return NOERROR;
}

HRESULT CLevelPanel::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	if (pArg == nullptr)
		return E_FAIL;

	DRAGPANEL tDragPanel = *(DRAGPANEL*)pArg;

	m_vMovePanel = tDragPanel.pMovePosition;

	m_iPassNum = 8;
	m_iTexNum = 26;

	m_vScale = { 80 ,32 };
	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	m_vPosition = tDragPanel.vPosition;

	m_pTransform->SetPosition(D3DXVECTOR3(m_vPosition.x, m_vPosition.y, 1));

	m_vColor = { 1,1.f,0 };

	return NOERROR;	
}

HRESULT CLevelPanel::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CLevelPanel::AddComponent()
{
	if (FAILED(CStatUI::AddComponent()))
		return E_FAIL;

	return NOERROR;
}

CLevelPanel::CLevelPanel(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CStatUI(_m_pGraphicDev)
{
}

CLevelPanel::CLevelPanel(const CLevelPanel & rhs)
	: CStatUI(rhs)
{
}

_int CLevelPanel::Progress(const _float & fTimeDelta)
{	
	return _int(CStatUI::Progress(fTimeDelta));
}

_int CLevelPanel::LateProgress(const _float & fTimeDelta)
{
	D3DXVECTOR2 vPosition = m_vPosition + *m_vMovePanel;

	m_pTransform->SetPosition(D3DXVECTOR3(vPosition.x, vPosition.y, 1));


	return _int(CStatUI::LateProgress(fTimeDelta));
}

HRESULT CLevelPanel::Render()
{
	return CStatUI::Render();
}

CGameObject * CLevelPanel::Clone(void * pArg)
{
	CLevelPanel*	pInstance = new CLevelPanel(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CLevelPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevelPanel::Free()
{
	CStatUI::Free();
}

CLevelPanel * CLevelPanel::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CLevelPanel*	pInstance = new CLevelPanel(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CLevelPanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
