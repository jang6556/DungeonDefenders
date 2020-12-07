#pragma once
#include "E:\Frame\Reference\Headers\GameObject.h"
class CCrystalRing :
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


	explicit CCrystalRing(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CCrystalRing(const CCrystalRing & rhs);
	virtual ~CCrystalRing() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;
	virtual HRESULT RenderShadow() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CCrystalRing* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};

