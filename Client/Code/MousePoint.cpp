#include "stdafx.h"
#include "..\Header\MousePoint.h"


_USING(Client)

HRESULT CMousePoint::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	m_pTransform->Scaling(65, 65, 1);

	return NOERROR;
}

HRESULT CMousePoint::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CMousePoint::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADERUI", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RECT_UI", (CComponent**)&m_pBuffer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"MOUSE_POINT", (CComponent**)&m_pTexture)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;


	return NOERROR;
}

CMousePoint::CMousePoint(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CMousePoint::CMousePoint(const CMousePoint & rhs)
	: CGameObject(rhs)
{
}

_int CMousePoint::Progress(const _float & fTimeDelta)
{
	
	return _int();
}

_int CMousePoint::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::UI, this)))
		return -1;

	POINT		ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	ptMouse.y *= -1.f;

	ptMouse.x -= iWINCX*0.5f;
	ptMouse.y += iWINCY*0.5f;

	m_pTransform->SetPosition(D3DXVECTOR3(ptMouse.x, ptMouse.y-10.f, 0));

	CPlayer* pPlayer = (CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
	
	switch (pPlayer->GetMode())
	{
	case CPlayer::MODE_DEFAULT:
		m_iTexNum = 0;
		break;
	
	case CPlayer::MODE_BULID:
		m_iTexNum = 1;
		break;
	} 

	return _int();
}

HRESULT CMousePoint::Render()
{
	LPD3DXEFFECT pEffect = m_pShader->GetEffect();

	if (pEffect == nullptr)
		return E_FAIL;	

	D3DXMATRIX  matView, matProj;

	D3DXMatrixIdentity(&matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	D3DXMatrixOrthoLH(&matProj, iWINCX, iWINCY, 0.f, 1.f);

	pEffect->SetMatrix("g_matWorld", m_pTransform->GetWorldMatrix());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);
	pEffect->SetFloat("g_fUV", 0);	

	m_pTexture->SetTexture(pEffect, "g_Texture", m_iTexNum);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(0);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
}

CGameObject * CMousePoint::Clone(void * pArg)
{
	CMousePoint*	pInstance = new CMousePoint(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CMousePoint Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMousePoint::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pShader);
	Safe_Release(m_pBuffer);
	Safe_Release(m_pRenderer);
	CGameObject::Free();
}

CMousePoint * CMousePoint::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CMousePoint*	pInstance = new CMousePoint(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CMousePoint Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
