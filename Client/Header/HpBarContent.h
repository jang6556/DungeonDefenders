#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CHpBarContent :
	public CGameObject
{
private:
	CTransform*				m_pTransform = nullptr;
	CTexture*				m_pTexture = nullptr;
	CShader*				m_pShader = nullptr;
	CRectUI*				m_pBuffer = nullptr;

	float					m_fTimeDelta = 0.f;

	float					m_fScale = 0.f;

	int						m_iflag = 1;
	float					m_fCurrUV = 0.f;

	float					m_fRatio = 1.f;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();

	explicit CHpBarContent(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CHpBarContent(const CHpBarContent & rhs);
	virtual ~CHpBarContent() = default;

public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	void SetHpRatio(float _fRatio) { m_fRatio = _fRatio; }

	virtual void Free() override;

	static CHpBarContent* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
