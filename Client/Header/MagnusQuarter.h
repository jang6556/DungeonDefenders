#pragma once
#include "GameObject.h"
_BEGIN(Client)
class CMagnusQuarter :
	public CGameObject
{
private:
	CTransform*		m_pTransform = nullptr;
	CShader*		m_pShader = nullptr;
	CRenderer*		m_pRenderer = nullptr;
	CMeshStatic*	m_pMeshStatic = nullptr;
	

	float			m_fTimeDelta = 0.f;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CMagnusQuarter(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CMagnusQuarter(const CMagnusQuarter & rhs);
	virtual ~CMagnusQuarter() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CMagnusQuarter* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
