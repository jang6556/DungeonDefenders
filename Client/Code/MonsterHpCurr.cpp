#include "stdafx.h"
#include "..\Header\MonsterHpCurr.h"

_USING(Client)

HRESULT CMonsterHpCurr::Initialize()
{
	return NOERROR;
}

HRESULT CMonsterHpCurr::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	m_pMonster = (CMonster*)pArg;

	m_pTransform->Move(0.f, 2.75f, 0.f, 1.f, 1.f);

	m_fTimeDelta = 0.1f;

	m_fScale = 1.5f;

	return NOERROR;
}

HRESULT CMonsterHpCurr::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CMonsterHpCurr::AddComponent()
{
	if (FAILED(CMonsterUI::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"MONSTER_UI", (CComponent**)&m_pTexture)))
		return E_FAIL;

	return NOERROR;
}

CMonsterHpCurr::CMonsterHpCurr(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CMonsterUI(_m_pGraphicDev)
{
}

CMonsterHpCurr::CMonsterHpCurr(const CMonsterHpCurr & rhs)
	: CMonsterUI(rhs)
{
}

_int CMonsterHpCurr::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CMonsterHpCurr::LateProgress(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta*0.5f;
	if (m_fTimeDelta >= 1.f)
		m_fTimeDelta = 0.f;
	return _int();
}

HRESULT CMonsterHpCurr::Render()
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
	m_pTransform->Scaling(m_fScale, m_fScale / 4.f, 1);
	m_pTransform->SetPosition(vPostion);

	D3DXMATRIX matParents;
	D3DXMatrixIdentity(&matParents);

	memcpy(&matParents.m[3][0], &m_pMonster->GetPosition(), sizeof(D3DXVECTOR3));

	matParents = *m_pTransform->GetWorldMatrix() * matParents;

	pEffect->SetMatrix("g_matWorld", &matParents);
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);

	float fRatio = m_pMonster->GetMonsterInfo()->m_fCurrHP / m_pMonster->GetMonsterInfo()->m_fMaxHP;
	pEffect->SetFloat("g_fRatio", fRatio);
	pEffect->SetFloat("g_fU", -m_fTimeDelta);
	pEffect->SetFloat("g_fSizeX", 1.f);
	pEffect->SetFloat("g_fSizeY", 0.5f);
	
	float fRed, fGreen;
	
	fRed = (1 - fRatio)*2.f;
	if (fRed >= 1.f)
		fRed = 1.f;

	fGreen = (fRatio)*2.f;
	if (fGreen >= 1.f)
		fGreen = 1.f;

	pEffect->SetVector("g_vColor", &D3DXVECTOR4(fRed, fGreen, 0.f, 1.f));

	m_pTexture->SetTexture(pEffect, "g_Texture", 1);
	m_pTexture->SetTexture(pEffect, "g_Filter", 2);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(2);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;

}

CGameObject * CMonsterHpCurr::Clone(void * pArg)
{
	CMonsterHpCurr*	pInstance = new CMonsterHpCurr(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CMonsterHpCurr Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMonsterHpCurr::Free()
{
	CMonsterUI::Free();
}

CMonsterHpCurr * CMonsterHpCurr::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CMonsterHpCurr*	pInstance = new CMonsterHpCurr(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CMonsterHpCurr Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
