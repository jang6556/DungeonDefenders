#include "..\Header\RenderTargetMgr.h"
#include "../Header/Render_Target.h"


IMPLEMENT_SINGLETON(CRenderTargetMgr);

CRenderTargetMgr::CRenderTargetMgr()
{
}

#ifdef _DEBUG
HRESULT CRenderTargetMgr::Render_Buffer(const TCHAR * szMultiTargetTag)
{
	list<CRender_Target*>*	pMultiTarget = FindMultiTarget(szMultiTargetTag);
	if (pMultiTarget == nullptr)
		return E_FAIL;	

	for (auto& iter : *pMultiTarget)
	{
		if (iter != nullptr)
			iter->Render_Buffer();
	}

	return NOERROR;
}

HRESULT CRenderTargetMgr::Initialize_Buffer(const TCHAR * szTargetTag, _float _fStartX, _float _fStartY, _float _fSizeX, _float _fSizeY)
{
	CRender_Target* pInstance = FindTarget(szTargetTag);
	if (pInstance == nullptr)
		return E_FAIL;

	return pInstance->Initialize_Buffer(_fStartX, _fStartY, _fSizeX, _fSizeY);
}
#endif

CRender_Target * CRenderTargetMgr::FindTarget(const TCHAR * szTagName)
{
	auto pInstance = find_if(m_MapTarget.begin(), m_MapTarget.end(), CFind_Tag(szTagName));
	if (pInstance == m_MapTarget.end())
		return nullptr;
		
	return pInstance->second;
}

list<CRender_Target*>* CRenderTargetMgr::FindMultiTarget(const TCHAR * szTagName)
{
	auto pInstance = find_if(m_MapMultiTarget.begin(), m_MapMultiTarget.end(), CFind_Tag(szTagName));
	if (pInstance == m_MapMultiTarget.end())
		return nullptr;

	return &pInstance->second;
}

HRESULT CRenderTargetMgr::AddRenderTarget(LPDIRECT3DDEVICE9 _m_pGraphicDev, const TCHAR * szTargetTag, _uint iWidth, _uint iHeight, D3DFORMAT eFormat, D3DXCOLOR Back_Color)
{
	CRender_Target* pInstance = FindTarget(szTargetTag);
	if (pInstance != nullptr)
		return E_FAIL;

	pInstance = CRender_Target::Create(_m_pGraphicDev, iWidth, iHeight, eFormat, Back_Color);
	if (pInstance == nullptr);

	m_MapTarget.emplace(szTargetTag, pInstance);

	return NOERROR;
}

HRESULT CRenderTargetMgr::AddMultiTarget(const TCHAR * szMultiTargetTag, const TCHAR * szTargetTag)
{
	CRender_Target*		pInstance = FindTarget(szTargetTag);
	if (pInstance == nullptr)
		return E_FAIL;

	list<CRender_Target*>*	pMultiTarget = FindMultiTarget(szMultiTargetTag);
	
	if (pMultiTarget == nullptr)
	{
		list<CRender_Target*> MultiTarget;
		MultiTarget.push_back(pInstance);

		m_MapMultiTarget.emplace(szMultiTargetTag, MultiTarget);

	}
	else
		pMultiTarget->push_back(pInstance);

	return NOERROR;
}

HRESULT CRenderTargetMgr::MultiTarget_Begin(const TCHAR * szMultiTargetTag)
{
	list<CRender_Target*>*	pMultiTarget = FindMultiTarget(szMultiTargetTag);
	if (pMultiTarget == nullptr)
		return E_FAIL;

	_uint	iIndex = 0;

	for (auto& iter : *pMultiTarget)
	{
		if (iter != nullptr)
			iter->ClearRenderTarget();
	}

	for (auto& iter : *pMultiTarget)
	{
		if (iter != nullptr)
			iter->SetRenderTarget(iIndex++);
	}

	return NOERROR;
}

HRESULT CRenderTargetMgr::MultiTarget_End(const TCHAR * szMultiTargetTag)
{
	list<CRender_Target*>*	pMultiTarget = FindMultiTarget(szMultiTargetTag);
	if (pMultiTarget == nullptr)
		return E_FAIL;

	_uint	iIndex = 0;	

	for (auto& iter : *pMultiTarget)
	{
		if (iter != nullptr)
			iter->ReleaseRenderTarget(iIndex++);
	}

	return NOERROR;
}

HRESULT CRenderTargetMgr::SetTexture(LPD3DXEFFECT pEffect, const TCHAR * szTargetTag, const char * ShaderTexName)
{
	CRender_Target*		pInstance = FindTarget(szTargetTag);
	if (pInstance == nullptr)
		return E_FAIL;	

	return pInstance->SetTexture(pEffect, ShaderTexName);
}

void CRenderTargetMgr::Free()
{
	for (auto& iter : m_MapTarget)
		Safe_Release(iter.second);

	m_MapTarget.clear();
}
