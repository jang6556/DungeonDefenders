#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CEffect :
	public CGameObject
{
protected:
	CTransform*				m_pTransform	= nullptr;
	CRectUI*				m_pBuffer   = nullptr;
	CShader*				m_pShader		= nullptr;
	CRenderer*				m_pRenderer		= nullptr;
	CTexture*				m_pTexture		= nullptr;	

	float					m_fTimeDelta	= 0.f;

	float					m_iTexNum		= 0;
	int						m_iShaderPass   = 0;
	D3DXVECTOR3				m_vScale;
	D3DXVECTOR3				m_vColor;


	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();


	explicit CEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CEffect(const CEffect & rhs);
	virtual ~CEffect() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;	

	virtual void Free() override;	
};
_END
