#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CDarkElfArrow :
	public CGameObject
{
private:
	D3DXVECTOR3		m_vDir;

	CTransform*		m_pTransform = nullptr;
	CShader*		m_pShader = nullptr;
	CRenderer*		m_pRenderer = nullptr;
	CMeshStatic*	m_pMeshStatic = nullptr;
	CCollider*		m_pCollider = nullptr;

	float			m_fTimeDelta = 0.f;

	HRESULT Initialize(void * pArg);
	
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	bool	CheckCollision();


	explicit CDarkElfArrow(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CDarkElfArrow(const CDarkElfArrow & rhs);
	virtual ~CDarkElfArrow() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CDarkElfArrow* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
