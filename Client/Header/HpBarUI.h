#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CHpBarUI :
	public CGameObject
{
protected:
	CTransform*				m_pTransform = nullptr;
	CTexture*				m_pTexture = nullptr;
	CShader*				m_pShader = nullptr;
	CRectUI*				m_pBuffer = nullptr;

	float					m_fTimeDelta = 0.f;

	float					m_fScale = 0.f;	

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();	

	explicit CHpBarUI(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CHpBarUI(const CHpBarUI & rhs);
	virtual ~CHpBarUI() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;
	static CHpBarUI* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END

