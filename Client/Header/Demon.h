#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CDemon :
	public CGameObject
{
public:
	enum STATE { STATE_IDLE, STATE_HIT, STATE_ATTACK,END};
private:
	STATE					m_State = STATE_IDLE;	
	CTransform*				m_pTransform = nullptr;
	CShader*				m_pShader = nullptr;
	CRenderer*				m_pRenderer = nullptr;
	CMeshDynamic*			m_pMeshDynamic = nullptr;
	vector<CCollider*>		m_pCollider;


	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();
	

	explicit CDemon(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CDemon(const CDemon & rhs);
	virtual ~CDemon() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CDemon* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
