#pragma once
#include "LightObject.h"

_BEGIN(Client)
class CWallTorchAngle :
	public CLightObject
{
private:
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();

	explicit CWallTorchAngle(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CWallTorchAngle(const CWallTorchAngle & rhs);
	virtual ~CWallTorchAngle() = default;

public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CWallTorchAngle* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
