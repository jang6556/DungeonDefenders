#pragma once
#include "Component.h"

_BEGIN(Engine)
class CTransform;
class _DLLEXPORTS CFrustum :
	public CComponent
{
private:
	D3DXVECTOR3 m_vPoint[8];

	HRESULT Initialize();

	HRESULT TransformLocal(D3DXMATRIX _matWorldInv, D3DXVECTOR3* _PointArray);
	HRESULT MakePlane(D3DXVECTOR3* _PointArray, D3DXPLANE* _pPlane);

	explicit CFrustum(LPDIRECT3DDEVICE9	_m_pGraphicDev);
	explicit CFrustum(const CFrustum& rhs);
	virtual ~CFrustum() = default;
	
public:
	bool IsInFrustum(D3DXVECTOR3 _vPosition, CTransform* _pTransform, float _fRadius = 0.f);
	bool IsInFrustumLight(D3DXVECTOR3 _vPosition, float _fRadius = 0.f);
		
	virtual CComponent* Clone();
	virtual void Free();

	static CFrustum* Create(LPDIRECT3DDEVICE9	_m_pGraphicDev);
};
_END

