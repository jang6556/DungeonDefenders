#include "stdafx.h"
#include "..\Header\WaveBar.h"

_USING(Client)

HRESULT CWaveBar::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	
	m_pTransform->Scaling(442, 51.5f, 0);
	m_pTransform->Move(266.5f, 320.5f, 0, 1, 1);

	m_iTexNum = 2;
	m_iPassNum = 0;
}

HRESULT CWaveBar::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CWaveBar::AddComponent()
{
	if (FAILED(CPlayerUI::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADERUI", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"PANEL", (CComponent**)&m_Texture)))
		return E_FAIL;

	return NOERROR;
}

CWaveBar::CWaveBar(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	: CPlayerUI(_m_pGraphicDev)
{
}

CWaveBar::CWaveBar(const CWaveBar & rhs)
	: CPlayerUI(rhs)
{
}

_int CWaveBar::Progress(const _float & fTimeDelta)
{
	
	return _int();
}

_int CWaveBar::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CWaveBar::Render()
{
	return CPlayerUI::Render();
}

CGameObject * CWaveBar::Clone(void * pArg)
{
	CWaveBar*	pInstance = new CWaveBar(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CWaveBar Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CWaveBar::Free()
{
	CPlayerUI::Free();
}

CWaveBar * CWaveBar::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CWaveBar*	pInstance = new CWaveBar(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CWaveBar Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
