#include "..\Header\Layer.h"
#include "GameObject.h"


CLayer::CLayer()
{
}

HRESULT CLayer::Initialize()
{
	return NOERROR;
}

_int CLayer::Progress(const _float & fTimeDelta)
{
	for (auto& iter = m_ObjList.begin(); iter != m_ObjList.end();)
	{
		if ((*iter)->Progress(fTimeDelta) == -1)
		{
			Safe_Release((*iter));
			iter = m_ObjList.erase(iter);
		}
		else
			++iter;
	}
	return _int();
}

_int CLayer::LateProgress(const _float & fTimeDelta)
{
	for (auto& iter = m_ObjList.begin(); iter != m_ObjList.end();)
	{
		if ((*iter)->LateProgress(fTimeDelta) == -1)
		{
			Safe_Release((*iter));
			iter = m_ObjList.erase(iter);
		}
		else
			++iter;
	}
	return _int();
}

HRESULT CLayer::Render()
{
	
	for (auto& iter : m_ObjList)
	{
		if (FAILED(iter->Render()))
		{
			return E_FAIL;
		}
		
	}
	return NOERROR;
}

HRESULT CLayer::AddObject(CGameObject * _pGameObject)
{
	if (_pGameObject == nullptr)
		return E_FAIL;

	m_ObjList.push_back(_pGameObject);

	return NOERROR;
}

CLayer * CLayer::Create()
{
	CLayer* pInstance = new CLayer();
	
	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CLayer Created Failed");
		Safe_Release(pInstance);		
	}
	return pInstance;
}

void CLayer::Free()
{
	for (auto& iter : m_ObjList)
		Safe_Release(iter);

	m_ObjList.clear();
}


