#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CDecal :
	public CGameObject
{
protected:
	CTransform*			m_pTransform = nullptr;
	CRenderer*			m_pRenderer  = nullptr;
	CScreenTex_Buffer*	m_pBuffer	 = nullptr;
	CTexture*			m_pTexture   = nullptr;

	bool				m_bIsRelease = false;
	float				m_fScale = 0.f;

	float				m_fTimeDelta = 0.f;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();


	explicit CDecal(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CDecal(const CDecal & rhs);
	virtual ~CDecal() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render(LPD3DXEFFECT pEffect) override;

	HRESULT SetRelease();

	virtual void Free() override;
};
_END
