#include "..\Header\VIBuffer.h"



D3DXVECTOR3 CVIBuffer::VertexNoramlize(D3DXVECTOR3 First, D3DXVECTOR3 Second, D3DXVECTOR3 Third)
{
	D3DXVECTOR3 u = Second - First;
	D3DXVECTOR3 v = Third - First;

	D3DXVECTOR3 pOut;
	D3DXVec3Cross(&pOut, &u, &v);

	D3DXVec3Normalize(&pOut, &pOut);


	return pOut;
}

HRESULT CVIBuffer::CreateBuffer()
{
	if (m_pGraphicDev == nullptr)
		return E_FAIL;

	m_pGraphicDev->CreateVertexBuffer(iVertexSize * iVertexNum, D3DUSAGE_WRITEONLY, dwFVF, D3DPOOL_MANAGED, &VB, 0);
	m_pGraphicDev->CreateIndexBuffer(iIndexSize * iIndexNum, D3DUSAGE_WRITEONLY, D3DFormat, D3DPOOL_MANAGED, &IB, 0);
	
	return NOERROR;
}

CVIBuffer::CVIBuffer(LPDIRECT3DDEVICE9	_m_pGraphicDev)
	:CComponent(_m_pGraphicDev)
{
	
}

CVIBuffer::CVIBuffer(const CVIBuffer & rhs)
	: CComponent(rhs.m_pGraphicDev),
	iVertexNum(rhs.iVertexNum),
	iIndexNum(rhs.iIndexNum),
	iPolygonsize(rhs.iPolygonsize),
	iVertexSize(rhs.iVertexSize),
	iIndexSize(rhs.iIndexSize),
	D3DFormat(rhs.D3DFormat),
	dwFVF(rhs.dwFVF),
	VB(rhs.VB),
	IB(rhs.IB)

{
	VB->AddRef();
	IB->AddRef();
}

HRESULT CVIBuffer::Initialize()
{
	return NOERROR;
}

_int CVIBuffer::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CVIBuffer::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CVIBuffer::Render()
{
	if (nullptr == m_pGraphicDev)
		return E_FAIL;

	m_pGraphicDev->SetStreamSource(0, VB, 0, iVertexSize);
	m_pGraphicDev->SetFVF(dwFVF);
	m_pGraphicDev->SetIndices(IB);
	m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, iVertexNum, 0, iPolygonsize);
	return NOERROR;
}

void CVIBuffer::Free()
{
	Safe_Release(VB);
	Safe_Release(IB);
	CComponent::Free();
}


