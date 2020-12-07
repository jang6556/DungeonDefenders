#pragma once
#include "LightObject.h"

_BEGIN(Client)
class CWallTorchLong :
	public CLightObject
{
private:
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();

	explicit CWallTorchLong(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CWallTorchLong(const CWallTorchLong & rhs);
	virtual ~CWallTorchLong() = default;

public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CWallTorchLong* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
