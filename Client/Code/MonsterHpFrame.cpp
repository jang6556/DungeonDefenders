#include "stdafx.h"
#include "..\Header\MonsterHpFrame.h"


_USING(Client)

HRESULT CMonsterHpFrame::Initialize()
{
	return NOERROR;
}

HRESULT CMonsterHpFrame::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	m_pMonster = (CMonster*)pArg;

	m_pTransform->Move(0.f, 2.75f, 0.f, 1.f, 1.f);

	m_fScale = 1.5f;
	return NOERROR;
}

HRESULT CMonsterHpFrame::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CMonsterHpFrame::AddComponent()
{
	if (FAILED(CMonsterUI::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"MONSTER_UI", (CComponent**)&m_pTexture)))
		return E_FAIL;
	return NOERROR;
}

CMonsterHpFrame::CMonsterHpFrame(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CMonsterUI(_m_pGraphicDev)
{
}

CMonsterHpFrame::CMonsterHpFrame(const CMonsterHpFrame & rhs)
	: CMonsterUI(rhs)
{
}

_int CMonsterHpFrame::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CMonsterHpFrame::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CMonsterHpFrame::Render()
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
	m_pTransform->Scaling(m_fScale, m_fScale/4.f, 1);
	m_pTransform->SetPosition(vPostion);

	D3DXMATRIX matParents;
	D3DXMatrixIdentity(&matParents);

	memcpy(&matParents.m[3][0], &m_pMonster->GetPosition(), sizeof(D3DXVECTOR3));

	matParents = *m_pTransform->GetWorldMatrix() * matParents;

	pEffect->SetMatrix("g_matWorld", &matParents);
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);
	pEffect->SetFloat("g_fUV", 0);

	m_pTexture->SetTexture(pEffect, "g_Texture", 0);
	m_pTexture->SetTexture(pEffect, "g_AlphaTexture", 1);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(6);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
}

CGameObject * CMonsterHpFrame::Clone(void * pArg)
{
	CMonsterHpFrame*	pInstance = new CMonsterHpFrame(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CMonsterHpFrame Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMonsterHpFrame::Free()
{
	CMonsterUI::Free();
}

CMonsterHpFrame * CMonsterHpFrame::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CMonsterHpFrame*	pInstance = new CMonsterHpFrame(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CMonsterHpFrame Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
