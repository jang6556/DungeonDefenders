#include "stdafx.h"
#include "..\Header\MonsterHpColor.h"


_USING(Client)
HRESULT CMonsterHpColor::Initialize()
{
	return NOERROR;
}

HRESULT CMonsterHpColor::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	m_pMonster = (CMonster*)pArg;

	m_pTransform->Move(0.f, 3.f, 0.f, 1.f, 1.f);
}

HRESULT CMonsterHpColor::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CMonsterHpColor::AddComponent()
{
	if (FAILED(CMonsterUI::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"MONSTER_UI", (CComponent**)&m_pTexture)))
		return E_FAIL;

	return NOERROR;
}

CMonsterHpColor::CMonsterHpColor(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CMonsterUI(_m_pGraphicDev)
{
}

CMonsterHpColor::CMonsterHpColor(const CMonsterHpColor & rhs)
	: CMonsterUI(rhs)
{
}

_int CMonsterHpColor::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CMonsterHpColor::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CMonsterHpColor::Render()
{
	LPD3DXEFFECT pEffect = m_pShader->GetEffect();

	if (pEffect == nullptr)
		return E_FAIL;

	D3DXMATRIX matWorld, matView, matProj;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	matWorld = *m_pTransform->GetWorldMatrix();

	D3DXMatrixInverse(&matWorld, nullptr, &matView);

	D3DXVECTOR3 vPostion = m_pTransform->GetPosition();

	m_pTransform->SetWorldMatrix(matWorld);
	m_pTransform->Scaling(3, 0.5f, 1);
	m_pTransform->SetPosition(vPostion);

	D3DXMATRIX matParents;
	D3DXMatrixIdentity(&matParents);

	memcpy(&matParents.m[3][0], &m_pMonster->GetPosition(), sizeof(D3DXVECTOR3));

	matParents = *m_pTransform->GetWorldMatrix() * matParents;

	pEffect->SetMatrix("g_matWorld", &matParents);
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);
	pEffect->SetFloat("g_fUV", 0);
	pEffect->SetFloat("g_fGlare", 0);
	
	m_pTexture->SetTexture(pEffect, "g_Texture", 4);	
	m_pTexture->SetTexture(pEffect, "FilterSampler_Wave", 4);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(2);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
}

CGameObject * CMonsterHpColor::Clone(void * pArg)
{
	CMonsterHpColor*	pInstance = new CMonsterHpColor(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CMonsterHpColor Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMonsterHpColor::Free()
{
	CMonsterUI::Free();
}

CMonsterHpColor * CMonsterHpColor::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CMonsterHpColor*	pInstance = new CMonsterHpColor(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CMonsterHpColor Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
