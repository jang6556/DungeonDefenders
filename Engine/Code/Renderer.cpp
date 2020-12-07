#include "..\Header\Renderer.h"
#include "../Header/RenderTargetMgr.h"
#include "../Header/Shader.h"
#include "../Header/LightMgr.h"
#include "../Header/ScreenTex_Buffer.h"
#include "../Header/ManageMent.h"

HRESULT CRenderer::SetBuffer(D3DVIEWPORT9	_ViewPort)
{
	m_pBuffer = CScreenTex_Buffer::Create(m_pGraphicDev, -0.5f, -0.5f, _ViewPort.Width, _ViewPort.Height);
	if (m_pBuffer == nullptr)
		return E_FAIL;

	m_pBlurBuffer = CScreenTex_Buffer::Create(m_pGraphicDev, -0.5f, -0.5f, _ViewPort.Width, _ViewPort.Height);
	if (m_pBuffer == nullptr)
		return E_FAIL;


	m_pBlurBuffer_X = CScreenTex_Buffer::Create(m_pGraphicDev, -0.5f, -0.5f, _ViewPort.Width, _ViewPort.Height);
	if (m_pBlurBuffer_X == nullptr)
		return E_FAIL;

	m_pBlendBuffer = CScreenTex_Buffer::Create(m_pGraphicDev, -0.5f, -0.5f, _ViewPort.Width, _ViewPort.Height);
	if (m_pBlendBuffer == nullptr)
		return E_FAIL;

	return NOERROR;
}

HRESULT CRenderer::RenderPriority()
{
	for (auto& iter : RedererList[PRIORITY])
	{
		if (iter != nullptr)
			iter->Render();
		Safe_Release(iter);
	}

	RedererList[PRIORITY].clear();

	return NOERROR;
}

HRESULT CRenderer::RenderShadow()
{
	if (m_pRenderTargetMgr == nullptr)
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->MultiTarget_Begin(L"MULTI_SHADOW")))
		return E_FAIL;	

	m_pGraphicDev->GetDepthStencilSurface(&m_pOldSurface);
	m_pGraphicDev->SetDepthStencilSurface(m_pShadowSurface);

	m_pGraphicDev->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 255, 255, 1), 1.f, 0);

	for (auto& iter : RedererList[DEPTH_SHADOW])
	{
		if (iter != nullptr)
			iter->RenderShadow();
		Safe_Release(iter);
	}

	RedererList[DEPTH_SHADOW].clear();

	m_pGraphicDev->SetDepthStencilSurface(m_pOldSurface);
	Safe_Release(m_pOldSurface);

	if (FAILED(m_pRenderTargetMgr->MultiTarget_End(L"MULTI_SHADOW")))
		return E_FAIL;	

	return NOERROR;
}

HRESULT CRenderer::RenderNoneAlpha()
{
	for (auto& iter : RedererList[NONALPHA])
	{
		if (iter != nullptr)
			iter->Render();
		Safe_Release(iter);
	}

	RedererList[NONALPHA].clear();

	return NOERROR;
}

bool AlphaSort(CGameObject* pSour, CGameObject* pDest)
{
	return pSour->GetZlength() > pDest->GetZlength();
}

HRESULT CRenderer::RenderAlpha()
{
	RedererList[ALPHA_OBJECT].sort(AlphaSort);

	for (auto& iter : RedererList[ALPHA_OBJECT])
	{
		if (iter != nullptr)
			iter->Render();
		Safe_Release(iter);
	}

	RedererList[ALPHA_OBJECT].clear();

	RedererList[ALPHA_EFFECT].sort(AlphaSort);

	for (auto& iter : RedererList[ALPHA_EFFECT])
	{
		if (iter != nullptr)
			iter->Render();
		Safe_Release(iter);
	}

	RedererList[ALPHA_EFFECT].clear();

	return NOERROR;
}

HRESULT CRenderer::RenderUI()
{
	for (auto& iter : RedererList[UI])
	{
		if (iter != nullptr)
			iter->Render();
		Safe_Release(iter);
	}

	RedererList[UI].clear();

	return NOERROR;
}

