#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CLoadingBarFrame :
	public CGameObject
{
private:
	CTransform*				m_pTransform = nullptr;
	CTexture*				m_Texture = nullptr;
	CShader*				m_pShader = nullptr;
	CRenderer*				m_pRenderer = nullptr;
	CRectUI*				m_pBuffer = nullptr;	

	float					m_fTimeDelta = 0.f;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	explicit CLoadingBarFrame(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CLoadingBarFrame(const CLoadingBarFrame & rhs);
	virtual ~CLoadingBarFrame() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CLoadingBarFrame* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
