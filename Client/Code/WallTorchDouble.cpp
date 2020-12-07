#include "stdafx.h"
#include "..\Header\WallTorchDouble.h"


_USING(Client)

HRESULT CWallTorchDouble::Initialize()
{
	return NOERROR;
}

HRESULT CWallTorchDouble::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXMATRIX matWorld = *(D3DXMATRIX*)pArg;

	m_pTransform->SetWorldMatrix(matWorld);

	if (FAILED(CLightObject::SetPointLight(SCENE_MAGNUS)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CWallTorchDouble::Initialize_Prototype()
{
	if (FAILED(CLightObject::LoadLightData(L"Data/WallTorch_Double_Light.dat")))
		return E_FAIL;

	return NOERROR;
}

HRESULT CWallTorchDouble::AddComponent()
{
	if (FAILED(CLightObject::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"WALLTORCH_DOUBLE", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	return NOERROR;
}

CWallTorchDouble::CWallTorchDouble(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CLightObject(_m_pGraphicDev)
{
}

CWallTorchDouble::CWallTorchDouble(const CWallTorchDouble & rhs)
	: CLightObject(rhs)
{
}

_int CWallTorchDouble::Progress(const _float & fTimeDelta)
{
	return CLightObject::Progress(fTimeDelta);
}

_int CWallTorchDouble::LateProgress(const _float & fTimeDelta)
{
	return CLightObject::LateProgress(fTimeDelta);
}

HRESULT CWallTorchDouble::Render()
{
	return CLightObject::Render();
}

CGameObject * CWallTorchDouble::Clone(void * pArg)
{
	CWallTorchDouble*	pInstance = new CWallTorchDouble(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CWallTorchDouble Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CWallTorchDouble::Free()
{
	CLightObject::Free();
}

CWallTorchDouble * CWallTorchDouble::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CWallTorchDouble*	pInstance = new CWallTorchDouble(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CWallTorchDouble Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
