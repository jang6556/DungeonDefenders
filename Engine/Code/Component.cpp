#include "..\Header\Component.h"



CComponent::CComponent(LPDIRECT3DDEVICE9	_m_pGraphicDev)
	:m_pGraphicDev(_m_pGraphicDev), m_IsClone(false)
{
	m_pGraphicDev->AddRef();
}

CComponent::CComponent(const CComponent & rhs)
	: m_pGraphicDev(rhs.m_pGraphicDev), m_IsClone(true)
{
	m_pGraphicDev->AddRef();
}



HRESULT CComponent::Initialize()
{
	return NOERROR;
}

void CComponent::Free()
{
	Safe_Release(m_pGraphicDev);
}
