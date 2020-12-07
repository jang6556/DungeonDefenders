#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CVerticalBarMP :
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

	explicit CVerticalBarMP(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CVerticalBarMP(const CVerticalBarMP & rhs);
	virtual ~CVerticalBarMP() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CVerticalBarMP* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
