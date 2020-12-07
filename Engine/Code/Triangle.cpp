#include "..\Header\Triangle.h"



CTriangle::CTriangle(LPDIRECT3DDEVICE9	_m_pGraphicDev)
	:CVIBuffer(_m_pGraphicDev)
{

}

CTriangle::CTriangle(const CTriangle & rhs)
	: CVIBuffer(rhs.m_pGraphicDev)
{
}

HRESULT CTriangle::Initialize()
{
	m_pGraphicDev->CreateVertexBuffer(sizeof(Vertex) * 3, D3DUSAGE_WRITEONLY, D3DFVF_XYZ | D3DFVF_NORMAL, D3DPOOL_MANAGED, &VB, 0);
	m_pGraphicDev->CreateIndexBuffer(sizeof(DWORD) * 16, D3DUSAGE_WRITEONLY,D3DFMT_INDEX16, D3DPOOL_MANAGED, &IB, 0);

	Vertex* pVertex = nullptr;

	VB->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0] = Vertex(D3DXVECTOR3(0.f, 1.f, 1.f));
	pVertex[1] = Vertex(D3DXVECTOR3(1.f, -1.f, 1.f));
	pVertex[2] = Vertex(D3DXVECTOR3(-1.f, -1.f, 1.f));
	
	VB->Unlock();


	WORD* Indices = nullptr;

	IB->Lock(0, 0, (void**)&Indices, 0);

	Indices[0] = 0; Indices[1] = 1; Indices[2] = 2;

	IB->Unlock();



	return NOERROR;
}

_int CTriangle::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CTriangle::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CTriangle::Render(CTransform* pTransform)
{
	m_pGraphicDev->SetStreamSource(0, VB, 0, sizeof(Vertex));
	m_pGraphicDev->SetIndices(IB);
	m_pGraphicDev->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL);
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pGraphicDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
	return NOERROR;
}

CTriangle * CTriangle::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CTriangle*	pInstance = new CTriangle(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CTriangle Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent * CTriangle::Clone()
{	
	return new CTriangle(*this);
}

void CTriangle::Free()
{
	CVIBuffer::Free();
}


