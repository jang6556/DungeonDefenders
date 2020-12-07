#include "..\Header\GameObject.h"
#include "ComponentMgr.h"


CGameObject::CGameObject(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:m_pGraphicDev(_m_pGraphicDev), m_IsClone(false)

{
	m_pGraphicDev->AddRef();
}

CGameObject::CGameObject(const CGameObject & rhs)
	:m_pGraphicDev(rhs.m_pGraphicDev),m_MapComponent(rhs.m_MapComponent), m_IsClone(true), m_ColliderData(rhs.m_ColliderData), m_fZlength(rhs.m_fZlength)
{
	m_pGraphicDev->AddRef();
}

HRESULT CGameObject::AddComponent(const _uint & iSceneId,const _tchar * szProtoTag, CComponent ** pComponentOut, const _tchar* szComponentTag)
{
	CComponent* pInstance= (CComponentMgr::GetInstance()->AddComponent(szProtoTag, iSceneId));
	if (pInstance == nullptr)
		return E_FAIL;

	list<CComponent*>*	pComponentList = FindComponentList(szProtoTag);

	if (pComponentList == nullptr)
	{
		list<CComponent*>	ComponentList;
		ComponentList.push_back(pInstance);

		m_MapComponent.emplace(szProtoTag, ComponentList);
	}
	else
		pComponentList->push_back(pInstance);	

	*pComponentOut = pInstance;
	
	pInstance->AddRef();

	return NOERROR;
}

HRESULT CGameObject::Initialize()
{
	return NOERROR;
}

HRESULT CGameObject::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CGameObject::LoadColliderData(TCHAR * szFilePath)
{
	HANDLE	hFile = CreateFile(szFilePath,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hFile == 0)
		return E_FAIL;

	DWORD		dwByte;

	int		iColliderNum=0;
	ReadFile(hFile, &iColliderNum, sizeof(int), &dwByte, NULL);

	
	
	for (int i = 0; i < iColliderNum; ++i)
	{
		OBJCOLLIDERDATA*	pInstance = new OBJCOLLIDERDATA;
		
		ReadFile(hFile, pInstance, sizeof(OBJCOLLIDERDATA), &dwByte, NULL);

		m_ColliderData.push_back(pInstance);
	}
		
	
	CloseHandle(hFile);

	return NOERROR;
}

HRESULT CGameObject::ComputeZ(D3DXVECTOR3 _vPosition)
{
	if (m_pGraphicDev == nullptr)
		return E_FAIL;

	D3DXMATRIX matView;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView,nullptr,&matView);

	D3DXVECTOR3 vCamPosition;

	memcpy(&vCamPosition, &matView.m[3][0], sizeof(D3DXVECTOR3));

	m_fZlength = D3DXVec3Length(&(_vPosition - vCamPosition));

	return NOERROR;
}

_int CGameObject::Progress(const _float& fTimeDelta)
{
	return _int();
}

_int CGameObject::LateProgress(const _float& fTimeDelta)
{
	return _int();
}

HRESULT CGameObject::Render()
{
	return NOERROR;
}

HRESULT CGameObject::Render(LPD3DXEFFECT pEffect)
{
	return NOERROR;
}

HRESULT CGameObject::RenderShadow()
{
	return NOERROR;
}

CComponent * CGameObject::GetComponent(const _tchar * szProtoTag)
{

	if ( m_MapComponent.size() == 0)
		return nullptr;

	auto iter = find_if(m_MapComponent.begin(),
		m_MapComponent.end(),
		CFind_Tag(szProtoTag));

	if (iter == m_MapComponent.end())
		return nullptr;

	return iter->second.back();
}

list<CComponent*>* CGameObject::FindComponentList(const _tchar * szProtoTag)
{
	auto iter = find_if(m_MapComponent.begin(),
		m_MapComponent.end(),
		CFind_Tag(szProtoTag));

	if (iter == m_MapComponent.end())
		return nullptr;

	return &iter->second;;
}



void CGameObject::Free()
{
	for (auto& iter : m_MapComponent)
	{
		for(auto& iter_vec: iter.second)
			Safe_Release(iter_vec);

		iter.second.clear();
	}

	m_MapComponent.clear();

	if (m_IsClone == false)
	{
		for (auto& iter : m_ColliderData)
			Safe_Delete(iter);
	}

	Safe_Release(m_pGraphicDev);
}