HRESULT CRenderer::RenderDecalObject()
{
	for (auto& iter : RedererList[DECAL_OBJECT])
	{
		if (iter != nullptr)
			iter->Render();
		Safe_Release(iter);
	}

	RedererList[DECAL_OBJECT].clear();

	return NOERROR;
}

HRESULT CRenderer::RenderOutline()
{
	if (m_pRenderTargetMgr == nullptr)
		return E_FAIL;	

	if (FAILED(m_pRenderTargetMgr->MultiTarget_Begin(L"MULTI_OUTLINE")))
		return E_FAIL;

	LPD3DXEFFECT pEffect = m_pShader_OutLine->GetEffect();
	if (pEffect == nullptr)
		return E_FAIL;

	pEffect->AddRef();

	if (FAILED(m_pRenderTargetMgr->SetTexture(pEffect, L"TARGET_DIFFUSE", "g_DiffuseTexture")))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->SetTexture(pEffect, L"TARGET_NORMAL", "g_NormalTexture")))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->SetTexture(pEffect, L"TARGET_DEPTH", "g_DepthTexture")))
		return E_FAIL;	

	D3DXMATRIX matView, matProj;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	D3DXVECTOR3 vCamPosition;	

	D3DXMatrixInverse(&matView, nullptr, &matView);
	D3DXMatrixInverse(&matProj, nullptr, &matProj);

	memcpy(&vCamPosition, &matView.m[3][0], sizeof(D3DXVECTOR3));

	pEffect->SetMatrix("g_matViewInv", &matView);
	pEffect->SetMatrix("g_matProjInv", &matProj);

	pEffect->SetVector("g_vCamPos", &D3DXVECTOR4(vCamPosition, 1));

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(0);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	Safe_Release(pEffect);

	if (FAILED(m_pRenderTargetMgr->MultiTarget_End(L"MULTI_OUTLINE")))
		return E_FAIL;

	return NOERROR;
}

HRESULT CRenderer::RenderBlur()
{
	if (m_pRenderTargetMgr == nullptr)
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->MultiTarget_Begin(L"MULTI_BLUR")))
		return E_FAIL;

	LPD3DXEFFECT pEffect = m_pShader_Blur->GetEffect();
	if (pEffect == nullptr)
		return E_FAIL;

	pEffect->AddRef();

	if (FAILED(m_pRenderTargetMgr->SetTexture(pEffect, L"TARGET_BLEND", "g_DiffuseTexture")))
		return E_FAIL;

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(0);

	m_pBlurBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	Safe_Release(pEffect);

	if (FAILED(m_pRenderTargetMgr->MultiTarget_End(L"MULTI_BLUR")))
		return E_FAIL;


	RenderBlur_X();

	return NOERROR;
}

HRESULT CRenderer::RenderBlur_X()
{
	if (m_pRenderTargetMgr == nullptr)
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->MultiTarget_Begin(L"MULTI_BLUR_X")))
		return E_FAIL;

	LPD3DXEFFECT pEffect = m_pShader_Blur->GetEffect();
	if (pEffect == nullptr)
		return E_FAIL;

	pEffect->AddRef();

	if (FAILED(m_pRenderTargetMgr->SetTexture(pEffect, L"TARGET_BLUR", "g_DiffuseTexture")))
		return E_FAIL;

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(1);

	m_pBlurBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	Safe_Release(pEffect);

	if (FAILED(m_pRenderTargetMgr->MultiTarget_End(L"MULTI_BLUR_X")))
		return E_FAIL;

	return NOERROR;
}

HRESULT CRenderer::RenderDecal(LPD3DXEFFECT pEffect)
{
	for (auto& iter : RedererList[DECAL])
	{
		if (iter != nullptr)
			iter->Render(pEffect);
		Safe_Release(iter);
	}

	RedererList[DECAL].clear();

	return NOERROR;
}

