#pragma once
#include "StaticMapObject.h"

_BEGIN(Client)
class CBridgeWall :
	public CStaticMapObject
{
private:
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();


	explicit CBridgeWall(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CBridgeWall(const CBridgeWall & rhs);
	virtual ~CBridgeWall() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CBridgeWall* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
