#include "stdafx.h"
#include "..\Header\MonsterHpNum.h"


_USING(Client)
HRESULT CMonsterHpNum::Initialize()
{
	return NOERROR;
}

HRESULT CMonsterHpNum::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	m_pMonster = (CMonster*)pArg;

	m_pTransform->Move(0.f, 2.73f, 0.f, 1.f, 1.f);

	m_fTimeDelta = 0.1f;

	m_fScale = 1.2;

	return NOERROR;
}

HRESULT CMonsterHpNum::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CMonsterHpNum::AddComponent()
{
	if (FAILED(CMonsterUI::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"MONSTER_FONT", (CComponent**)&m_pTexture)))
		return E_FAIL;

	return NOERROR;
}

CMonsterHpNum::CMonsterHpNum(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CMonsterUI(_m_pGraphicDev)
{

}

CMonsterHpNum::CMonsterHpNum(const CMonsterHpNum & rhs)
	: CMonsterUI(rhs)
{

}

_int CMonsterHpNum::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CMonsterHpNum::LateProgress(const _float & fTimeDelta)
{
	
	return _int();
}

HRESULT CMonsterHpNum::Render()
{
	int fMonsterHp = m_pMonster->GetMonsterInfo()->m_fCurrHP;
	if (fMonsterHp <= 0)
		return NOERROR;

	int iHundred = fMonsterHp / 100;
	if (iHundred == 0)
		iHundred = 10;

	int iTen = fMonsterHp % 100 / 10;
	if (iTen == 0 && fMonsterHp / 100 == 0)
		iTen = 10;

	int iOne = fMonsterHp % 100 % 10;

	int iTextureNum;

	switch (m_eDigit)
	{
	case DIGIT_HUNDRED:
		iTextureNum = iHundred;
		break;

	case DIGIT_TEN:
		iTextureNum = iTen;
		break;

	case DIGIT_ONE:
		iTextureNum = iOne;
		break;

	
	}


		
	
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
	m_pTransform->Scaling(m_fScale, m_fScale / 3.f, 1);
	m_pTransform->SetPosition(vPostion);
	
	D3DXMATRIX matParents;
	D3DXMatrixIdentity(&matParents);
	
	memcpy(&matParents.m[3][0], &m_pMonster->GetPosition(), sizeof(D3DXVECTOR3));
	
	matParents = *m_pTransform->GetWorldMatrix() * matParents;
	
	pEffect->SetMatrix("g_matWorld", &matParents);
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);
	pEffect->SetFloat("g_fStart", 0.2f+0.15f*m_eDigit);
	
	m_pTexture->SetTexture(pEffect, "g_Texture", iTextureNum);
	
	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(3);
	
	m_pBuffer->Render();
	
	pEffect->EndPass();
	pEffect->End();
	

	return NOERROR;
}

HRESULT CMonsterHpNum::SetDigit(DIGIT eType)
{
	if (eType >= DIGIT_END)
		return E_FAIL;

	m_eDigit = eType;

	return NOERROR;
}

CGameObject * CMonsterHpNum::Clone(void * pArg)
{
	CMonsterHpNum*	pInstance = new CMonsterHpNum(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CMonsterHpNum Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMonsterHpNum::Free()
{
	CMonsterUI::Free();
}

CMonsterHpNum * CMonsterHpNum::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CMonsterHpNum*	pInstance = new CMonsterHpNum(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CMonsterHpNum Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
