#include "..\Header\GameObjectMgr.h"
#include "..\Header\GameObject.h"
#include "Layer.h"


IMPLEMENT_SINGLETON(CGameObjectMgr)

CGameObject * CGameObjectMgr::FindPrototype(const _uint SceneID, const _tchar * _szTag)
{
	if (iMaxSceneNum <= SceneID || 
		m_pMapPrototype == nullptr)
	{
		return nullptr;
	}

	auto iter = find_if(m_pMapPrototype[SceneID].begin(),
		m_pMapPrototype[SceneID].end(),
		CFind_Tag(_szTag));

	if (iter == m_pMapPrototype[SceneID].end())
		return nullptr;

	return iter->second;
}

CLayer * CGameObjectMgr::FindLayer(const _uint SceneID, const _tchar * _szTag)
{
	if (SceneID >= iMaxSceneNum || m_pMapObject == nullptr)
		return nullptr;

	auto iter = find_if(m_pMapObject[SceneID].begin(),
		m_pMapObject[SceneID].end(),
		CFind_Tag(_szTag));

	if (iter == m_pMapObject[SceneID].end())
		return nullptr;

	return iter->second;
}

CGameObjectMgr::CGameObjectMgr()
{
}

HRESULT CGameObjectMgr::ReserveMaxScene(const _uint & SceneNum)
{
	if(m_pMapPrototype != nullptr)
		return E_FAIL;

	m_pMapPrototype = new MAPPROTOTYPE[SceneNum];

	m_pMapObject = new MAPOBJECT[SceneNum];

	iMaxSceneNum = SceneNum;

	return NOERROR;
}

HRESULT CGameObjectMgr::AddObejct_Prototype(const _uint & SceneID, const _tchar * _szTag, CGameObject * _GameObject)
{
	if (m_pMapPrototype == nullptr || SceneID>=iMaxSceneNum || _GameObject==nullptr)
		return E_FAIL;

	CGameObject* pGameObject = FindPrototype(SceneID, _szTag);

	if (pGameObject != nullptr)
		return E_FAIL;

	m_pMapPrototype[SceneID].insert(MAPPROTOTYPE::value_type(_szTag, _GameObject));

	return NOERROR;
}

HRESULT CGameObjectMgr::AddObejct(const _uint & SceneProtoID, const _tchar * _szProtoTag, const _uint & SceneID, const _tchar * _szTag,  void* pArg)
{
	CGameObject*	pProtoType = FindPrototype(SceneProtoID, _szProtoTag);

	if (pProtoType == nullptr)
		return E_FAIL;

	CGameObject*	pGameObject = pProtoType->Clone(pArg);

	if (pGameObject == nullptr)
		return E_FAIL;

	CLayer*			pLayer = FindLayer(SceneID, _szTag);

	if (pLayer == nullptr)
	{
		pLayer = CLayer::Create();
		if (pLayer == nullptr)
			return E_FAIL;

		if (FAILED(pLayer->AddObject(pGameObject)))
			return E_FAIL;

		m_pMapObject[SceneID].emplace(_szTag, pLayer);
	}
	else
	{
		if (FAILED(pLayer->AddObject(pGameObject)))
			return E_FAIL;
	}

	return NOERROR;
}

CGameObject * CGameObjectMgr::GetGameObject(const _uint & SceneProtoID, const _tchar * _szProtoTag, void* pArg)
{
	CGameObject*	pProtoType = FindPrototype(SceneProtoID, _szProtoTag);

	if (pProtoType == nullptr)
		return nullptr;

	
	CGameObject*	pGameObject = pProtoType->Clone(pArg);

	if (pGameObject == nullptr)
		return nullptr;

	return pGameObject;
}

