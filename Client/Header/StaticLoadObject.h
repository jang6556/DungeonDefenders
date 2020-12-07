#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CStaticLoadObject :
	public CGameObject
{
public:
	enum MAPOBJECT {
		MAGUNUSSQUARTER, CROSSSTAIR, LONGSTAIR, SIDESTAIR, SHORTSTAIR,
		TRESURECHEST, ARCANEPAD, CENTER_ARCH, CENTER_UP, CENTER_WALL, SET_RAIL, LONG_RAIL,
		DOUBLE_RAIL, BRIDGE_WALL, CRYSTAL_STAFF, WALLTORCH_DOUBLE, WALLTORCH_TRIPLE,
		WALLTORCH_ANGLE, WALLTORCH_HEIGHT, WALLTORCH_SINGLE, WALLTORCH_LONG, SHORT_RAIL,
		ROOF, SINGLE_BRIDGE, WALL_BANNER_0, WALL_BANNER_1, WALL_BANNER_2, WALL_BANNER_3, WALL_BANNER_4, WALL_BANNER_5, WALL_BANNER_6,
		LARGE_CRYSTALSTAFF, BARREL_0, BARREL_1, BARREL_2, BARREL_3, TABLE_0, TABLE_1, DOOR, MAPOBJECTEND	};
protected:
	CTransform*		m_pTransform = nullptr;
	CShader*		m_pShader = nullptr;
	CRenderer*		m_pRenderer = nullptr;
	CMeshStatic*	m_pMeshStatic = nullptr;
	CFrustum*		m_pFrustum = nullptr;

	float			m_fTimeDelta = 0.f;
	float			m_fRadius = 5.f;
	int				m_iShaderPassNum = 0;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();

	HRESULT SetMesh(MAPOBJECT _iType);


	explicit CStaticLoadObject(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CStaticLoadObject(const CStaticLoadObject & rhs);
	virtual ~CStaticLoadObject() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;
	virtual HRESULT RenderShadow() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CStaticLoadObject* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
