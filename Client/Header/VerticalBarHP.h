#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CVerticalBarHP :
	public CGameObject
{
private:
	CTransform*				m_pTransform = nullptr;
	CTexture*				m_Texture = nullptr;
	CShader*				m_pShader = nullptr;
	
	CRectUI*				m_pBuffer = nullptr;

	float					m_fHP = 0.f;
	float					m_fTimeDelta = 1.f;


	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CVerticalBarHP(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CVerticalBarHP(const CVerticalBarHP & rhs);
	virtual ~CVerticalBarHP() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CVerticalBarHP* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
