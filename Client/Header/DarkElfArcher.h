#pragma once
#include "Monster.h"

_BEGIN(Client)
class CDarkElfArcher :
	public CMonster
{
private:
	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CDarkElfArcher(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CDarkElfArcher(const CDarkElfArcher & rhs);
	virtual ~CDarkElfArcher() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CDarkElfArcher* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
