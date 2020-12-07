#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CStatUI :
	public CGameObject
{
protected:
	CTransform*				m_pTransform = nullptr;
	CTexture*				m_Texture = nullptr;
	CShader*				m_pShader = nullptr;
	CRectUI*				m_pBuffer = nullptr;

	_uint					m_iTexNum = 0;
	_uint					m_iPassNum = 0;

	float					m_fAlpha = 0.f;
	int						m_iAlphaFlag = -1.f;
	D3DXVECTOR3				m_vColor;

	D3DXVECTOR2				m_vPosition;
	D3DXVECTOR2				m_vScale;
	bool					m_bOnIcon = false;
	bool					m_bClickIcon = false;

	D3DXVECTOR2*			m_vMovePanel;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	bool	CheckOnIcon(D3DXVECTOR2	_vPosition, D3DXVECTOR2 _vScale);


	explicit CStatUI(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CStatUI(const CStatUI & rhs);
	virtual ~CStatUI() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	HRESULT	RenderSwitch();

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;
};
_END
