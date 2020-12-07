#include "..\Header\Wall.h"



CWall::CWall(LPDIRECT3DDEVICE9	_m_pGraphicDev)
	:CVIBuffer(_m_pGraphicDev)
{
}

CWall::CWall(const CWall & rhs)
	:CVIBuffer(rhs)
	
{

}

HRESULT CWall::Initialize()
{
	iVertexSize = 4;
	iIndexSize = 6;
	m_pGraphicDev->CreateVertexBuffer(sizeof(VertexUV) * iVertexSize, D3DUSAGE_WRITEONLY, D3DFVF_XYZ | D3DFVF_TEX1, D3DPOOL_MANAGED, &VB, 0);
	m_pGraphicDev->CreateIndexBuffer(sizeof(DWORD) * iIndexSize, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &IB, 0);

	VertexUV* pVertex = nullptr;

	VB->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0] = VertexUV(D3DXVECTOR3(-1.f, -1.f, 0.f), D3DXVECTOR2(0.f, 1.f));
	pVertex[1] = VertexUV(D3DXVECTOR3(-1.f,  1.f, 0.f),D3DXVECTOR2(0.f,0.f));
	pVertex[2] = VertexUV(D3DXVECTOR3( 1.f,  1.f, 0.f), D3DXVECTOR2(1.f, 0.f));
	pVertex[3] = VertexUV(D3DXVECTOR3( 1.f, -1.f, 0.f), D3DXVECTOR2(1.f, 1.f));
	
	

	VB->Unlock();


	WORD* Indices = nullptr;

	IB->Lock(0, 0, (void**)&Indices, 0);

	Indices[0] = 0; Indices[1] = 1; Indices[2] = 2;
	Indices[3] = 0; Indices[4] = 2; Indices[5] = 3;
	IB->Unlock();


	m_Material.Ambient = D3DXCOLOR(0.f,0.f,0.f,1.f);
	m_Material.Specular = D3DXCOLOR(0.f, 0.f, 0.f, 1.f);
	m_Material.Diffuse = D3DXCOLOR(0.f, 0.f, 0.f, 1.f);
	m_Material.Emissive = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
	m_Material.Power = 5.f;

	return NOERROR;
}

_int CWall::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CWall::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CWall::Render(CTransform* pTransform)
{
	
	
	m_pGraphicDev->SetStreamSource(0, VB, 0, sizeof(VertexUV));
	m_pGraphicDev->SetIndices(IB);
	m_pGraphicDev->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	
	m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0,0, iVertexSize,0,2);
	
	return NOERROR;
}

CWall * CWall::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CWall*	pInstance = new CWall(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CWall Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent * CWall::Clone()
{
	return new CWall(*this);
}

void CWall::Free()
{
	CVIBuffer::Free();
}
