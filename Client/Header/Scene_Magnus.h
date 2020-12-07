#pragma once
#include "Scene.h"

_BEGIN(Client)
class CScene_Magnus :
	public CScene
{
public:
	enum MAPOBJECT { MAGUNUSSQUARTER, CROSSSTAIR, LONGSTAIR, SIDESTAIR, SHORTSTAIR, 
					 TRESURECHEST, ARCANEPAD,CENTER_ARCH,CENTER_UP,CENTER_WALL,SET_RAIL,LONG_RAIL,
					 DOUBLE_RAIL,BRIDGE_WALL,CRYSTAL_STAFF, WALLTORCH_DOUBLE, WALLTORCH_TRIPLE, 
					 WALLTORCH_ANGLE, WALLTORCH_HEIGHT, WALLTORCH_SINGLE, WALLTORCH_LONG,SHORT_RAIL,
					 ROOF,SINGLE_BRIDGE,WALL_BANNER_0, WALL_BANNER_1, WALL_BANNER_2, WALL_BANNER_3, WALL_BANNER_4, WALL_BANNER_5, WALL_BANNER_6,
					 LARGE_CRYSTALSTAFF, BARREL_0, BARREL_1, BARREL_2, BARREL_3, TABLE_0, TABLE_1, DOOR,LAVA_EFFECT_0, LAVA_EFFECT_1, MAPOBJECTEND };
private:
	virtual HRESULT SetGameObjectPrototype() override;
	virtual HRESULT SetComponentPrototype() override;
	virtual HRESULT SetGameObject()  override;
	virtual HRESULT LoadGameObject() override;


	explicit CScene_Magnus(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	virtual ~CScene_Magnus() = default;
public:
	virtual HRESULT Initialize() override;
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual	_int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	static CScene_Magnus* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);

	void Free() override;
};
_END
