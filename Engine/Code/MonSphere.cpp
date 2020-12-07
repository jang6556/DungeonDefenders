#include "..\Header\MonSphere.h"
#include "Shader.h"



HRESULT CMonSphere::Initialize(D3DXVECTOR3 _vPosition)
{
	m_vPosition = _vPosition;
	m_pShader = CShader::Create(m_pGraphicDevice, L"ShaderFile/ShaderCollider.fx");

	if (FAILED(D3DXCreateSphere(m_pGraphicDevice, 0.1f, 20, 20, &m_pMesh, nullptr)))
		return E_FAIL;

	return NOERROR;
}

CMonSphere::CMonSphere(LPDIRECT3DDEVICE9 _m_pGraphicDevice)
	:m_pGraphicDevice(_m_pGraphicDevice)
{
	m_pGraphicDevice->AddRef();
}

HRESULT CMonSphere::Render()
{
	LPD3DXEFFECT pEffect = m_pShader->GetEffect();
	if (pEffect == nullptr)
		return E_FAIL;
	D3DXMATRIX matWorld, matView, matProj;
	D3DXMatrixIdentity(&matWorld);

	memcpy(&matWorld.m[3][0], &m_vPosition, sizeof(D3DXVECTOR3));

	m_pGraphicDevice->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDevice->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matWorld", &matWorld);
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);
	pEffect->SetBool("g_IsCollision", false);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(0);

	m_pMesh->DrawSubset(0);

	pEffect->EndPass();
	pEffect->End();

	return NOERROR;
}

void CMonSphere::Free()
{
	Safe_Release(m_pShader);
	Safe_Release(m_pMesh);
	Safe_Release(m_pGraphicDevice);
}

CMonSphere * CMonSphere::Create(LPDIRECT3DDEVICE9 _m_pGraphicDevice, D3DXVECTOR3 _vPosition)
{
	CMonSphere* pInstance = new CMonSphere(_m_pGraphicDevice);

	if (FAILED(pInstance->Initialize(_vPosition)))
	{
		_MSGBOX("CMonSphere Created Failed");
		Safe_Release(pInstance);
	}

	return pInstance;
}
