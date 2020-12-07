#include "stdafx.h"
#include "..\Header\WavePanel.h"

_USING(Client)

HRESULT CWavePanel::Initialize()
{
	if (FAILED(Add_UI_Object()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CWavePanel::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CWavePanel::Add_UI_Object()
{
	
	m_vPanel.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"WAVE_BAR_CONTENT"));
	m_vPanel.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"WAVE_INFO"));
	m_vPanel.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"WAVE_BAR"));

	
	return NOERROR;
}

CWavePanel::CWavePanel(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CWavePanel::CWavePanel(const CWavePanel & rhs)
	: CGameObject(rhs)
{
}

_int CWavePanel::Progress(const _float & fTimeDelta)
{
	for (auto& iter : m_vPanel)
		iter->Progress(fTimeDelta);

	return _int();
}

_int CWavePanel::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::UI, this)))
		return -1;

	for (auto& iter : m_vPanel)
		iter->LateProgress(fTimeDelta);

	return _int();
}

HRESULT CWavePanel::Render()
{
	for (auto& iter : m_vPanel)
		iter->Render();

	return NOERROR;
}

CGameObject * CWavePanel::Clone(void * pArg)
{
	CWavePanel*	pInstance = new CWavePanel(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CWavePanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CWavePanel::Free()
{
	Safe_Release(m_pRenderer);
	for (auto& iter : m_vPanel)
		Safe_Release(iter);

	CGameObject::Free();
}

CWavePanel * CWavePanel::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CWavePanel*	pInstance = new CWavePanel(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CWavePanel Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
