#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CBuildObject :
	public CGameObject
{
protected:	
	CTransform*		m_pTransform = nullptr;
	CShader*		m_pShader = nullptr;
	CRenderer*		m_pRenderer = nullptr;
	CMeshStatic*	m_pMeshStatic = nullptr;
	CMeshDynamic*	m_pMeshDynamic = nullptr;
	CTexture*		m_pTexture = nullptr;
	CCollider*		m_pCollider = nullptr;

	float			m_fTimeDelta = 0.f;
	float			m_fDamage = 1.f;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	HRESULT Render_Static();
	HRESULT Render_Dynamic();


	explicit CBuildObject(LPDIRECT3DDEVICE9 _m_pGraphicDev);	
	explicit CBuildObject(const CBuildObject & rhs);
	virtual ~CBuildObject() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual void Free() override;
};
_END
