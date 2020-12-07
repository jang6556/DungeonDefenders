#include "stdafx.h"
#include "..\Header\PointIcon.h"


_USING(Client)

HRESULT CPointIcon::Initialize()
{
	return NOERROR;
}

HRESULT CPointIcon::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	if (pArg == nullptr)
		return E_FAIL;

	DRAGPANEL tDragPanel = *(DRAGPANEL*)pArg;

	m_vMovePanel = tDragPanel.pMovePosition;

	m_iPassNum = 8;
	m_iTexNum = 7;

	m_vScale = { 125,40 };
	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	m_vPosition = tDragPanel.vPosition;

	m_pTransform->SetPosition(D3DXVECTOR3(m_vPosition.x, m_vPosition.y, 1));

	m_vColor = { 1,0.3f,0 };
	return NOERROR;
}

HRESULT CPointIcon::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CPointIcon::AddComponent()
{
	if (FAILED(CStatUI::AddComponent()))
		return E_FAIL;
	return NOERROR;
}

CPointIcon::CPointIcon(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CStatUI(_m_pGraphicDev)
{
}

CPointIcon::CPointIcon(const CPointIcon & rhs)
	: CStatUI(rhs)
{
}

_int CPointIcon::Progress(const _float & fTimeDelta)
{
	

	return _int(CStatUI::Progress(fTimeDelta));
}

_int CPointIcon::LateProgress(const _float & fTimeDelta)
{
	D3DXVECTOR2 vPosition = m_vPosition + *m_vMovePanel;

	m_pTransform->SetPosition(D3DXVECTOR3(vPosition.x, vPosition.y, 1));


	return _int(CStatUI::LateProgress(fTimeDelta));
}

HRESULT CPointIcon::Render()
{
	return CStatUI::Render();
}

CGameObject * CPointIcon::Clone(void * pArg)
{
	CPointIcon*	pInstance = new CPointIcon(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CPointIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CPointIcon::Free()
{
	CStatUI::Free();
}

CPointIcon * CPointIcon::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CPointIcon*	pInstance = new CPointIcon(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CPointIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
