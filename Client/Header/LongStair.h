#pragma once
#include "GameObject.h"
_BEGIN(Client)
class CLongStair :
	public CGameObject
{
private:
	CTransform*		m_pTransform = nullptr;
	CShader*		m_pShader = nullptr;
	CRenderer*		m_pRenderer = nullptr;
	CMeshStatic*	m_pMeshStatic = nullptr;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CLongStair(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CLongStair(const CLongStair & rhs);
	virtual ~CLongStair() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CLongStair* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