HRESULT CRenderer::RenderFinal()
{
	if (m_pRenderTargetMgr == nullptr ||
		m_pBuffer == nullptr ||
		m_pShader_Blend == nullptr)
		return E_FAIL;

	LPD3DXEFFECT pEffect = m_pShader_Render->GetEffect();
	if (pEffect == nullptr)
		return E_FAIL;

	pEffect->AddRef();	

	if (FAILED(m_pRenderTargetMgr->SetTexture(pEffect, L"TARGET_BLUR_X", "g_BlurTexture")))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->SetTexture(pEffect, L"TARGET_DEPTH", "g_DepthTexture")))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->SetTexture(pEffect, L"TARGET_BLEND", "g_DiffuseTexture")))
		return E_FAIL;

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(0);

	m_pBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	Safe_Release(pEffect);

	return NOERROR;
}

HRESULT CRenderer::RenderDeferred()
{
	if (m_pRenderTargetMgr == nullptr)
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->MultiTarget_Begin(L"MULTI_DEFERRED")))
		return E_FAIL;

	RenderNoneAlpha();

	if (FAILED(m_pRenderTargetMgr->MultiTarget_End(L"MULTI_DEFERRED")))
		return E_FAIL;

	return NOERROR;
}

HRESULT CRenderer::RenderDecalDeferred()
{
	if (m_pRenderTargetMgr == nullptr)
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->MultiTarget_Begin(L"MULTI_DECAL_DEFERRED")))
		return E_FAIL;

	RenderDecalObject();

	if (FAILED(m_pRenderTargetMgr->MultiTarget_End(L"MULTI_DECAL_DEFERRED")))
		return E_FAIL;
	return NOERROR;
}

HRESULT CRenderer::RenderLight()
{
	if (m_pRenderTargetMgr == nullptr || m_pLightMgr == nullptr)
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->MultiTarget_Begin(L"MULTI_LIGHT")))
		return E_FAIL;

	LPD3DXEFFECT pEffect = m_pShader_Light->GetEffect();
	if (pEffect == nullptr)
		return E_FAIL;

	pEffect->AddRef();

	if (FAILED(m_pRenderTargetMgr->SetTexture(pEffect, L"TARGET_NORMAL", "g_NormalTexture")))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->SetTexture(pEffect, L"TARGET_DEPTH", "g_DepthTexture")))
		return E_FAIL;

	pEffect->Begin(nullptr,0);

	m_pLightMgr->Render(pEffect);

	pEffect->End();

	Safe_Release(pEffect);


	if (FAILED(m_pRenderTargetMgr->MultiTarget_End(L"MULTI_LIGHT")))
		return E_FAIL;

	return NOERROR;
}

HRESULT CRenderer::RenderDecalShader()
{
	if (m_pRenderTargetMgr == nullptr || m_pShader_Decal == nullptr)
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->MultiTarget_Begin(L"MULTI_EFFECT")))
		return E_FAIL;

	LPD3DXEFFECT pEffect = m_pShader_Decal->GetEffect();
	if (pEffect == nullptr)
		return E_FAIL;

	pEffect->AddRef();	

	if (FAILED(m_pRenderTargetMgr->SetTexture(pEffect, L"TARGET_DECAL_DEPTH", "g_DepthTexture")))
		return E_FAIL;
	
	pEffect->Begin(nullptr, 0);

	RenderDecal(pEffect);

	pEffect->End();

	Safe_Release(pEffect);

	if (FAILED(m_pRenderTargetMgr->MultiTarget_End(L"MULTI_EFFECT")))
		return E_FAIL;

	return NOERROR;
}

