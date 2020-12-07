#include "..\Header\Terrain.h"
#include <time.h>


CTerrain::CTerrain(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CVIBuffer(_m_pGraphicDev)
{
}

CTerrain::CTerrain(const CTerrain & rhs)
	: CVIBuffer(rhs)
{

}

HRESULT CTerrain::Initialize()
{
	
	¸¸¾à(m_pGraphicDev == nullptr)
		return E_FAIL;
	
	HANDLE hFile = 0;
	_ulong dwByte = 0;

	hFile = CreateFile(L"../Texture/Height.bmp", GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if(hFile==0)
		return E_FAIL;

	BITMAPFILEHEADER fh;
	BITMAPINFOHEADER ih;

	ReadFile(hFile, &fh, sizeof(BITMAPFILEHEADER), &dwByte, nullptr);
	ReadFile(hFile, &ih, sizeof(BITMAPINFOHEADER), &dwByte, nullptr);

	_ulong* pPixel = new _ulong[ih.biHeight*ih.biWidth];

	ReadFile(hFile, pPixel, sizeof(_ulong) * ih.biHeight * ih.biWidth, &dwByte, nullptr);
	CloseHandle(hFile);

	_uint iVertexSizeX = 0, iVertexSizeZ = 0;

	iVertexSizeX = ih.biWidth;
	iVertexSizeZ = ih.biHeight;


	
	iVertexSize = iVertexSizeX*iVertexSizeZ;
	
	iPolysize = (iVertexSizeX-1)*(iVertexSizeZ-1) * 2;
	m_pGraphicDev->CreateVertexBuffer(sizeof(VertexUV) * iVertexSize, D3DUSAGE_WRITEONLY, D3DFVF_XYZ | D3DFVF_TEX1, D3DPOOL_MANAGED, &VB, 0);
	m_pGraphicDev->CreateIndexBuffer(sizeof(DWORD) * iPolysize*2, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &IB, 0);

	VertexUV* pVertex = nullptr;

	VB->Lock(0, 0, (void**)&pVertex, 0);
	
	for (int i = 0; i < iVertexSizeZ; ++i)
	{
		for (int j = 0; j < iVertexSizeX; ++j)
		{			
			pVertex[i*iVertexSizeX + j] = VertexUV(D3DXVECTOR3(j, (pPixel[i*iVertexSizeX + j] & 0x000000ff) / 10.f, i), D3DXVECTOR2(j/(iVertexSizeX-1.f)*100, i / (iVertexSizeZ - 1.f) * 100));
		}
	}

	VB->Unlock();


	WORD* Indices = nullptr;
	_int iIndex = 0;
	IB->Lock(0, 0, (void**)&Indices, 0);

	for (int i = 0; i < (iVertexSizeZ-1); ++i)
	{
		for (int j = 0; j < (iVertexSizeX-1); ++j)
		{
			_uint		iIndexVertex = i * iVertexSizeX + j;

			Indices[iIndex++] = iIndexVertex;
			Indices[iIndex++] = iIndexVertex + iVertexSizeX;
			Indices[iIndex++] = iIndexVertex + iVertexSizeX + 1;

			Indices[iIndex++] = iIndexVertex;
			Indices[iIndex++] = iIndexVertex + iVertexSizeX + 1;
			Indices[iIndex++] = iIndexVertex + 1;
		}
	}

	IB->Unlock();
	return NOERROR;
}

_int CTerrain::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CTerrain::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CTerrain::Render(CTransform* pTransform)
{
	m_pGraphicDev->SetStreamSource(0, VB, 0, sizeof(VertexUV));
	m_pGraphicDev->SetIndices(IB);
	m_pGraphicDev->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	//m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);

	m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, iVertexSize, 0, iPolysize);
	return NOERROR;
}

CTerrain * CTerrain::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CTerrain*	pInstance = new CTerrain(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CTerrain Created Failed");
		Safe_Release(pInstance);
	}

	return pInstance;

}

CComponent * CTerrain::Clone()
{
	return new CTerrain(*this);
}

void CTerrain::Free()
{
	CVIBuffer::Free();
}
