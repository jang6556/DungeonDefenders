#pragma once
#include "Base.h"

_BEGIN(Engine)
class CShader;
class _DLLEXPORTS CMonSphere :
	public CBase
{
private:
	LPDIRECT3DDEVICE9	m_pGraphicDevice;
	CShader*			m_pShader = nullptr;
	LPD3DXMESH			m_pMesh = nullptr;

	D3DXVECTOR3			m_vPosition;

	HRESULT	 Initialize(D3DXVECTOR3 _vPosition);

	explicit CMonSphere(LPDIRECT3DDEVICE9	_m_pGraphicDevice);
	virtual ~CMonSphere() = default;
public:
	HRESULT Render();
	virtual void Free();

	D3DXVECTOR3 GetPosition() { return m_vPosition; }

	static CMonSphere* Create(LPDIRECT3DDEVICE9 _m_pGraphicDevice, D3DXVECTOR3 _vPosition);
};
_END
