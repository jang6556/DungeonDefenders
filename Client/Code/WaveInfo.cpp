#include "stdafx.h"
#include "..\Header\WaveInfo.h"


_USING(Client)
HRESULT CWaveInfo::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	m_pTransform->Scaling(181.5f,204, 0);
	m_pTransform->Move(552.5f, 257.5f, 0, 1, 1);

	m_iTexNum = 10;
	m_iPassNum = 0;
}

HRESULT CWaveInfo::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CWaveInfo::AddComponent()
{
	if (FAILED(CPlayerUI::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADERUI", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"PANEL", (CComponent**)&m_Texture)))
		return E_FAIL;

	return NOERROR;
}

CWaveInfo::CWaveInfo(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CPlayerUI(_m_pGraphicDev)
{
}

CWaveInfo::CWaveInfo(const CWaveInfo & rhs)
	: CPlayerUI(rhs)
{
}

_int CWaveInfo::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CWaveInfo::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CWaveInfo::Render()
{
	return CPlayerUI::Render();
}

CGameObject * CWaveInfo::Clone(void * pArg)
{
	CWaveInfo*	pInstance = new CWaveInfo(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CWaveInfo Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CWaveInfo::Free()
{
	CPlayerUI::Free();
}

CWaveInfo * CWaveInfo::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CWaveInfo*	pInstance = new CWaveInfo(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CWaveInfo Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
