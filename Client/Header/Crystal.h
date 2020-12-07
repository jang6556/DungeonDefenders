#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CCrystal :
	public CGameObject
{
private:
	CRenderer*				m_pRenderer = nullptr;
	CTransform*				m_pTransform = nullptr;
	list<CGameObject*>		m_pCrystal;

	vector<CCollider*>		m_pCollider;

	int						m_iMaxHp = 1000;
	int						m_iCurrHp = 1000;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	


	explicit CCrystal(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CCrystal(const CCrystal & rhs);
	virtual ~CCrystal() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;
	virtual HRESULT RenderShadow() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;


	HRESULT	SetDamage(_int iDamage);

	static CCrystal* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);

};
_END
