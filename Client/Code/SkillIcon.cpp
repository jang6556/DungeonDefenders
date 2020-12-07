#include "stdafx.h"
#include "..\Header\SkillIcon.h"


_USING(Client
)
HRESULT CSkillIcon::Initialize()
{
	return NOERROR;
}

HRESULT CSkillIcon::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CSkillIcon::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;	

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADER_COOL", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RECT_UI", (CComponent**)&m_pBuffer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SKILL_ICON", (CComponent**)&m_Texture)))
		return E_FAIL;
	
	return NOERROR;
}

CSkillIcon::CSkillIcon(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CSkillIcon::CSkillIcon(const CSkillIcon & rhs)
	: CGameObject(rhs)
{
}

_int CSkillIcon::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta;
	if (m_fTimeDelta >= 1)
		m_fTimeDelta = 0.f;

	return _int();
}

_int CSkillIcon::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CSkillIcon::Render()
{
	LPD3DXEFFECT pEffect = m_pShader->GetEffect();

	if (pEffect == nullptr)
		return E_FAIL;

	D3DXMATRIX  matView, matProj;

	CPlayer* pPlayer =(CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");

	float		fCool = m_pSkillInfo->fTimeDelta / (m_pSkillInfo->fCoolTime*pPlayer->GetAbility(CPlayer::ABILITY_COOL));
	if (fCool == 0)
		fCool = -1.f;
	/*if (fCool != 0)
		fCool = 1 - fCool;*/

	D3DXMatrixIdentity(&matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	D3DXMatrixOrthoLH(&matProj, iWINCX, iWINCY, 0.f, 1.f);

	pEffect->SetMatrix("g_matWorld", m_pTransform->GetWorldMatrix());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);
	pEffect->SetFloat("g_fCool", fCool);

	m_Texture->SetTexture(pEffect, "g_Texture", m_iIconNum);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(1);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
}

CGameObject * CSkillIcon::Clone(void * pArg)
{
	return nullptr;
}

void CSkillIcon::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_Texture);
	Safe_Release(m_pShader);	
	Safe_Release(m_pBuffer);
	CGameObject::Free();
}
