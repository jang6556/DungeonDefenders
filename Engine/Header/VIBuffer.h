#pragma once
#include "Component.h"
#include "Transform.h"
_BEGIN(Engine)
class _DLLEXPORTS CVIBuffer :
	public CComponent
{
protected:
	IDirect3DVertexBuffer9* VB = nullptr;
	IDirect3DIndexBuffer9*  IB = nullptr;
	
	_uint					iVertexNum		= 0;
	_uint					iIndexNum		= 0;
	_uint					iPolygonsize		= 0;
	_uint					iVertexSize		= 0;
	_uint					iIndexSize		= 0;
	D3DFORMAT				D3DFormat;
	DWORD					dwFVF;

	D3DXVECTOR3 VertexNoramlize(D3DXVECTOR3 First, D3DXVECTOR3 Second, D3DXVECTOR3 Third);
	HRESULT CreateBuffer();

	explicit CVIBuffer(LPDIRECT3DDEVICE9	_m_pGraphicDev);
	explicit CVIBuffer(const CVIBuffer& rhs);
	virtual ~CVIBuffer() = default;
public:
	virtual HRESULT Initialize();
	virtual _int	Progress(const _float& fTimeDelta);
	virtual _int	LateProgress(const _float& fTimeDelta);
	virtual HRESULT Render();

	virtual CComponent* Clone() PURE;

	virtual void Free();
};
_END