HRESULT CRenderer::RenderBlend()
{
	if (m_pRenderTargetMgr == nullptr || 
		m_pBuffer == nullptr ||
		m_pShader_Blend == nullptr)
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->MultiTarget_Begin(L"MULTI_BLEND")))
		return E_FAIL;

	LPD3DXEFFECT pEffect = m_pShader_Blend->GetEffect();
	if (pEffect == nullptr)
		return E_FAIL;
	
	pEffect->AddRef();

	if (FAILED(m_pRenderTargetMgr->SetTexture(pEffect, L"TARGET_DIFFUSE", "g_DiffuseTexture")))
		return E_FAIL;
		
	if (FAILED(m_pRenderTargetMgr->SetTexture(pEffect, L"TARGET_SHADE", "g_ShadeTexture")))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->SetTexture(pEffect, L"TARGET_DECAL", "g_DecalTexture")))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->SetTexture(pEffect, L"TARGET_DEPTH", "g_DepthTexture")))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->SetTexture(pEffect, L"TARGET_SHADOW", "g_DepthShadowTexture")))
		return E_FAIL;

	D3DXMATRIX  matViewInv, matProjInv,matProj;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matViewInv);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProjInv);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matProj", &matProj);

	D3DXMatrixInverse(&matViewInv, nullptr, &matViewInv);
	D3DXMatrixInverse(&matProjInv, nullptr, &matProjInv);
	
	pEffect->SetMatrix("g_matViewInv", &matViewInv);
	pEffect->SetMatrix("g_matProjInv", &matProjInv);

	D3DXMATRIX  matLightView;

	D3DXVECTOR3 vLightPosition, vLightDirection, vLightUp;

	if (FAILED(CLightMgr::GetInstance()->GetDirectionalLight(CManageMent::GetInstance()->GetCurrSceneID(), &vLightPosition, &vLightDirection, &vLightUp)))
	{
		Safe_Release(pEffect);

		if (FAILED(m_pRenderTargetMgr->MultiTarget_End(L"MULTI_BLEND")))
			return E_FAIL;

		return NOERROR;
	}

	D3DXMatrixIdentity(&matLightView);

	D3DXMatrixLookAtLH(&matLightView, &vLightPosition, &vLightDirection, &vLightUp);

	pEffect->SetMatrix("g_matLightView", &matLightView);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(0);

	m_pBlendBuffer->Render();

	pEffect->EndPass();
	pEffect->End();

	Safe_Release(pEffect);

	RenderAlpha();

	if (FAILED(m_pRenderTargetMgr->MultiTarget_End(L"MULTI_BLEND")))
		return E_FAIL;

	return NOERROR;
}

