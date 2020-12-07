#include "..\Header\LightMgr.h"
#include "../Header/Light.h"

IMPLEMENT_SINGLETON(CLightMgr)
CLightMgr::CLightMgr()
{
}

HRESULT CLightMgr::ReserveMaxScene(const _uint & SceneNum)
{
	if (m_pLight_List != nullptr)
		return E_FAIL;

	m_pLight_List = new LIGHTLIST[SceneNum];

	m_iMaxScene = SceneNum;

	return NOERROR;
}

HRESULT CLightMgr::AddLight(const _uint & SceneID, LPDIRECT3DDEVICE9 _m_pGraphicDev, const D3DLIGHT9 * LightInfo)
{
	CLight* pInstance = CLight::Create(_m_pGraphicDev, LightInfo);
	if (pInstance == nullptr)
		return E_FAIL;

	m_pLight_List[SceneID].push_back(pInstance);

	return NOERROR;
}

HRESULT CLightMgr::Render(LPD3DXEFFECT pEffect)
{
	for (size_t i = 0; i < m_iMaxScene; ++i)
	{
		for (auto& iter : m_pLight_List[i])
		{
			if (iter != nullptr)
				iter->Render(pEffect);
		}
	}

	return NOERROR;
}

HRESULT CLightMgr::DeleteSceneLight(const _uint & SceneID)
{
	for (auto& iter : m_pLight_List[SceneID])
	{
		Safe_Release(iter);
	}

	m_pLight_List[SceneID].clear();

	return NOERROR;
}

HRESULT CLightMgr::GetDirectionalLight(const _uint& SceneID,D3DXVECTOR3 * _vPosition, D3DXVECTOR3 * _vDirection, D3DXVECTOR3* _vUp, const int& _iNum)
{
	if (SceneID >= m_iMaxScene ||_iNum >= m_pLight_List[SceneID].size())
		return E_FAIL;

	CLight* pLight = nullptr;
	int iNum = 0;
	for (auto& iter : m_pLight_List[SceneID])
	{
		if (iter->GetLightInfo().Type == D3DLIGHT_DIRECTIONAL)
		{
			if (iNum == _iNum)
			{
				pLight = iter;
				break;
			}
			else
				++iNum;
		}
	}

	if (pLight == nullptr)
		return E_FAIL;

	*_vPosition = D3DXVECTOR3(0,50,0);

	*_vDirection = pLight->GetLightInfo().Direction;

	D3DXVECTOR3 vLook= pLight->GetLightInfo().Direction;
	D3DXVECTOR3 vRight, vUp;
	D3DXVec3Cross(&vRight, &D3DXVECTOR3(0, 1, 0), &vLook);
	D3DXVec3Cross(&vUp, &vLook, &vRight);

	*_vUp = vUp;


	return NOERROR;
}

void CLightMgr::Free()
{
	for (size_t i = 0; i < m_iMaxScene; ++i)
	{
		for (auto& iter : m_pLight_List[i])
		{
			Safe_Release(iter);
		}

		m_pLight_List[i].clear();
	}

	Safe_Delete_Arr(m_pLight_List);
}
