#include "stdafx.h"
#include "..\Header\Decal.h"


_USING(Client)
HRESULT CDecal::Initialize()
{
	return NOERROR;
}

HRESULT CDecal::Initialize(void * pArg)
{
	return NOERROR;
}

HRESULT CDecal::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CDecal::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	

	return NOERROR;
}

CDecal::CDecal(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CDecal::CDecal(const CDecal & rhs)
	: CGameObject(rhs)
{
}

_int CDecal::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CDecal::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CDecal::Render(LPD3DXEFFECT pEffect)
{
	return NOERROR;
}

HRESULT CDecal::SetRelease()
{
	if (m_bIsRelease == true)
		return E_FAIL;

	m_bIsRelease = true;

	return NOERROR;
}


void CDecal::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pBuffer);
	Safe_Release(m_pTexture);
	CGameObject::Free();
}
