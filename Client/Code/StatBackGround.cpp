#include "stdafx.h"
#include "..\Header\StatBackGround.h"

_USING(Client)

HRESULT CStatBackGround::Initialize()
{
	

	return NOERROR;
}

HRESULT CStatBackGround::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	if (pArg == nullptr)
		return E_FAIL;

	m_vMovePanel = (D3DXVECTOR2*)pArg;

	m_iPassNum = 7;
	m_iTexNum = 0;

	m_vScale = { 400,500 };

	m_pTransform->Scaling(m_vScale.x, m_vScale.y, 1);

	m_vPosition = { 0,0 };
	m_pTransform->SetPosition(D3DXVECTOR3(m_vPosition.x, m_vPosition.y, 1));
	return NOERROR;
}

HRESULT CStatBackGround::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CStatBackGround::AddComponent()
{
	if (FAILED(CStatUI::AddComponent()))
		return E_FAIL;

	return NOERROR;
}

CStatBackGround::CStatBackGround(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CStatUI(_m_pGraphicDev)
{
}

CStatBackGround::CStatBackGround(const CStatBackGround & rhs)
	: CStatUI(rhs)
{
}

_int CStatBackGround::Progress(const _float & fTimeDelta)
{
	D3DXVECTOR2 vPosition=D3DXVECTOR2(m_vPosition.x, m_vPosition.y+ m_vScale.y*0.5f-30.f);
	D3DXVECTOR2 vScale = D3DXVECTOR2(m_vScale.x, 60.f);
	
	if (GetAsyncKeyState(VK_LBUTTON) && (m_bClick == true || true == CheckOnIcon(vPosition, vScale)))
	{
		if (m_bClick == false)
		{
			POINT		ptMouse;
			GetCursorPos(&ptMouse);
			ScreenToClient(g_hWnd, &ptMouse);

			m_vMousePoint = ptMouse;
			m_bClick = true;

			
		}
		else if (m_bClick == true)
		{
			POINT		ptMouse;
			GetCursorPos(&ptMouse);
			ScreenToClient(g_hWnd, &ptMouse);

			m_vMovePanel->x += ptMouse.x - m_vMousePoint.x;
			m_vMovePanel->y -= ptMouse.y - m_vMousePoint.y;

			m_vMousePoint = ptMouse;			
		}
	}

	if (!GetAsyncKeyState(VK_LBUTTON))
	{
		m_bClick = false;		
	}

	return _int(CStatUI::Progress(fTimeDelta));
}

_int CStatBackGround::LateProgress(const _float & fTimeDelta)
{
	m_vPosition.x = m_vMovePanel->x;
	m_vPosition.y = m_vMovePanel->y;

	m_pTransform->SetPosition(D3DXVECTOR3(m_vPosition.x, m_vPosition.y, 1));

	return _int(CStatUI::LateProgress(fTimeDelta));
}

HRESULT CStatBackGround::Render()
{
	return CStatUI::Render();
}

CGameObject * CStatBackGround::Clone(void * pArg)
{
	CStatBackGround*	pInstance = new CStatBackGround(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CStatBackGround Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CStatBackGround::Free()
{
	CStatUI::Free();
}

CStatBackGround * CStatBackGround::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CStatBackGround*	pInstance = new CStatBackGround(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CStatBackGround Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
