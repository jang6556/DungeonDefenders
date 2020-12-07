#pragma once
#include "StatUI.h"

_BEGIN(Client)
class CStatBackGround :
	public CStatUI
{
private:
	bool					m_bClick=false;
	POINT					m_vMousePoint;
	virtual HRESULT Initialize() override;
	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CStatBackGround(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CStatBackGround(const CStatBackGround & rhs);
	virtual ~CStatBackGround() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;
	
	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CStatBackGround* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
