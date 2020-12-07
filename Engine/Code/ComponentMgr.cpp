#include "..\Header\ComponentMgr.h"


IMPLEMENT_SINGLETON(CComponentMgr)

CComponentMgr::CComponentMgr()
{

}

HRESULT CComponentMgr::AddPrototype(const TCHAR * szTag, CComponent * pComponent, _uint SceneNum)
{
	if (SceneNum >= iMaxSceneNum ||
		pComponent == nullptr)
		return E_FAIL;

	CComponent* pInstance = FindPrototype(szTag, SceneNum);
	if (pInstance != nullptr)
		return E_FAIL;

	m_pMapComponent[SceneNum].emplace(szTag, pComponent);

	return NOERROR;
}

CComponent * CComponentMgr::FindPrototype(const TCHAR * szTag, _uint SceneNum)
{
	if (SceneNum >= iMaxSceneNum)
		return nullptr;

	auto pInstance = find_if(m_pMapComponent[SceneNum].begin(), m_pMapComponent[SceneNum].end(), CFind_Tag(szTag));

	if (pInstance == m_pMapComponent[SceneNum].end())
		return nullptr;


	return pInstance->second;
}

HRESULT CComponentMgr::ReserveMapComponent(const _uint& SceneNum)
{
	if (m_pMapComponent != nullptr)
		return E_FAIL;

	m_pMapComponent = new MAPCOMPONENT[SceneNum];

	iMaxSceneNum = SceneNum;

	return NOERROR;
}

CComponent * CComponentMgr::AddComponent(const TCHAR * szTag, _uint SceneNum)
{
	CComponent* pInstance = FindPrototype(szTag, SceneNum);
	
	if (pInstance == nullptr)
		return nullptr;

	return pInstance->Clone();
}

HRESULT CComponentMgr::DeleteSceneComponent(const _uint & SceneNum)
{
	for (auto& iter : m_pMapComponent[SceneNum])
	{
		Safe_Release(iter.second);
	}

	m_pMapComponent[SceneNum].clear();

	return NOERROR;
}

void CComponentMgr::Free()
{
	for (int i = 0; i < iMaxSceneNum; ++i)
	{
		for (auto& iter : m_pMapComponent[i])
		{
			int a = Safe_Release(iter.second);
			int b = 10;
		}

		m_pMapComponent[i].clear();
	}

	Safe_Delete_Arr(m_pMapComponent);
}
