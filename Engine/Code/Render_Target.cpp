#include "..\Header\Render_Target.h"
#include "../Header/ScreenTex_Buffer.h"

#ifdef _DEBUG

HRESULT CRender_Target::Initialize_Buffer(_float _fStartX, _float _fStartY, _float _fSizeX, _float _fSizeY)
{
	m_pBuffer = CScreenTex_Buffer::Create(m_pGraphicDev, _fStartX, _fStartY, _fSizeX, _fSizeY);
	if (m_pBuffer == nullptr)
		return E_FAIL;

	return NOERROR;
}

HRESULT CRender_Target::Render_Buffer()
{
	if (m_pBuffer == nullptr)
		return E_FAIL;

	m_pGraphicDev->SetTexture(0, m_pTexture);
	m_pBuffer->Render();
	return NOERROR;
}
#endif // _DEBUG

HRESULT CRender_Target::Initialize(_uint iWidth, _uint iHeight, D3DFORMAT eFormat, D3DXCOLOR Back_Color)
{
	if(FAILED(D3DXCreateTexture(m_pGraphicDev,iWidth,iHeight,1,D3DUSAGE_RENDERTARGET, eFormat,D3DPOOL_DEFAULT,&m_pTexture)))
		return E_FAIL;

	if (FAILED(m_pTexture->GetSurfaceLevel(0, &m_pCurrSurface)))
		return E_FAIL;

	m_BackColor = Back_Color;

	return NOERROR;
}

CRender_Target::CRender_Target(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:m_pGraphicDev(_m_pGraphicDev)
{
	m_pGraphicDev->AddRef();
}

HRESULT CRender_Target::SetTexture(LPD3DXEFFECT pEffect, const char * ShaderTexName)
{
	pEffect->SetTexture(ShaderTexName, m_pTexture);
	return NOERROR;
}

HRESULT CRender_Target::SetRenderTarget(const int & iIndex)
{
	if (m_pGraphicDev == nullptr ||
		m_pCurrSurface == nullptr)
		return E_FAIL;

	m_pGraphicDev->GetRenderTarget(iIndex, &m_pOldSurface);

	if (FAILED(m_pGraphicDev->SetRenderTarget(iIndex, m_pCurrSurface)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CRender_Target::ReleaseRenderTarget(const int & iIndex)
{
	if (m_pGraphicDev == nullptr)
		return E_FAIL;

	m_pGraphicDev->SetRenderTarget(iIndex, m_pOldSurface);

	Safe_Release(m_pOldSurface);

	return NOERROR;
}

HRESULT CRender_Target::ClearRenderTarget()
{
	if (m_pGraphicDev == nullptr ||
		m_pCurrSurface == nullptr)
		return E_FAIL;

	m_pGraphicDev->GetRenderTarget(0, &m_pOldSurface);

	m_pGraphicDev->SetRenderTarget(0, m_pCurrSurface);

	m_pGraphicDev->Clear(0, nullptr, D3DCLEAR_TARGET, m_BackColor, 1.f, 0);

	m_pGraphicDev->SetRenderTarget(0, m_pOldSurface);

	Safe_Release(m_pOldSurface);

	return NOERROR;
}

CRender_Target * CRender_Target::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev, _uint iWidth, _uint iHeight, D3DFORMAT eFormat, D3DXCOLOR Back_Color)
{
	CRender_Target* pInstance = new CRender_Target(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize(iWidth, iHeight, eFormat, Back_Color)))
	{
		_MSGBOX("CRender_Target Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CRender_Target::Free()
{
	Safe_Release(m_pBuffer);

	Safe_Release(m_pGraphicDev);
	Safe_Release(m_pTexture);
	Safe_Release(m_pCurrSurface);	
}
