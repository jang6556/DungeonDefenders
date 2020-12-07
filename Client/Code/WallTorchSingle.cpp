#include "stdafx.h"
#include "..\Header\WallTorchSingle.h"


_USING(Client)
HRESULT CWallTorchSingle::Initialize()
{
	return NOERROR;
}

HRESULT CWallTorchSingle::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXMATRIX matWorld = *(D3DXMATRIX*)pArg;

	m_pTransform->SetWorldMatrix(matWorld);

	if (FAILED(CLightObject::SetPointLight(SCENE_MAGNUS)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CWallTorchSingle::Initialize_Prototype()
{
	if (FAILED(CLightObject::LoadLightData(L"Data/WallTorch_Single_Light.dat")))
		return E_FAIL;
	return NOERROR;
}

HRESULT CWallTorchSingle::AddComponent()
{
	if (FAILED(CLightObject::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"WALLTORCH_SINGLE", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	return NOERROR;
}

CWallTorchSingle::CWallTorchSingle(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CLightObject(_m_pGraphicDev)
{
}

CWallTorchSingle::CWallTorchSingle(const CWallTorchSingle & rhs)
	: CLightObject(rhs)
{
}

_int CWallTorchSingle::Progress(const _float & fTimeDelta)
{
	return CLightObject::Progress(fTimeDelta);
}

_int CWallTorchSingle::LateProgress(const _float & fTimeDelta)
{
	return CLightObject::LateProgress(fTimeDelta);
}

HRESULT CWallTorchSingle::Render()
{
	return CLightObject::Render();
}

CGameObject * CWallTorchSingle::Clone(void * pArg)
{
	CWallTorchSingle*	pInstance = new CWallTorchSingle(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CWallTorchSingle Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CWallTorchSingle::Free()
{
	CLightObject::Free();
}

CWallTorchSingle * CWallTorchSingle::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CWallTorchSingle*	pInstance = new CWallTorchSingle(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CWallTorchSingle Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
