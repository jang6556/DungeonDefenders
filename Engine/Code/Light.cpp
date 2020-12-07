#include "..\Header\Light.h"
#include "../Header/ScreenTex_Buffer.h"
#include "../Header/Frustum.h"


HRESULT CLight::Initialize(const D3DLIGHT9* LightInfo)
{
	m_LightInfo = *LightInfo;

	D3DVIEWPORT9 ViewPort;
	ZeroMemory(&ViewPort, sizeof(ViewPort));

	m_pGraphicDev->GetViewport(&ViewPort);

	m_pBuffer = CScreenTex_Buffer::Create(m_pGraphicDev,-0.5f,-0.5f, ViewPort.Width, ViewPort.Height);
	if (m_pBuffer == nullptr)
		return E_FAIL;

	m_pFrustum = CFrustum::Create(m_pGraphicDev);
	if (m_pFrustum == nullptr)
		return E_FAIL;

	return NOERROR;
}

CLight::CLight(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:m_pGraphicDev(_m_pGraphicDev)
{
	m_pGraphicDev->AddRef();
}

HRESULT CLight::Render(LPD3DXEFFECT pEffect)
{
	_uint iPass = 0;

	if (m_LightInfo.Type == D3DLIGHT_DIRECTIONAL)
	{
		pEffect->SetVector("g_vLightDir", &D3DXVECTOR4(m_LightInfo.Direction, 0));
	}
	else if(m_LightInfo.Type == D3DLIGHT_POINT)
	{
		if (m_pFrustum->IsInFrustumLight(m_LightInfo.Position, m_LightInfo.Range) == false)
			return NOERROR;

		iPass = 1;
		pEffect->SetVector("g_vLightPos", &D3DXVECTOR4(m_LightInfo.Position, 1));
		pEffect->SetFloat("g_fRange", m_LightInfo.Range);
	}
	pEffect->SetVector("g_vLightDiffuse", (D3DXVECTOR4*)&m_LightInfo.Diffuse);
	pEffect->SetVector("g_vLightSpecular", (D3DXVECTOR4*)&m_LightInfo.Specular);
	pEffect->SetVector("g_vLightAmbient", (D3DXVECTOR4*)&m_LightInfo.Ambient);


	D3DXMATRIX matView, matProj;	

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	D3DXMatrixInverse(&matView, nullptr, &matView);
	D3DXMatrixInverse(&matProj, nullptr, &matProj);

	pEffect->SetMatrix("g_matViewInv", &matView);
	pEffect->SetMatrix("g_matProjInv", &matProj);
	
	pEffect->CommitChanges();

	pEffect->BeginPass(iPass);

	m_pBuffer->Render();

	pEffect->EndPass();

	return NOERROR;
}

CLight * CLight::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev, const D3DLIGHT9* LightInfo)
{
	CLight* pInstance = new CLight(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize(LightInfo)))
	{
		_MSGBOX("CLight Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLight::Free()
{
	Safe_Release(m_pGraphicDev);
	Safe_Release(m_pBuffer);
	Safe_Release(m_pFrustum);
}
