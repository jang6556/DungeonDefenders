#pragma once
#include "Monster.h"

_BEGIN(Client)
class CKobold :
	public CMonster
{
private:
	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	explicit CKobold(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CKobold(const CKobold & rhs);
	virtual ~CKobold() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CKobold* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
