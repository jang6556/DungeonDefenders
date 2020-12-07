#include "stdafx.h"
#include "..\Header\WallTorchAngle.h"


_USING(Client)
HRESULT CWallTorchAngle::Initialize()
{
	return NOERROR;
}

HRESULT CWallTorchAngle::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXMATRIX matWorld = *(D3DXMATRIX*)pArg;

	m_pTransform->SetWorldMatrix(matWorld);

	if (FAILED(CLightObject::SetPointLight(SCENE_MAGNUS)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CWallTorchAngle::Initialize_Prototype()
{
	if (FAILED(CLightObject::LoadLightData(L"Data/WallTorch_Angle_Light.dat")))
		return E_FAIL;
	return NOERROR;
}

HRESULT CWallTorchAngle::AddComponent()
{
	if (FAILED(CLightObject::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"WALLTORCH_ANGLE", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	return NOERROR;
}

CWallTorchAngle::CWallTorchAngle(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CLightObject(_m_pGraphicDev)
{
}

CWallTorchAngle::CWallTorchAngle(const CWallTorchAngle & rhs)
	: CLightObject(rhs)
{
}

_int CWallTorchAngle::Progress(const _float & fTimeDelta)
{
	return CLightObject::Progress(fTimeDelta);
}

_int CWallTorchAngle::LateProgress(const _float & fTimeDelta)
{
	return CLightObject::LateProgress(fTimeDelta);
}

HRESULT CWallTorchAngle::Render()
{
	return CLightObject::Render();
}

CGameObject * CWallTorchAngle::Clone(void * pArg)
{
	CWallTorchAngle*	pInstance = new CWallTorchAngle(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CWallTorchAngle Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CWallTorchAngle::Free()
{
	CLightObject::Free();
}

CWallTorchAngle * CWallTorchAngle::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CWallTorchAngle*	pInstance = new CWallTorchAngle(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CWallTorchAngle Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
