#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CTextUI :
	public CGameObject
{
private:
	CTransform*				m_pTransform = nullptr;
	CTexture*				m_Texture = nullptr;
	CShader*				m_pShader = nullptr;
	CRectUI*				m_pBuffer = nullptr;

	_uint					m_iTexNum = 0;
	_uint					m_iShaderNum = 7;

	D3DXVECTOR3				m_vColor;

	D3DXVECTOR2				m_vPosition;
	D3DXVECTOR2				m_vScale;

	virtual HRESULT Initialize() override;
	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	explicit CTextUI(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CTextUI(const CTextUI & rhs);
	virtual ~CTextUI() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	HRESULT SetTextureNum(int iNum);
	HRESULT SetScale(float fScaleX, float fScaleY);
	HRESULT SetPosition(D3DXVECTOR2 vPosition);
	HRESULT SetShaderNum(_uint iShaderNum) { m_iShaderNum = iShaderNum; return NOERROR; }

	virtual void Free() override;

	static CTextUI* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
