#pragma once
#include "GameObject.h"
#include "DamageBuffer.h"

_BEGIN(Client)
class CDamageFont :
	public CGameObject
{
private:
	list<CGameObject*>		m_FontList;
	CRenderer*				m_pRenderer = nullptr;
	CFrustum*				m_pFrustum = nullptr;

	D3DXVECTOR3				m_vPosition;


	float					m_fTimeDelta = 0.f;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();


	HRESULT CreateDamageBuffer(D3DXVECTOR4 _iDamage);
	int	GetNum(float fNum, int iSize,int iPos);


	explicit CDamageFont(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CDamageFont(const CDamageFont & rhs);
	virtual ~CDamageFont() = default;

public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CDamageFont* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
