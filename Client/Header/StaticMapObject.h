#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CStaticMapObject :
	public CGameObject
{
protected:
	CTransform*		m_pTransform = nullptr;
	CShader*		m_pShader = nullptr;
	CRenderer*		m_pRenderer = nullptr;
	CMeshStatic*	m_pMeshStatic = nullptr;
	CFrustum*		m_pFrustum = nullptr;

	float			m_fTimeDelta = 0.f;
	float			m_fRadius = 5.f;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();


	explicit CStaticMapObject(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CStaticMapObject(const CStaticMapObject & rhs);
	virtual ~CStaticMapObject() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;
	virtual HRESULT RenderShadow() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;
};
_END
