#include "..\Header\ScreenTex_Buffer.h"





HRESULT CScreenTex_Buffer::Initialize()
{
	iVertexNum = 4;
	iIndexNum = 20;
	iPolygonsize = 2;
	iVertexSize = sizeof(VertexScreenTex);
	iIndexSize = sizeof(WORD);
	D3DFormat = D3DFMT_INDEX16;
	dwFVF = D3DFVF_XYZRHW | D3DFVF_TEX1;


	if (FAILED(CVIBuffer::CreateBuffer()))
		return E_FAIL;

	VertexScreenTex* pVertices = nullptr;

	VB->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].vPosition = D3DXVECTOR4(-0.5f, -0.5f, 0.f, 1.f);
	pVertices[0].vTexUV = D3DXVECTOR2(0.f, 1.f);

	pVertices[1].vPosition = D3DXVECTOR4(-0.5f, 0.5f, 0.f, 1.f);
	pVertices[1].vTexUV = D3DXVECTOR2(0.f, 0.f);

	pVertices[2].vPosition = D3DXVECTOR4(0.5f, 0.5f, 0.f, 1.f);
	pVertices[2].vTexUV = D3DXVECTOR2(1.f, 0.f);

	pVertices[3].vPosition = D3DXVECTOR4(0.5f, -0.5f, 0.f, 1.f);
	pVertices[3].vTexUV = D3DXVECTOR2(1.f, 1.f);

	VB->Unlock();

	WORD* pIndices = nullptr;

	IB->Lock(0, 0, (void**)&pIndices, 0);

	pIndices[0] = 0;
	pIndices[1] = 1;
	pIndices[2] = 2;

	pIndices[3] = 0;
	pIndices[4] = 2;
	pIndices[5] = 3;

	IB->Unlock();

	return NOERROR;
}

HRESULT CScreenTex_Buffer::Initialize(_float _fStartX, _float _fStartY, _float _fSizeX, _float _fSizeY)
{
	iVertexNum = 4;
	iIndexNum = 20;
	iPolygonsize = 2;
	iVertexSize = sizeof(VertexScreenTex);
	iIndexSize = sizeof(WORD);
	D3DFormat = D3DFMT_INDEX16;
	dwFVF = D3DFVF_XYZRHW | D3DFVF_TEX1;


	if (FAILED(CVIBuffer::CreateBuffer()))
		return E_FAIL;

	VertexScreenTex* pVertices = nullptr;

	VB->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].vPosition = D3DXVECTOR4(_fStartX, _fStartY + _fSizeY, 0.f, 1.f);
	pVertices[0].vTexUV = D3DXVECTOR2(0.f, 1.f);

	pVertices[1].vPosition = D3DXVECTOR4(_fStartX, _fStartY, 0.f, 1.f);
	pVertices[1].vTexUV = D3DXVECTOR2(0.f, 0.f);

	pVertices[2].vPosition = D3DXVECTOR4(_fStartX + _fSizeX, _fStartY, 0.f, 1.f);
	pVertices[2].vTexUV = D3DXVECTOR2(1.f, 0.f);

	pVertices[3].vPosition = D3DXVECTOR4(_fStartX + _fSizeX, _fStartY + _fSizeY, 0.f, 1.f);
	pVertices[3].vTexUV = D3DXVECTOR2(1.f, 1.f);

	VB->Unlock();

	WORD* pIndices = nullptr;

	IB->Lock(0, 0, (void**)&pIndices, 0);

	pIndices[0] = 0;
	pIndices[1] = 1;
	pIndices[2] = 2;

	pIndices[3] = 0;
	pIndices[4] = 2;
	pIndices[5] = 3;

	IB->Unlock();

	return NOERROR;
}

CScreenTex_Buffer::CScreenTex_Buffer(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CVIBuffer(_m_pGraphicDev)
{
}

CScreenTex_Buffer::CScreenTex_Buffer(CScreenTex_Buffer & rhs)
	: CVIBuffer(rhs)
{
}

HRESULT CScreenTex_Buffer::Render()
{
	if (FAILED(CVIBuffer::Render()))
		return E_FAIL;

	return NOERROR;
}

_int CScreenTex_Buffer::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CScreenTex_Buffer::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

CScreenTex_Buffer * CScreenTex_Buffer::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CScreenTex_Buffer*	pInstance = new CScreenTex_Buffer(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CScreenTex_Buffer Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CScreenTex_Buffer * CScreenTex_Buffer::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev, _float _fStartX, _float _fStartY, _float _fSizeX, _float _fSizeY)
{
	CScreenTex_Buffer*	pInstance = new CScreenTex_Buffer(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize(_fStartX, _fStartY, _fSizeX, _fSizeY)))
	{
		_MSGBOX("CScreenTex_Buffer Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent * CScreenTex_Buffer::Clone()
{
	return new CScreenTex_Buffer(*this);
}

void CScreenTex_Buffer::Free()
{
	CVIBuffer::Free();
}
