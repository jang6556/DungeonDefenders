#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CTresureChest :
	public CGameObject
{
private:	
	CTransform*				m_pTransform = nullptr;
	CShader*				m_pShader = nullptr;
	CRenderer*				m_pRenderer = nullptr;
	CMeshDynamic*			m_pMeshDynamic = nullptr;
	CCollider*				m_pCollider = nullptr;

	bool					m_IsOpen = false;
	float					m_fTimeDelta=0.f;	

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CTresureChest(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CTresureChest(const CTresureChest & rhs);
	virtual ~CTresureChest() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CTresureChest* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);

};
_END
