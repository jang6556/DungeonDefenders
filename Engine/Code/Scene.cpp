#include "..\Header\Scene.h"
#include "GameObject.h"




CScene::CScene(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	: m_pGraphicDev(_m_pGraphicDev),m_pGameObjectMgr(CGameObjectMgr::GetInstance()), m_pComponentMgr(CComponentMgr::GetInstance())
{
	m_pGraphicDev->AddRef();
	m_pGameObjectMgr->AddRef();
	m_pComponentMgr->AddRef();
}

HRESULT CScene::AddObjectPrototype(const _uint & _SceneID, const _tchar * _szTag, CGameObject * _pGameObject)
{
	if (m_pGameObjectMgr == nullptr)
		return E_FAIL;

	if (FAILED(m_pGameObjectMgr->AddObejct_Prototype(_SceneID, _szTag, _pGameObject)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CScene::AddObject(const _uint & _SceneProtoID, const _tchar * _szProtoTag, const _uint & _SceneID, const _tchar * _szTag,void* pArg)
{
	if (m_pGameObjectMgr == nullptr)
		return E_FAIL;

	if (FAILED(m_pGameObjectMgr->AddObejct(_SceneProtoID, _szProtoTag,_SceneID, _szTag, pArg)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CScene::Initialize()
{
	return NOERROR;
}

_int CScene::Progress(const _float & fTimeDelta)
{
	if (m_pGameObjectMgr == nullptr)
		return -1;

	m_pGameObjectMgr->Progress(fTimeDelta);
	return _int();
}

_int CScene::LateProgress(const _float & fTimeDelta)
{
	if (m_pGameObjectMgr == nullptr)
		return -1;

	m_pGameObjectMgr->LateProgress(fTimeDelta);
	return _int();
}

HRESULT CScene::Render()
{
	return NOERROR;
}

void CScene::Free()
{
	Safe_Release(m_pGameObjectMgr);
	Safe_Release(m_pComponentMgr);
	Safe_Release(m_pGraphicDev);	
}

