#include "stdafx.h"
#include "..\Header\DamageBuffer.h"


_USING(Client)

HRESULT CDamageBuffer::Initialize()
{
	return NOERROR;
}

HRESULT CDamageBuffer::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	m_vPosition = *(D3DXVECTOR4*)pArg;	

	D3DXVECTOR3 vPosition = D3DXVECTOR3(m_vPosition.x, m_vPosition.y, m_vPosition.z);

	CGameObject::ComputeZ(vPosition);

	m_fScale = CGameObject::GetZlength();
	
	if (m_fScale >= 30.f)
		m_fScale = 30.f;

	if (m_fScale <= 10)
		m_fScale = 10;

	m_fScale = 250 / m_fScale;

	m_pTransform->Scaling(m_fScale, m_fScale, 1);

	return NOERROR;
}

HRESULT CDamageBuffer::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CDamageBuffer::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADERUI", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RECT_UI", (CComponent**)&m_pBuffer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"DAMAGE_FONT", (CComponent**)&m_pTexture)))
		return E_FAIL;

	return NOERROR;
}

CDamageBuffer::CDamageBuffer(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{

}

CDamageBuffer::CDamageBuffer(const CDamageBuffer & rhs)
	: CGameObject(rhs)
{

}

_int CDamageBuffer::Progress(const _float & fTimeDelta)
{
	
	return _int();
}

_int CDamageBuffer::LateProgress(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta;

	return _int();
}

HRESULT CDamageBuffer::Render()
{
	LPD3DXEFFECT pEffect = m_pShader->GetEffect();

	if (pEffect == nullptr)
		return E_FAIL;

	D3DXMATRIX  matView, matProj;	

	D3DXMatrixIdentity(&matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	D3DXMatrixOrthoLH(&matProj, iWINCX, iWINCY, 0.f, 1.f);

	ComputePosition();	
	m_pTransform->Move(0, 50, 0, 1, m_fTimeDelta);

	pEffect->SetMatrix("g_matWorld", m_pTransform->GetWorldMatrix());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);	

	m_pTexture->SetTexture(pEffect, "g_Texture", m_vPosition.w);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(0);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
	
}

void CDamageBuffer::ComputePosition()
{
	D3DXVECTOR3 vPosition = D3DXVECTOR3(m_vPosition.x, m_vPosition.y, m_vPosition.z);

	D3DXMATRIX matView, matProj,matWorld;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMatrixIdentity(&matWorld);

	D3DVIEWPORT9		ViewPort;
	ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));

	m_pGraphicDev->GetViewport(&ViewPort);

	D3DXVECTOR3 vOut;	
	
	D3DXVec3Project(&vOut, &vPosition, &ViewPort, &matProj, &matView, &matWorld);

	vOut.y *= -1.f;

	vOut.x -= iWINCX*0.5f;
	vOut.y += iWINCY*0.5f;
	vOut.z = 0;

	SetPosition(&vOut);

	//cout << vOut.x << " " << vOut.y << endl;

	m_pTransform->SetPosition(vOut);
}

void CDamageBuffer::SetPosition(D3DXVECTOR3 * pOut)
{
	D3DXVECTOR3 vPosition = *pOut;
	switch (m_eType)
	{
	case TYPE_EVEN:
		switch (m_ePos)
		{
		case POS_THOU:
			vPosition.x -= m_fScale;
			break;
		case POS_HUN:
			vPosition.x -= m_fScale / 3.f- 10.f;
			break;
		case POS_TEN:
			vPosition.x += m_fScale / 3.f + 10.f;
			break;
		case POS_ONE:
			vPosition.x += m_fScale;
			break;
		}
		break;

	case TYPE_ODD:
		switch (m_ePos)
		{
		case POS_MILL:
			vPosition.x -= m_fScale * 4.f / 3.f;
			break;
		case POS_THOU:
			vPosition.x -= m_fScale * 2.f / 3.f;
			break;
		case POS_HUN:
			break;
		case POS_TEN:
			vPosition.x += m_fScale * 2.f / 3.f;
			break;
		case POS_ONE:
			vPosition.x += m_fScale * 4.f / 3.f;
			break;			
		}
		break;	
	}
	*pOut = vPosition;

}

CGameObject * CDamageBuffer::Clone(void * pArg)
{
	CDamageBuffer*	pInstance = new CDamageBuffer(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CDamageBuffer Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CDamageBuffer::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pShader);
	Safe_Release(m_pBuffer);
	CGameObject::Free();
}

CDamageBuffer * CDamageBuffer::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CDamageBuffer*	pInstance = new CDamageBuffer(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CDamageBuffer Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
