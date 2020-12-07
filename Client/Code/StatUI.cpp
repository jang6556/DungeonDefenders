#include "stdafx.h"
#include "..\Header\StatUI.h"


_USING(Client)
HRESULT CStatUI::Initialize()
{
	return NOERROR;
}

HRESULT CStatUI::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CStatUI::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADERUI", (CComponent**)&m_pShader)))
		return E_FAIL;
	
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RECT_UI", (CComponent**)&m_pBuffer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"STAT_UI", (CComponent**)&m_Texture)))
		return E_FAIL;

	return NOERROR;
}

bool CStatUI::CheckOnIcon(D3DXVECTOR2	_vPosition, D3DXVECTOR2 _vScale)
{
	POINT		ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	ptMouse.x -= iWINCX*0.5f;
	ptMouse.y -= iWINCY*0.5f;
	ptMouse.y *= -1.f;	

	RECT rcIcon;

	rcIcon.left =  _vPosition.x - _vScale.x*0.5f;
	rcIcon.right = _vPosition.x + _vScale.x*0.5f;

	rcIcon.top =    _vPosition.y + _vScale.y*0.5f;
	rcIcon.bottom = _vPosition.y - _vScale.y*0.5f;

	if (ptMouse.x < rcIcon.left)
		return false;

	if (ptMouse.x > rcIcon.right)
		return false;

	if (ptMouse.y > rcIcon.top)
		return false;

	if (ptMouse.y < rcIcon.bottom)
		return false;

	return true;
}

CStatUI::CStatUI(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{

}

CStatUI::CStatUI(const CStatUI & rhs)
	: CGameObject(rhs)
{

}

_int CStatUI::Progress(const _float & fTimeDelta)
{
	m_fAlpha += fTimeDelta*m_iAlphaFlag;
	
	if (m_fAlpha >= 1.f)
		m_fAlpha = 1.f;
	
	if (m_fAlpha <= 0.f)
		m_fAlpha = 0.f;

	return _int();
}

_int CStatUI::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CStatUI::Render()
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

	if(m_iPassNum==8)
		pEffect->SetVector("g_vColor", &D3DXVECTOR4(m_vColor,1));

	m_Texture->SetTexture(pEffect, "g_Texture", m_iTexNum);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(m_iPassNum);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
}

HRESULT CStatUI::RenderSwitch()
{
	m_iAlphaFlag *= -1;

	return NOERROR;
}

CGameObject * CStatUI::Clone(void * pArg)
{
	return nullptr;
}

void CStatUI::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_Texture);
	Safe_Release(m_pShader);
	Safe_Release(m_pBuffer);
	CGameObject::Free();
}
