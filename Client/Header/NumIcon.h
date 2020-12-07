#pragma once
#include "StatUI.h"

_BEGIN(Client)
class CNumIcon :
	public CStatUI
{
private:
	virtual HRESULT Initialize() override;
	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	explicit CNumIcon(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CNumIcon(const CNumIcon & rhs);
	virtual ~CNumIcon() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	HRESULT SetTextureNum(int iNum);
	HRESULT SetScale(float fScale);

	virtual void Free() override;

	static CNumIcon* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
