#include "..\Header\Shader.h"




HRESULT CShader::Initialize(TCHAR* szFilePath)
{
	if (FAILED(D3DXCreateEffectFromFile(m_pGraphicDev, szFilePath, nullptr, nullptr, 0, nullptr, &m_pEffect, nullptr)))
		return E_FAIL;

	return NOERROR;
}

CShader::CShader(LPDIRECT3DDEVICE9 _m_pGraphicDevice)
	:CComponent(_m_pGraphicDevice)
{

}

CShader::CShader(const CShader & rhs)
	: CComponent(rhs),m_pEffect(rhs.m_pEffect)
{
	m_pEffect->AddRef();
}

HRESULT CShader::LoadShaderFile(TCHAR * szFileName)
{
	if (FAILED(D3DXCreateEffectFromFile(m_pGraphicDev, szFileName, nullptr, nullptr, 0, nullptr, &m_pEffect, nullptr)))
		return E_FAIL;


	return NOERROR;
}

CShader * CShader::Create(LPDIRECT3DDEVICE9 _m_pGraphicDevice, TCHAR* szFilePath)
{
	CShader* pInstance = new CShader(_m_pGraphicDevice);

	if (FAILED(pInstance->Initialize(szFilePath)))
	{
		_MSGBOX("CShader Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent * CShader::Clone()
{
	return new CShader(*this);
}

void CShader::Free()
{
	Safe_Release(m_pEffect);
	CComponent::Free();
}
