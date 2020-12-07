#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CMonster;
class CGlowBall :
	public CGameObject
{
private:
	CTransform*				m_pParentTransform = nullptr;
	D3DXMATRIX				m_pParentBoneMatirx;

	CTransform*				m_pTransform  = nullptr;
	CShader*				m_pShader     = nullptr;	
	CMeshStatic*			m_pMeshStatic = nullptr;
	CRenderer*				m_pRenderer   = nullptr;	

	float					m_fScale = 0.f;
	
	virtual HRESULT Initialize() override;
	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	HRESULT ComputeMatrix(D3DXMATRIX* pOut);

	explicit CGlowBall(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CGlowBall(const CGlowBall & rhs);
	virtual ~CGlowBall() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	HRESULT SetMatrix(CTransform* pParentTransform, D3DXMATRIX pParentBoneMatirx);
	


	virtual void Free() override;

	static CGlowBall* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END

