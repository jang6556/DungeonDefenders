#pragma once
#include "Component.h"
#include "Collider.h"

_BEGIN(Engine)
class _DLLEXPORTS CColliederDetector :
	public CComponent
{
public:
	enum COLLISIONTYPE { AABB, OBB, SPHERE, COLLISIONTYPEEND };
private:
	list<CCollider*>		CColliederDetectorList[RENDERTYPEEND];

	explicit CColliederDetector(LPDIRECT3DDEVICE9	_m_pGraphicDev);
	virtual ~CColliederDetector() = default;
public:
	virtual HRESULT Initialize();
	virtual _int	Progress(const _float& fTimeDelta);
	virtual _int	LateProgress(const _float& fTimeDelta);
	virtual HRESULT Render();

	HRESULT AddRenderGroup(RENDERTYPE eType, CGameObject* pGameObject);

	static CColliederDetector* Create(LPDIRECT3DDEVICE9	_m_pGraphicDev);
	virtual CComponent* Clone();
	virtual void Free();
};
_END
