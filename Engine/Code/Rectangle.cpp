#include "..\Header\Rectangle.h"





CRectangle::CRectangle(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CVIBuffer(_m_pGraphicDev)
{
}

CRectangle::CRectangle(const CRectangle & rhs)
	:CVIBuffer(rhs)
{
}

HRESULT CRectangle::Initialize()
{
	iVertexSize = 36;
	iIndexSize = 64;
	m_pGraphicDev->CreateVertexBuffer(sizeof(VertexNormal) * iVertexSize, D3DUSAGE_WRITEONLY, D3DFVF_XYZ | D3DFVF_NORMAL, D3DPOOL_MANAGED, &VB, 0);
	m_pGraphicDev->CreateIndexBuffer(sizeof(DWORD) * iIndexSize, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &IB, 0);

	VertexNormal* pVertex = nullptr;

	VB->Lock(0, 0, (void**)&pVertex, 0);
	//전면
	pVertex[0] = VertexNormal(D3DXVECTOR3(-2.f, -3.f, -1.f));
	pVertex[1] = VertexNormal(D3DXVECTOR3(-2.f,  3.f, -1.f));
	pVertex[2] = VertexNormal(D3DXVECTOR3( 2.f,  3.f, -1.f));

	pVertex[0].vNormal = VertexNoramlize(pVertex[0].vPosition, pVertex[1].vPosition, pVertex[2].vPosition);
	pVertex[1].vNormal = VertexNoramlize(pVertex[0].vPosition, pVertex[1].vPosition, pVertex[2].vPosition);
	pVertex[2].vNormal = VertexNoramlize(pVertex[0].vPosition, pVertex[1].vPosition, pVertex[2].vPosition);

	pVertex[3] = VertexNormal(D3DXVECTOR3(-2.f, -3.f, -1.f));
	pVertex[4] = VertexNormal(D3DXVECTOR3(2.f, 3.f, -1.f));
	pVertex[5] = VertexNormal(D3DXVECTOR3(2.f, -3.f, -1.f));

	pVertex[3].vNormal = VertexNoramlize(pVertex[3].vPosition, pVertex[4].vPosition, pVertex[5].vPosition);
	pVertex[4].vNormal = VertexNoramlize(pVertex[3].vPosition, pVertex[4].vPosition, pVertex[5].vPosition);
	pVertex[5].vNormal = VertexNoramlize(pVertex[3].vPosition, pVertex[4].vPosition, pVertex[5].vPosition);
	//후면
	pVertex[6] = VertexNormal(D3DXVECTOR3(2.f, -3.f, 1.f));
	pVertex[7] = VertexNormal(D3DXVECTOR3(2.f, 3.f, 1.f));
	pVertex[8] = VertexNormal(D3DXVECTOR3(-2.f, 3.f, 1.f));

	pVertex[6].vNormal = VertexNoramlize(pVertex[6].vPosition, pVertex[7].vPosition, pVertex[8].vPosition);
	pVertex[7].vNormal = VertexNoramlize(pVertex[6].vPosition, pVertex[7].vPosition, pVertex[8].vPosition);
	pVertex[8].vNormal = VertexNoramlize(pVertex[6].vPosition, pVertex[7].vPosition, pVertex[8].vPosition);
																							 
	pVertex[9 ] = VertexNormal(D3DXVECTOR3( 2.f, -3.f,1.f));
	pVertex[10] = VertexNormal(D3DXVECTOR3(-2.f, 3.f,  1.f));
	pVertex[11] = VertexNormal(D3DXVECTOR3(-2.f, -3.f, 1.f));

	pVertex[9].vNormal = VertexNoramlize(pVertex[9].vPosition, pVertex[10].vPosition, pVertex[11].vPosition);
	pVertex[10].vNormal = VertexNoramlize(pVertex[9].vPosition, pVertex[10].vPosition, pVertex[11].vPosition);
	pVertex[11].vNormal = VertexNoramlize(pVertex[9].vPosition, pVertex[10].vPosition, pVertex[11].vPosition);
	//우측
	pVertex[12] = VertexNormal(D3DXVECTOR3(2.f, -3.f, -1.f));
	pVertex[13] = VertexNormal(D3DXVECTOR3(2.f,  3.f, -1.f));
	pVertex[14] = VertexNormal(D3DXVECTOR3(2.f,  3.f,  1.f));

	pVertex[12].vNormal = VertexNoramlize(pVertex[12].vPosition, pVertex[13].vPosition, pVertex[14].vPosition);
	pVertex[13].vNormal = VertexNoramlize(pVertex[12].vPosition, pVertex[13].vPosition, pVertex[14].vPosition);
	pVertex[14].vNormal = VertexNoramlize(pVertex[12].vPosition, pVertex[13].vPosition, pVertex[14].vPosition);

	pVertex[15] = VertexNormal(D3DXVECTOR3(2.f, -3.f, -1.f));
	pVertex[16] = VertexNormal(D3DXVECTOR3(2.f, 3.f, 1.f));
	pVertex[17] = VertexNormal(D3DXVECTOR3(2.f, -3.f, 1.f));

	pVertex[15].vNormal = VertexNoramlize(pVertex[15].vPosition, pVertex[16].vPosition, pVertex[17].vPosition);
	pVertex[16].vNormal = VertexNoramlize(pVertex[15].vPosition, pVertex[16].vPosition, pVertex[17].vPosition);
	pVertex[17].vNormal = VertexNoramlize(pVertex[15].vPosition, pVertex[16].vPosition, pVertex[17].vPosition);
	//좌측
	pVertex[18] = VertexNormal(D3DXVECTOR3(-2.f, -3.f, 1.f));
	pVertex[19] = VertexNormal(D3DXVECTOR3(-2.f, 3.f, 1.f));
	pVertex[20] = VertexNormal(D3DXVECTOR3(-2.f, 3.f, -1.f));

	pVertex[18].vNormal = VertexNoramlize(pVertex[18].vPosition, pVertex[19].vPosition, pVertex[20].vPosition);
	pVertex[19].vNormal = VertexNoramlize(pVertex[18].vPosition, pVertex[19].vPosition, pVertex[20].vPosition);
	pVertex[20].vNormal = VertexNoramlize(pVertex[18].vPosition, pVertex[19].vPosition, pVertex[20].vPosition);

	pVertex[21] = VertexNormal(D3DXVECTOR3(-2.f, -3.f, 1.f));
	pVertex[22] = VertexNormal(D3DXVECTOR3(-2.f, 3.f, -1.f));
	pVertex[23] = VertexNormal(D3DXVECTOR3(-2.f, -3.f, -1.f));

	pVertex[21].vNormal = VertexNoramlize(pVertex[21].vPosition, pVertex[22].vPosition, pVertex[23].vPosition);
	pVertex[22].vNormal = VertexNoramlize(pVertex[21].vPosition, pVertex[22].vPosition, pVertex[23].vPosition);
	pVertex[23].vNormal = VertexNoramlize(pVertex[21].vPosition, pVertex[22].vPosition, pVertex[23].vPosition);
	//위
	pVertex[24] = VertexNormal(D3DXVECTOR3(-2.f, 3.f, -1.f));
	pVertex[25] = VertexNormal(D3DXVECTOR3(-2.f, 3.f, 1.f));
	pVertex[26] = VertexNormal(D3DXVECTOR3(2.f,  3.f, 1.f));

	pVertex[24].vNormal = VertexNoramlize(pVertex[24].vPosition, pVertex[25].vPosition, pVertex[26].vPosition);
	pVertex[25].vNormal = VertexNoramlize(pVertex[24].vPosition, pVertex[25].vPosition, pVertex[26].vPosition);
	pVertex[26].vNormal = VertexNoramlize(pVertex[24].vPosition, pVertex[25].vPosition, pVertex[26].vPosition);

	pVertex[27] = VertexNormal(D3DXVECTOR3(-2.f, 3.f, -1.f));
	pVertex[28] = VertexNormal(D3DXVECTOR3( 2.f, 3.f, 1.f));
	pVertex[29] = VertexNormal(D3DXVECTOR3( 2.f, 3.f, -1.f));

	pVertex[27].vNormal = VertexNoramlize(pVertex[27].vPosition, pVertex[28].vPosition, pVertex[29].vPosition);
	pVertex[28].vNormal = VertexNoramlize(pVertex[27].vPosition, pVertex[28].vPosition, pVertex[29].vPosition);
	pVertex[29].vNormal = VertexNoramlize(pVertex[27].vPosition, pVertex[28].vPosition, pVertex[29].vPosition);
	//아래
	pVertex[30] = VertexNormal(D3DXVECTOR3(-2.f, -3.f, 1.f));
	pVertex[31] = VertexNormal(D3DXVECTOR3(-2.f, -3.f, -1.f));
	pVertex[32] = VertexNormal(D3DXVECTOR3( 2.f, -3.f, -1.f));

	pVertex[30].vNormal = VertexNoramlize(pVertex[30].vPosition, pVertex[31].vPosition, pVertex[32].vPosition);
	pVertex[31].vNormal = VertexNoramlize(pVertex[30].vPosition, pVertex[31].vPosition, pVertex[32].vPosition);
	pVertex[32].vNormal = VertexNoramlize(pVertex[30].vPosition, pVertex[31].vPosition, pVertex[32].vPosition);

	pVertex[33] = VertexNormal(D3DXVECTOR3(-2.f, -3.f, 1.f));
	pVertex[34] = VertexNormal(D3DXVECTOR3(2.f, -3.f, -1.f));
	pVertex[35] = VertexNormal(D3DXVECTOR3(2.f, -3.f, 1.f));

	pVertex[33].vNormal = VertexNoramlize(pVertex[33].vPosition, pVertex[34].vPosition, pVertex[35].vPosition);
	pVertex[34].vNormal = VertexNoramlize(pVertex[33].vPosition, pVertex[34].vPosition, pVertex[35].vPosition);
	pVertex[35].vNormal = VertexNoramlize(pVertex[33].vPosition, pVertex[34].vPosition, pVertex[35].vPosition);

	VB->Unlock();


	WORD* Indices = nullptr;

	IB->Lock(0, 0, (void**)&Indices, 0);

	Indices[0] = 0; Indices[1] = 1; Indices[2] = 2;
	Indices[3] = 3; Indices[4] = 4; Indices[5] = 5;
	Indices[6] = 6; Indices[7] = 7; Indices[8] = 8;
	Indices[9] = 9; Indices[10] = 10; Indices[11] = 11;
	Indices[12] = 12; Indices[13] = 13; Indices[14] = 14;
	Indices[15] = 15; Indices[16] = 16; Indices[17] = 17;
	Indices[18] = 18; Indices[19] = 19; Indices[20] = 20;
	Indices[21] = 21; Indices[22] = 22; Indices[23] = 23;
	Indices[24] = 24; Indices[25] = 25; Indices[26] = 26;
	Indices[27] = 27; Indices[28] = 28; Indices[29] = 29;
	Indices[30] = 30; Indices[31] = 31; Indices[32] = 32;
	Indices[33] = 33; Indices[34] = 34; Indices[35] = 35;
	IB->Unlock();


	m_Material.Ambient = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	m_Material.Specular = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	m_Material.Diffuse = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	m_Material.Emissive = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
	m_Material.Power = 5.f;

	return NOERROR;
}

_int CRectangle::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CRectangle::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CRectangle::Render(CTransform* pTransform)
{
	D3DMATERIAL9 pOut;
	m_pGraphicDev->GetMaterial(&pOut);
	m_pGraphicDev->SetMaterial(&m_Material);
	m_pGraphicDev->SetStreamSource(0, VB, 0, sizeof(VertexNormal));
	m_pGraphicDev->SetIndices(IB);
	m_pGraphicDev->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL);


	m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, iVertexSize, 0, 12);
	//m_pGraphicDev->SetMaterial(&pOut);
	return NOERROR;
}

CRectangle * CRectangle::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CRectangle*	pInstance = new CRectangle(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CRectangle Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent * CRectangle::Clone()
{
	return new CRectangle(*this);
}

void CRectangle::Free()
{
	CVIBuffer::Free();
}
