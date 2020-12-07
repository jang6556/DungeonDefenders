#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CCrystalHead :
	public CGameObject
{
private:
	CTransform*				m_pTransform = nullptr;
	CShader*				m_pShader = nullptr;	
	CMeshStatic*			m_pMeshStatic = nullptr;
	CCollider*				m_pCollider = nullptr;

	virtual HRESULT Initialize() override;
	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CCrystalHead(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CCrystalHead(const CCrystalHead & rhs);
	virtual ~CCrystalHead() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;
	virtual HRESULT RenderShadow() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CCrystalHead* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
