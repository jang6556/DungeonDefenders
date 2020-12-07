#pragma once
#include "PlayerUI.h"

_BEGIN(Client)
class CWaveInfo :
	public CPlayerUI
{
private:
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	explicit CWaveInfo(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CWaveInfo(const CWaveInfo & rhs);
	virtual ~CWaveInfo() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CWaveInfo* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END

