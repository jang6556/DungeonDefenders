#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CLoadingBarContent :
	public CGameObject
{
private:
	CTransform*				m_pTransform = nullptr;
	CTexture*				m_Texture = nullptr;
	CShader*				m_pShader = nullptr;
	CRenderer*				m_pRenderer = nullptr;
	CRectUI*				m_pBuffer = nullptr;	

	float					m_fTimeDelta = 0.f;
	float					m_fComplete = 0.5f;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	explicit CLoadingBarContent(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CLoadingBarContent(const CLoadingBarContent & rhs);
	virtual ~CLoadingBarContent() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	void	SetComplete(int iComplete, const _float& fTimeDelta);

	virtual void Free() override;

	static CLoadingBarContent* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