CRenderer::CRenderer(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CComponent(_m_pGraphicDev),m_pRenderTargetMgr(CRenderTargetMgr::GetInstance()), m_pLightMgr(CLightMgr::GetInstance())
{
	m_pRenderTargetMgr->AddRef();
	m_pLightMgr->AddRef();
}

HRESULT CRenderer::Initialize()
{
	D3DVIEWPORT9	ViewPort;
	ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));

	m_pGraphicDev->GetViewport(&ViewPort);

	if (FAILED(m_pRenderTargetMgr->AddRenderTarget(m_pGraphicDev, L"TARGET_DIFFUSE", ViewPort.Width, ViewPort.Height, D3DFMT_A8R8G8B8, D3DXCOLOR(0, 0, 0, 0))))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->AddRenderTarget(m_pGraphicDev, L"TARGET_NORMAL", ViewPort.Width, ViewPort.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 1))))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->AddRenderTarget(m_pGraphicDev, L"TARGET_DEPTH", ViewPort.Width, ViewPort.Height, D3DFMT_A32B32G32R32F, D3DXCOLOR(1, 0, 0, 0))))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->AddRenderTarget(m_pGraphicDev, L"TARGET_SHADE", ViewPort.Width, ViewPort.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 1))))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->AddRenderTarget(m_pGraphicDev, L"TARGET_DECAL", ViewPort.Width, ViewPort.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 0))))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->AddRenderTarget(m_pGraphicDev, L"TARGET_DECAL_DIFFUSE", ViewPort.Width, ViewPort.Height, D3DFMT_A8R8G8B8, D3DXCOLOR(0, 0, 0, 0))))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->AddRenderTarget(m_pGraphicDev, L"TARGET_DECAL_NORMAL", ViewPort.Width, ViewPort.Height, D3DFMT_A16B16G16R16F, D3DXCOLOR(0, 0, 0, 1))))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->AddRenderTarget(m_pGraphicDev, L"TARGET_DECAL_DEPTH", ViewPort.Width, ViewPort.Height, D3DFMT_A32B32G32R32F, D3DXCOLOR(1, 0, 0, 0))))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->AddRenderTarget(m_pGraphicDev, L"TARGET_OUTLINE", ViewPort.Width, ViewPort.Height, D3DFMT_A32B32G32R32F, D3DXCOLOR(0, 0, 0, 1))))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->AddRenderTarget(m_pGraphicDev, L"TARGET_BLUR", ViewPort.Width, ViewPort.Height, D3DFMT_A32B32G32R32F, D3DXCOLOR(0, 0, 0, 1))))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->AddRenderTarget(m_pGraphicDev, L"TARGET_BLUR_X", ViewPort.Width, ViewPort.Height, D3DFMT_A32B32G32R32F, D3DXCOLOR(0, 0, 0, 1))))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->AddRenderTarget(m_pGraphicDev, L"TARGET_BLEND", ViewPort.Width, ViewPort.Height, D3DFMT_A32B32G32R32F, D3DXCOLOR(0, 0, 0, 1))))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->AddRenderTarget(m_pGraphicDev, L"TARGET_SHADOW", 8000, 6000, D3DFMT_A32B32G32R32F, D3DXCOLOR(1, 1, 1, 0))))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->AddMultiTarget(L"MULTI_DEFERRED", L"TARGET_DIFFUSE")))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->AddMultiTarget(L"MULTI_DEFERRED", L"TARGET_NORMAL")))
		return E_FAIL;
	
	if (FAILED(m_pRenderTargetMgr->AddMultiTarget(L"MULTI_DEFERRED", L"TARGET_DEPTH")))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->AddMultiTarget(L"MULTI_EFFECT", L"TARGET_DECAL")))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->AddMultiTarget(L"MULTI_LIGHT", L"TARGET_SHADE")))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->AddMultiTarget(L"MULTI_DECAL_DEFERRED", L"TARGET_DECAL_DIFFUSE")))
		return E_FAIL;
	if (FAILED(m_pRenderTargetMgr->AddMultiTarget(L"MULTI_DECAL_DEFERRED", L"TARGET_DECAL_NORMAL")))
		return E_FAIL;
	if (FAILED(m_pRenderTargetMgr->AddMultiTarget(L"MULTI_DECAL_DEFERRED", L"TARGET_DECAL_DEPTH")))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->AddMultiTarget(L"MULTI_OUTLINE", L"TARGET_OUTLINE")))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->AddMultiTarget(L"MULTI_BLUR", L"TARGET_BLUR")))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->AddMultiTarget(L"MULTI_BLUR_X", L"TARGET_BLUR_X")))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->AddMultiTarget(L"MULTI_BLEND", L"TARGET_BLEND")))
		return E_FAIL;

	if (FAILED(m_pRenderTargetMgr->AddMultiTarget(L"MULTI_SHADOW", L"TARGET_SHADOW")))
		return E_FAIL;



	m_pShader_Light = CShader::Create(m_pGraphicDev, L"ShaderFile/Shader_Light.fx");
	if (m_pShader_Light == nullptr)
		return E_FAIL;

	m_pShader_Blend = CShader::Create(m_pGraphicDev, L"ShaderFile/Shader_Blend.fx");
	if (m_pShader_Blend == nullptr)
		return E_FAIL;
	
	m_pShader_Decal = CShader::Create(m_pGraphicDev, L"ShaderFile/Shader_Decal.fx");
	if (m_pShader_Decal == nullptr)
		return E_FAIL;

	m_pShader_OutLine = CShader::Create(m_pGraphicDev, L"ShaderFile/Shader_OutLine.fx");
	if (m_pShader_OutLine == nullptr)
		return E_FAIL;

	m_pShader_Blur = CShader::Create(m_pGraphicDev, L"ShaderFile/Shader_Blur.fx");
	if (m_pShader_Blur == nullptr)
		return E_FAIL;

	m_pShader_Render= CShader::Create(m_pGraphicDev, L"ShaderFile/Shader_Render.fx");
	if (m_pShader_Render == nullptr)
		return E_FAIL;
	
	if (FAILED(SetBuffer(ViewPort)))
		return E_FAIL;


	m_pGraphicDev->CreateDepthStencilSurface(8000, 6000, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, TRUE, &m_pShadowSurface, NULL);
	if (m_pShadowSurface == nullptr)
		return E_FAIL;


