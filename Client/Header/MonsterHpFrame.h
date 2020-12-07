#pragma once
#include "MonsterUI.h"

_BEGIN(Client)
class CMonsterHpFrame :
	public CMonsterUI
{
private:	
	
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();

	explicit CMonsterHpFrame(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CMonsterHpFrame(const CMonsterHpFrame & rhs);
	virtual ~CMonsterHpFrame() = default;

public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CMonsterHpFrame* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
