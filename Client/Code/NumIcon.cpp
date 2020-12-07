#include "stdafx.h"
#include "..\Header\NumIcon.h"


_USING(Client)
HRESULT CNumIcon::Initialize()
{
	return NOERROR;
}

HRESULT CNumIcon::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	if (pArg == nullptr)
		return E_FAIL;

	DRAGPANEL tDragPanel = *(DRAGPANEL*)pArg;

	m_vMovePanel = tDragPanel.pMovePosition;

	m_iPassNum = 8;
	m_iTexNum = 15;

	m_vScale = { 36,36 };
	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	m_vPosition = tDragPanel.vPosition;

	m_pTransform->SetPosition(D3DXVECTOR3(m_vPosition.x, m_vPosition.y, 1));

	m_vColor = tDragPanel.vColor;

	return NOERROR;
}

HRESULT CNumIcon::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CNumIcon::AddComponent()
{
	if (FAILED(CStatUI::AddComponent()))
		return E_FAIL;

	return NOERROR;
}

CNumIcon::CNumIcon(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CStatUI(_m_pGraphicDev)
{
}

CNumIcon::CNumIcon(const CNumIcon & rhs)
	: CStatUI(rhs)
{
}

_int CNumIcon::Progress(const _float & fTimeDelta)
{


	return _int(CStatUI::Progress(fTimeDelta));
}

_int CNumIcon::LateProgress(const _float & fTimeDelta)
{
	D3DXVECTOR2 vPosition = m_vPosition + *m_vMovePanel;

	m_pTransform->SetPosition(D3DXVECTOR3(vPosition.x, vPosition.y, 1));

	return _int(CStatUI::LateProgress(fTimeDelta));
}

HRESULT CNumIcon::Render()
{
	return CStatUI::Render();
}

CGameObject * CNumIcon::Clone(void * pArg)
{
	CNumIcon*	pInstance = new CNumIcon(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CNumIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

HRESULT CNumIcon::SetTextureNum(int iNum)
{
	if (iNum < 0)
		return E_FAIL;

	m_iTexNum = iNum + 15;

	return NOERROR;
}

HRESULT CNumIcon::SetScale(float fScale)
{
	m_vScale.x = fScale;
	m_vScale.y = fScale;
	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);
	return NOERROR;
}

void CNumIcon::Free()
{
	CStatUI::Free();
}

CNumIcon * CNumIcon::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CNumIcon*	pInstance = new CNumIcon(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CNumIcon Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
