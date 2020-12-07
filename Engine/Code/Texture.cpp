#include "..\Header\Texture.h"



CTexture::CTexture(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CComponent(_m_pGraphicDev)
{
}

CTexture::CTexture(const CTexture & rhs)
	:CComponent(rhs),m_vecTexture(rhs.m_vecTexture)
{
	for (auto& pTexture : m_vecTexture)
		pTexture->AddRef();
}

HRESULT CTexture::Initialize(const _tchar * szFileName, const _uint & iFileNum, TEXTYPE eType)
{
	m_vecTexture.reserve(iFileNum);

	for (size_t i = 0; i < iFileNum; ++i)
	{
		_tchar	Filename[MAX_PATH] = L"";

		IDirect3DBaseTexture9* pTexture = nullptr;

		wsprintf(Filename, szFileName, i);
		if (eType == GENERIC)
		{
			if (FAILED(D3DXCreateTextureFromFile(m_pGraphicDev, Filename,(LPDIRECT3DTEXTURE9*)&pTexture)))
				return E_FAIL;
		}
		else if (eType == CUBE)
		{
			if (FAILED(D3DXCreateCubeTextureFromFile(m_pGraphicDev, Filename, (LPDIRECT3DCUBETEXTURE9*)&pTexture)))
				return E_FAIL;
		}
		m_vecTexture.push_back(pTexture);


	}



	return NOERROR;
}

HRESULT CTexture::SetTexture(const _uint & iIndex)
{
	if (m_vecTexture.size() < iIndex ||
		m_vecTexture[iIndex] == nullptr ||
		m_pGraphicDev == nullptr)
		return E_FAIL;

	if (FAILED(m_pGraphicDev->SetTexture(0, m_vecTexture[iIndex])))
		return E_FAIL;


	return NOERROR;
}

HRESULT CTexture::SetTexture(LPD3DXEFFECT pEffect, const char * ShaderTexName, const int & iIndex)
{
	if (m_pGraphicDev == nullptr ||
		pEffect == nullptr ||
		m_vecTexture.size() <= iIndex)
		return E_FAIL;

	pEffect->SetTexture(ShaderTexName, m_vecTexture[iIndex]);

	return NOERROR;
	
}

CTexture * CTexture::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev, const _tchar * szFileName, const _uint& iFileNum, TEXTYPE eType)
{
	CTexture*	pInstance = new CTexture(_m_pGraphicDev);
	if (FAILED(pInstance->Initialize(szFileName, iFileNum, eType)))
	{
		_MSGBOX("CTexture Created Failed");
		Safe_Release(pInstance);
	}

	return pInstance;
}



CComponent * CTexture::Clone()
{
	return new CTexture(*this);
}

void CTexture::Free()
{
	for (auto& iter : m_vecTexture)
	{
		Safe_Release(iter);
	}

	m_vecTexture.clear();

	CComponent::Free();
}
