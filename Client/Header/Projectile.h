#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CProjectile :
	public CGameObject
{
private:
	CTransform*		m_pParentsTransform = nullptr;
	CTransform*		m_pTransform = nullptr;
	CShader*		m_pShader = nullptr;
	CMeshStatic*	m_pMeshStatic = nullptr;
	

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	explicit CProjectile(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CProjectile(const CProjectile & rhs);
	virtual ~CProjectile() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CProjectile* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
