#include "..\Header\RectUI.h"




HRESULT CRectUI::Initialize()
{
	iVertexNum = 4;
	iIndexNum = 20;
	iPolygonsize = 2;
	iVertexSize = sizeof(VertexUV);
	iIndexSize = sizeof(WORD);
	D3DFormat = D3DFMT_INDEX16;
	dwFVF = D3DFVF_XYZ | D3DFVF_TEX1;


	if (FAILED(CVIBuffer::CreateBuffer()))
		return E_FAIL;

	VertexUV* pVertices = nullptr;

	VB->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].vPosition = D3DXVECTOR3(-0.5f, -0.5f, 0.f);
	pVertices[0].vTexUV = D3DXVECTOR2(0.f, 1.f);

	pVertices[1].vPosition = D3DXVECTOR3(-0.5f, 0.5f, 0.f);
	pVertices[1].vTexUV = D3DXVECTOR2(0.f, 0.f);

	pVertices[2].vPosition = D3DXVECTOR3(0.5f, 0.5f, 0.f);
	pVertices[2].vTexUV = D3DXVECTOR2(1.f, 0.f);

	pVertices[3].vPosition = D3DXVECTOR3(0.5f, -0.5f, 0.f);
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

CRectUI::CRectUI(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CVIBuffer(_m_pGraphicDev)
{

}

CRectUI::CRectUI(CRectUI & rhs)
	:CVIBuffer(rhs)
{

}

HRESULT CRectUI::Render()
{
	if (FAILED(CVIBuffer::Render()))
		return E_FAIL;

	return NOERROR;
}

_int CRectUI::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CRectUI::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

CRectUI * CRectUI::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CRectUI*	pInstance = new CRectUI(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CRectUI Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent * CRectUI::Clone()
{
	return new CRectUI(*this);
}

void CRectUI::Free()
{
	CVIBuffer::Free();
}
