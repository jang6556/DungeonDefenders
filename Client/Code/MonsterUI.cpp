#include "stdafx.h"
#include "..\Header\MonsterUI.h"


_USING(Client)

HRESULT CMonsterUI::Initialize()
{
	return NOERROR;
}

HRESULT CMonsterUI::Initialize(void * pArg)
{
	return NOERROR;
}

HRESULT CMonsterUI::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CMonsterUI::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADERUI", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;	

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RECT_UI", (CComponent**)&m_pBuffer)))
		return E_FAIL;	

	return NOERROR;
}

HRESULT CMonsterUI::ComputeViewPos()
{
	CTransform* pTransform =(CTransform*)m_pMonster->GetComponent(L"TRANSFORM");
	if (pTransform == nullptr)
		return E_FAIL;

	D3DXVECTOR3 vPosition = D3DXVECTOR3(pTransform->GetPosition().x, pTransform->GetPosition().y, pTransform->GetPosition().z);

	D3DXMATRIX matView, matProj, matWorld;

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

	//cout << vOut.x << " " << vOut.y << endl;

	m_pTransform->SetPosition(vOut);


	return NOERROR;
}

CMonsterUI::CMonsterUI(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{

}

CMonsterUI::CMonsterUI(const CMonsterUI & rhs)
	:CGameObject(rhs)
{

}

_int CMonsterUI::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CMonsterUI::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CMonsterUI::Render()
{
	return NOERROR;
}

CGameObject * CMonsterUI::Clone(void * pArg)
{
	return nullptr;
}

void CMonsterUI::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pShader);	
	Safe_Release(m_pBuffer);
	CGameObject::Free();
}