#ifdef _DEBUG

	m_pRenderTargetMgr->Initialize_Buffer(L"TARGET_DIFFUSE", 0, 0, 200, 200);
	m_pRenderTargetMgr->Initialize_Buffer(L"TARGET_NORMAL", 0, 200, 200, 200);
	m_pRenderTargetMgr->Initialize_Buffer(L"TARGET_DEPTH", 0, 400, 200, 200);
	m_pRenderTargetMgr->Initialize_Buffer(L"TARGET_SHADE", 200, 0, 200, 200);
	m_pRenderTargetMgr->Initialize_Buffer(L"TARGET_DECAL", 200, 200, 200, 200);
	m_pRenderTargetMgr->Initialize_Buffer(L"TARGET_DECAL_DIFFUSE", 200, 400, 200, 200);
	m_pRenderTargetMgr->Initialize_Buffer(L"TARGET_OUTLINE", 400, 0, 200, 200);
	m_pRenderTargetMgr->Initialize_Buffer(L"TARGET_BLUR", 400, 0, 200, 200);
	m_pRenderTargetMgr->Initialize_Buffer(L"TARGET_BLEND", 400, 200, 200, 200);
	m_pRenderTargetMgr->Initialize_Buffer(L"TARGET_SHADOW", 400, 400, 200, 200);
#endif // _DEBUG


	return NOERROR;
}

_int CRenderer::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CRenderer::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CRenderer::Render()
{
	RenderPriority();	
	RenderShadow();
	RenderDeferred();
	RenderDecalDeferred();
	//RenderOutline();
	RenderDecalShader();
	RenderLight();
	RenderBlend();	
	RenderBlur();
	RenderFinal();
	RenderUI();

#ifdef _DEBUG
	if (GetAsyncKeyState('Z'))
	{
		if (FAILED(m_pRenderTargetMgr->Render_Buffer(L"MULTI_DEFERRED")))
			return E_FAIL;

		if (FAILED(m_pRenderTargetMgr->Render_Buffer(L"MULTI_LIGHT")))
			return E_FAIL;

		if (FAILED(m_pRenderTargetMgr->Render_Buffer(L"MULTI_EFFECT")))
			return E_FAIL;

		if (FAILED(m_pRenderTargetMgr->Render_Buffer(L"MULTI_DECAL_DEFERRED")))
			return E_FAIL;

		if (FAILED(m_pRenderTargetMgr->Render_Buffer(L"MULTI_BLUR")))
			return E_FAIL;

		if (FAILED(m_pRenderTargetMgr->Render_Buffer(L"MULTI_BLEND")))
			return E_FAIL;

		if (FAILED(m_pRenderTargetMgr->Render_Buffer(L"MULTI_SHADOW")))
			return E_FAIL;
	}
#endif // _DEBUG
	return NOERROR;
}

HRESULT CRenderer::AddRenderGroup(RENDERTYPE eType, CGameObject * pGameObject)
{
	if (eType >= RENDERTYPEEND ||
		pGameObject == nullptr)
		return E_FAIL;

	RedererList[eType].push_back(pGameObject);

	pGameObject->AddRef();
	return NOERROR;
}

CRenderer * CRenderer::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{	
	CRenderer*	pInstance = new CRenderer(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CRenderer Created Failed");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CRenderer::Clone()
{
	AddRef();

	return this;
}

void CRenderer::Free()
{
	for (int i = 0; i < RENDERTYPEEND; ++i)
	{
		for (auto& iter : RedererList[i])
		{
			if (iter != nullptr)
				Safe_Release(iter);

		}

		RedererList[i].clear();
	}

	Safe_Release(m_pRenderTargetMgr);
	Safe_Release(m_pLightMgr);
	Safe_Release(m_pShader_Light);
	Safe_Release(m_pShader_Blend);
	Safe_Release(m_pShader_Decal);
	Safe_Release(m_pBuffer);
	Safe_Release(m_pShader_OutLine);
	Safe_Release(m_pShader_Blur);
	Safe_Release(m_pBlurBuffer);
	Safe_Release(m_pBlurBuffer_X);
	Safe_Release(m_pShader_Render);
	Safe_Release(m_pBlendBuffer);
	Safe_Release(m_pShadowSurface);

	CComponent::Free();
}
