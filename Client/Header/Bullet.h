#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CBullet :
	public CGameObject
{
protected:
	D3DXVECTOR3		m_vRight;
	D3DXMATRIX		matWorld;
	CMeshDynamic*	m_pPlayerBone = nullptr;
	CTransform*		m_pPlayerWorld = nullptr;
	CTransform*		m_pBowTransform = nullptr;
	CTransform*		m_pTransform = nullptr;
	CShader*		m_pShader = nullptr;
	CRenderer*		m_pRenderer = nullptr;
	CMeshStatic*	m_pMeshStatic = nullptr;
	CCollider*		m_pCollider = nullptr;

	float			m_fTimeDelta = 0.f;
	float			m_fDamage = 1.f;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	_int			CheckCollision(const _tchar* szEffectTag);

	explicit CBullet(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CBullet(const CBullet & rhs);
	virtual ~CBullet() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual void Free() override;

	
};
_END