CGameObject * CGameObjectMgr::FindGameObject(const _uint & SceneProtoID, const _tchar * _szProtoTag, int iNum)
{
	CLayer*			pLayer = FindLayer(SceneProtoID, _szProtoTag);

	if (pLayer == nullptr)
		return nullptr;

	if (iNum == -1)
		return pLayer->GetObjList()->back();

	auto& iter = pLayer->GetObjList()->begin();
	for (int i = 0; i < iNum; ++i)
	{
		++iter;
	}
	if (iter == pLayer->GetObjList()->end())
		return nullptr;
	

	return (*iter);
}

CComponent * CGameObjectMgr::FindComponent(const _uint & SceneProtoID, const _tchar * _szProtoTag, const _tchar * _szProtoComponentTag,int iNum)
{
	CLayer*			pLayer = FindLayer(SceneProtoID, _szProtoTag);

	if (pLayer == nullptr)
		return nullptr;

	CComponent*	pInstance = nullptr;
	if (iNum != -1.f)
	{
		auto& iter = pLayer->GetObjList()->begin();
		for (int i = 0; i < iNum; ++i)
		{
			++iter;
		}
		if (iter == pLayer->GetObjList()->end())
			return nullptr;

		pInstance = (*iter)->GetComponent(_szProtoComponentTag);
		if (pInstance == nullptr)
			return nullptr;
	}
	else if (iNum == -1.f)
	{
		pInstance = pLayer->GetObjList()->back()->GetComponent(_szProtoComponentTag);
		if (pInstance == nullptr)
			return nullptr;
	}
		
	return pInstance;
}

list<CGameObject*> *	 CGameObjectMgr::GetLayer(const _uint & SceneProtoID, const _tchar * _szTag)
{
	CLayer*			pLayer = FindLayer(SceneProtoID, _szTag);

	if (pLayer == nullptr)
		return nullptr;

	return pLayer->GetObjList();
}

HRESULT CGameObjectMgr::DeleteSceneObject(const _uint & SceneNum)
{
	for (auto& iter : m_pMapPrototype[SceneNum])
	{
		Safe_Release(iter.second);
	}

	m_pMapPrototype[SceneNum].clear();

	for (auto& iter : m_pMapObject[SceneNum])
	{
		Safe_Release(iter.second);
	}

	m_pMapObject[SceneNum].clear();


	return NOERROR;
}

_int CGameObjectMgr::Progress(const _float & fTimeDelta)
{

	if (nullptr == m_pMapObject)
		return -1;

	_int iResult = 0;

	for (size_t i = 0; i < iMaxSceneNum; ++i)
	{
		for (auto& iter : m_pMapObject[i])
		{
			iResult = iter.second->Progress(fTimeDelta);
			if (iResult & 0x80000000)
				return iResult;
		}
	}
	return iResult;
}

_int CGameObjectMgr::LateProgress(const _float & fTimeDelta)
{
	if (nullptr == m_pMapObject)
		return -1;

	_int iResult = 0;

	for (size_t i = 0; i < iMaxSceneNum; ++i)
	{
		for (auto& iter : m_pMapObject[i])
		{
			iResult = iter.second->LateProgress(fTimeDelta);
			if (iResult & 0x80000000)
				return iResult;
		}
	}
	return iResult;
}

HRESULT CGameObjectMgr::Render()
{
	if (nullptr == m_pMapObject)
		return -1;

	

	for (size_t i = 0; i < iMaxSceneNum; ++i)
	{
		for (auto& iter : m_pMapObject[i])
		{
			if (FAILED(iter.second->Render()))
				return E_FAIL;
		}
	}
	return NOERROR;
	
}


void CGameObjectMgr::Free()
{
	

	for (size_t i = 0; i < iMaxSceneNum; ++i)
	{
		for (auto& iter : m_pMapPrototype[i])
		{			
			Safe_Release(iter.second);
		}

		m_pMapPrototype[i].clear();
	}

	Safe_Delete_Arr(m_pMapPrototype);

	for (size_t i = 0; i < iMaxSceneNum; ++i)
	{
		for (auto& iter : m_pMapObject[i])
			Safe_Release(iter.second);

		m_pMapObject[i].clear();
	}

	Safe_Delete_Arr(m_pMapObject);

	
}
