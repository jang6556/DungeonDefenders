#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CMonster;
class CMonsterUI :
	public CGameObject
{
protected:
	CTransform*				m_pTransform	= nullptr;
	CTexture*				m_pTexture		= nullptr;
	CShader*				m_pShader		= nullptr;	
	CRectUI*				m_pBuffer		= nullptr;
	
	float					m_fTimeDelta	= 0.f;
	CMonster*				m_pMonster		= nullptr;

	float					m_fScale		= 0.f;
	D3DXVECTOR3				m_vOffSet		= { 0,0,0 };

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();

	HRESULT ComputeViewPos();

	explicit CMonsterUI(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CMonsterUI(const CMonsterUI & rhs);
	virtual ~CMonsterUI() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;	
};
_END
