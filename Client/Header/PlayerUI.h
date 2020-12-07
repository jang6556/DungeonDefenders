#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CPlayerUI :
	public CGameObject
{
protected:
	CTransform*				m_pTransform = nullptr;
	CTexture*				m_Texture = nullptr;
	CShader*				m_pShader = nullptr;
	CRectUI*				m_pBuffer = nullptr;

	_uint					m_iTexNum = 0;
	_uint					m_iPassNum = 0;


	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CPlayerUI(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CPlayerUI(const CPlayerUI & rhs);
	virtual ~CPlayerUI() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;	
};
_END

