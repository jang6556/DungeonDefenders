#pragma once
#include "MonsterUI.h"

_BEGIN(Client)
class CMonsterHpNum :
	public CMonsterUI
{
public:
	enum DIGIT { DIGIT_HUNDRED, DIGIT_TEN, DIGIT_ONE, DIGIT_END};
private:
	DIGIT	m_eDigit;
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();

	explicit CMonsterHpNum(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CMonsterHpNum(const CMonsterHpNum & rhs);
	virtual ~CMonsterHpNum() = default;

public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	HRESULT SetDigit(DIGIT eType);

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CMonsterHpNum* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
