#include "..\Header\ManageMent.h"
#include "Scene.h"
#include "TimeMgr.h"
#include "GraphicDev.h"
#include "InputDev.h"
#include "RenderTargetMgr.h"
#include "LightMgr.h"


IMPLEMENT_SINGLETON(CManageMent)

CManageMent::CManageMent()
{
}

HRESULT CManageMent::Initialize(const _uint& _SceneID)
{
	if (FAILED(CGameObjectMgr::GetInstance()->ReserveMaxScene(_SceneID)))
		return E_FAIL;

	if (FAILED(CComponentMgr::GetInstance()->ReserveMapComponent(_SceneID)))
		return E_FAIL;

	if (FAILED(CLightMgr::GetInstance()->ReserveMaxScene(_SceneID)))
		return E_FAIL;

	return NOERROR;
}

_int CManageMent::Progress(const _float & fTimeDelta)
{
	if (m_pCurrScene == nullptr)
		return -1;

	_int Result = 0;

	Result = m_pCurrScene->Progress(fTimeDelta);
	if (Result & 0x80000000)
		return -1;

	Result = m_pCurrScene->LateProgress(fTimeDelta);
	if (Result & 0x80000000)
		return -1;


	return _int();
}

HRESULT CManageMent::Render()
{
	if (m_pCurrScene == nullptr)
		return E_FAIL;

	if(FAILED(m_pCurrScene->Render()))
		return E_FAIL;


	return NOERROR;
}

HRESULT CManageMent::SetCurrScene(CScene * _pScene, const _uint& _SceneID)
{
	if (_pScene == nullptr)
		return E_FAIL;

	if (m_pCurrScene != nullptr)
	{
		if (0 != Safe_Release(m_pCurrScene))
		{
			_MSGBOX("Fail Scene Release");
		}
	}

	m_pCurrScene = _pScene;

	m_SceneID = _SceneID;


	return NOERROR;
}
 
HRESULT CManageMent::Release_Engine()
{
	if(0 != CManageMent::GetInstance()->DestroyInstance())
		_MSGBOX("CManagement Release Failed");	

	if (0 != CGameObjectMgr::GetInstance()->DestroyInstance())
		_MSGBOX("CGameObjectMgr Release Failed");
	
	if (0 != CComponentMgr::GetInstance()->DestroyInstance())
		_MSGBOX("CComponentMgr Release Failed");

	if (0 != CTimeMgr::GetInstance()->DestroyInstance())
		_MSGBOX("CTimeMgr Release Failed");

	if (0 != CInputDev::GetInstance()->DestroyInstance())
		_MSGBOX("CInputDev Release Failed");

	if (0 != CRenderTargetMgr::GetInstance()->DestroyInstance())
		_MSGBOX("CRenderTargetMgr Release Failed");
	
	if (0 != CLightMgr::GetInstance()->DestroyInstance())
		_MSGBOX("CLightMgr Release Failed");

	if (0 != CGraphicDev::GetInstance()->DestroyInstance())
		_MSGBOX("CGraphicDev Release Failed");	

	return NOERROR;
}

void CManageMent::Free()
{
	Safe_Release(m_pCurrScene);
}
