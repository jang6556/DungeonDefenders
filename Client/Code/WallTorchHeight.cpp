#include "stdafx.h"
#include "..\Header\WallTorchHeight.h"


_USING(Client)

HRESULT CWallTorchHeight::Initialize()
{
	return NOERROR;
}

HRESULT CWallTorchHeight::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXMATRIX matWorld = *(D3DXMATRIX*)pArg;

	m_pTransform->SetWorldMatrix(matWorld);

	if (FAILED(CLightObject::SetPointLight(SCENE_MAGNUS)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CWallTorchHeight::Initialize_Prototype()
{
	if (FAILED(CLightObject::LoadLightData(L"Data/WallTorch_Height_Light.dat")))
		return E_FAIL;
	return NOERROR;
}

HRESULT CWallTorchHeight::AddComponent()
{
	if (FAILED(CLightObject::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"WALLTORCH_HEIGHT", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	return NOERROR;
}

CWallTorchHeight::CWallTorchHeight(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CLightObject(_m_pGraphicDev)
{
}

CWallTorchHeight::CWallTorchHeight(const CWallTorchHeight & rhs)
	: CLightObject(rhs)
{
}

_int CWallTorchHeight::Progress(const _float & fTimeDelta)
{
	return CLightObject::Progress(fTimeDelta);
}

_int CWallTorchHeight::LateProgress(const _float & fTimeDelta)
{
	return CLightObject::LateProgress(fTimeDelta);
}

HRESULT CWallTorchHeight::Render()
{
	return CLightObject::Render();
}

CGameObject * CWallTorchHeight::Clone(void * pArg)
{
	CWallTorchHeight*	pInstance = new CWallTorchHeight(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CWallTorchHeight Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CWallTorchHeight::Free()
{
	CLightObject::Free();
}

CWallTorchHeight * CWallTorchHeight::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CWallTorchHeight*	pInstance = new CWallTorchHeight(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CWallTorchHeight Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
