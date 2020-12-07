#pragma once
#include "Component.h"
#include "GameObject.h"
_BEGIN(Engine)
class CRenderTargetMgr;
class CLightMgr;
class CShader;
class CScreenTex_Buffer;
class _DLLEXPORTS CRenderer :
	public CComponent
{
public:
	enum RENDERTYPE { PRIORITY,DEPTH_SHADOW, NONALPHA,DECAL_OBJECT, ALPHA_OBJECT,ALPHA_EFFECT,DECAL, UI, RENDERTYPEEND };
private:
	list<CGameObject*>		RedererList[RENDERTYPEEND];
	CRenderTargetMgr*		m_pRenderTargetMgr = nullptr;
	CLightMgr*				m_pLightMgr = nullptr;
	IDirect3DSurface9*		m_pOldSurface = nullptr;
	IDirect3DSurface9*		m_pShadowSurface = nullptr;

	CShader*				m_pShader_Light = nullptr;
	CShader*				m_pShader_Blend = nullptr;
	CShader*				m_pShader_Decal = nullptr;
	CShader*				m_pShader_OutLine = nullptr;
	CShader*				m_pShader_Blur = nullptr;
	CShader*				m_pShader_Render = nullptr;

	CScreenTex_Buffer*		m_pBuffer = nullptr;	
	CScreenTex_Buffer*		m_pBlurBuffer = nullptr;
	CScreenTex_Buffer*		m_pBlurBuffer_X = nullptr;
	CScreenTex_Buffer*		m_pBlendBuffer = nullptr;

	HRESULT SetBuffer(D3DVIEWPORT9	_ViewPort);
	
	HRESULT RenderPriority();
	HRESULT RenderShadow();
	HRESULT RenderNoneAlpha();
	HRESULT RenderAlpha();
	HRESULT RenderUI();
	HRESULT RenderDecalObject();
	HRESULT RenderOutline();
	HRESULT RenderBlur();
	HRESULT RenderBlur_X();
	HRESULT RenderDecal(LPD3DXEFFECT pEffect);
	HRESULT RenderFinal();

	HRESULT RenderDeferred();
	HRESULT RenderDecalDeferred();
	HRESULT RenderLight();
	HRESULT RenderDecalShader();
	HRESULT RenderBlend();


	explicit CRenderer(LPDIRECT3DDEVICE9	_m_pGraphicDev);
	virtual ~CRenderer() = default;
public:
	virtual HRESULT Initialize();
	virtual _int	Progress(const _float& fTimeDelta);
	virtual _int	LateProgress(const _float& fTimeDelta);
	virtual HRESULT Render();

	HRESULT AddRenderGroup(RENDERTYPE eType, CGameObject* pGameObject);

	static CRenderer* Create(LPDIRECT3DDEVICE9	_m_pGraphicDev);
	virtual CComponent* Clone();
	virtual void Free();
};
_END
