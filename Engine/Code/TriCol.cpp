#include "..\Header\TriCol.h"



CTriCol::CTriCol(LPDIRECT3DDEVICE9	_m_pGraphicDev)
	:CVIBuffer(_m_pGraphicDev)
{
}

CTriCol::CTriCol(const CTriCol & rhs)
	: CVIBuffer(rhs.m_pGraphicDev)
{
}

HRESULT CTriCol::Initialize()
{
	m_pGraphicDev->CreateVertexBuffer(sizeof(VertexCol) * 18, D3DUSAGE_WRITEONLY, D3DFVF_XYZ | D3DFVF_DIFFUSE, D3DPOOL_MANAGED, &VB, 0);
	m_pGraphicDev->CreateIndexBuffer(sizeof(DWORD) * 64, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &IB, 0);

	VertexCol* pVertex = nullptr;

	VB->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0] = VertexCol(D3DXVECTOR3(-1,0,-1),D3DCOLOR_XRGB(0,255,0));
	pVertex[1] = VertexCol(D3DXVECTOR3(0, 2, 0), D3DCOLOR_XRGB(255, 0, 0));
	pVertex[2] = VertexCol(D3DXVECTOR3(1,0,-1), D3DCOLOR_XRGB(255, 0, 0));

	pVertex[3] = VertexCol(D3DXVECTOR3(1, 0, -1), D3DCOLOR_XRGB(255, 255, 0));
	pVertex[4] = VertexCol(D3DXVECTOR3(0, 2, 0), D3DCOLOR_XRGB(255, 0, 0));
	pVertex[5] = VertexCol(D3DXVECTOR3(1, 0, 1), D3DCOLOR_XRGB(255, 0, 0));
	
	pVertex[6] = VertexCol(D3DXVECTOR3(1, 0, 1), D3DCOLOR_XRGB(255, 0, 255));
	pVertex[7] = VertexCol(D3DXVECTOR3(0, 2, 0), D3DCOLOR_XRGB(255, 0, 0));
	pVertex[8] = VertexCol(D3DXVECTOR3(-1, 0, 1), D3DCOLOR_XRGB(255, 0, 0));

	pVertex[9] = VertexCol(D3DXVECTOR3(-1, 0, 1), D3DCOLOR_XRGB(0, 255, 255));
	pVertex[10] = VertexCol(D3DXVECTOR3(0, 2, 0), D3DCOLOR_XRGB(255, 0, 0));
	pVertex[11] = VertexCol(D3DXVECTOR3(-1, 0, -1), D3DCOLOR_XRGB(255, 0, 0));

	pVertex[12] = VertexCol(D3DXVECTOR3(-1, 0, -1), D3DCOLOR_XRGB(255, 0, 0));
	pVertex[13] = VertexCol(D3DXVECTOR3(1, 0, -1), D3DCOLOR_XRGB(255, 0, 0));
	pVertex[14] = VertexCol(D3DXVECTOR3(1, 0, 1), D3DCOLOR_XRGB(255, 0, 0));

	pVertex[15] = VertexCol(D3DXVECTOR3(-1, 0, -1), D3DCOLOR_XRGB(255, 0, 0));
	pVertex[16] = VertexCol(D3DXVECTOR3(1,0,1), D3DCOLOR_XRGB(255, 0, 0));
	pVertex[17] = VertexCol(D3DXVECTOR3(-1, 0, 1), D3DCOLOR_XRGB(255, 0, 0));




	VB->Unlock();


	WORD* Indices = nullptr;

	IB->Lock(0, 0, (void**)&Indices, 0);

	Indices[0] = 0; Indices[1] = 1; Indices[2] = 2;
	Indices[3] = 3; Indices[4] = 4; Indices[5] = 5;
	Indices[6] = 6; Indices[7] = 7; Indices[8] = 8;
	Indices[9] = 9; Indices[10] = 10; Indices[11] = 11;
	Indices[12] = 12; Indices[13] = 13; Indices[14] = 14;
	Indices[15] = 15; Indices[16] = 16; Indices[17] = 17;
	

	IB->Unlock();



	return NOERROR;
}

_int CTriCol::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CTriCol::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CTriCol::Render(CTransform* pTransform)
{
	m_pGraphicDev->SetStreamSource(0, VB, 0, sizeof(VertexCol));
	m_pGraphicDev->SetIndices(IB);
	m_pGraphicDev->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);

	m_pGraphicDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 6);
	return NOERROR;
}

CTriCol * CTriCol::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CTriCol*	pInstance = new CTriCol(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CTriCol Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent * CTriCol::Clone()
{
	CTriCol*	pInstance = new CTriCol(*this);
	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CTriCol Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTriCol::Free()
{
	CVIBuffer::Free();
}


