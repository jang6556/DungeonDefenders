#include "..\Header\Cube.h"




CCube::CCube(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CVIBuffer(_m_pGraphicDev)
{
}

CCube::CCube(const CCube & rhs)
	:CVIBuffer(rhs)
{

}

HRESULT CCube::Initialize()
{
	iVertexSize = 8;
	iIndexSize = 36;
	m_pGraphicDev->CreateVertexBuffer(sizeof(VertexCubeUV) * iVertexSize, D3DUSAGE_WRITEONLY, D3DFVF_XYZ | D3DFVF_TEX1 |  D3DFVF_TEXCOORDSIZE3(0), D3DPOOL_MANAGED, &VB, 0);
	m_pGraphicDev->CreateIndexBuffer(sizeof(DWORD) * iIndexSize, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &IB, 0);

	VertexCubeUV* pVertex = nullptr;
	VB->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].vPosition = D3DXVECTOR3(-0.5f, 0.5f, -0.5f);
	D3DXVec3Normalize(&pVertex[0].UV, &pVertex[0].vPosition);
	
	pVertex[1].vPosition = D3DXVECTOR3(0.5f, 0.5f, -0.5f);
	D3DXVec3Normalize(&pVertex[1].UV, &pVertex[1].vPosition);

	pVertex[2].vPosition = D3DXVECTOR3(0.5f, -0.5f, -0.5f);
	D3DXVec3Normalize(&pVertex[2].UV, &pVertex[2].vPosition);

	pVertex[3].vPosition = D3DXVECTOR3(-0.5f, -0.5f, -0.5f);
	D3DXVec3Normalize(&pVertex[3].UV, &pVertex[3].vPosition);

	pVertex[4].vPosition = D3DXVECTOR3(-0.5f, 0.5f, 0.5f);
	D3DXVec3Normalize(&pVertex[4].UV, &pVertex[4].vPosition);

	pVertex[5].vPosition = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
	D3DXVec3Normalize(&pVertex[5].UV, &pVertex[5].vPosition);

	pVertex[6].vPosition = D3DXVECTOR3(0.5f, -0.5f, 0.5f);
	D3DXVec3Normalize(&pVertex[6].UV, &pVertex[6].vPosition);

	pVertex[7].vPosition = D3DXVECTOR3(-0.5f, -0.5f, 0.5f);
	D3DXVec3Normalize(&pVertex[7].UV, &pVertex[7].vPosition);

	
	VB->Unlock();

	_uint iIndex=0;

	WORD* Indices = nullptr;

	IB->Lock(0, 0, (void**)&Indices, 0);

	//전면
	Indices[0] = 0; Indices[1] = 1; Indices[2] = 2;
	Indices[3] = 0; Indices[4] = 2; Indices[5] = 3;

	//후면
	Indices[6] = 5; Indices[7] = 4; Indices[8] = 7;
	Indices[9] = 5; Indices[10] = 7; Indices[11] = 6;

	//위면
	Indices[12] = 4; Indices[13] = 5; Indices[14] = 1;
	Indices[15] = 4; Indices[16] = 1; Indices[17] = 0;

	//아랫면
	Indices[18] = 3; Indices[19] = 2; Indices[20] = 6;
	Indices[21] = 3; Indices[22] = 6; Indices[23] = 7;

	//오른쪽면
	Indices[24] = 1; Indices[25] = 5; Indices[26] = 6;
	Indices[27] = 1; Indices[28] = 6; Indices[29] = 2;

	//왼쪽면
	Indices[30] = 4; Indices[31] = 0; Indices[32] = 3;
	Indices[33] = 4; Indices[34] = 3; Indices[35] = 7;

	

	IB->Unlock();


	

	return NOERROR;	
}

_int CCube::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CCube::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CCube::Render(CTransform* pTransform)
{
	if (pTransform != nullptr)
	{
		/*D3DXMATRIX Wolrd = *pTransform->GetWorldMatrix();*/
		VertexCubeUV* pVertex = nullptr;
		VB->Lock(0, 0, (void**)&pVertex, 0);

		pVertex[0].vPosition = D3DXVECTOR3(-0.5f, 0.5f, -0.5f);
		D3DXVec3Normalize(&pVertex[0].UV, &pVertex[0].vPosition);
		pVertex[0].vPosition += pTransform->GetPosition();
	//	D3DXVec3TransformCoord(&pVertex[0].vPosition, &pVertex[0].vPosition, &Wolrd);
		

		pVertex[1].vPosition = D3DXVECTOR3(0.5f, 0.5f, -0.5f);
		D3DXVec3Normalize(&pVertex[1].UV, &pVertex[1].vPosition);
		pVertex[1].vPosition += pTransform->GetPosition();
	//	D3DXVec3TransformCoord(&pVertex[1].vPosition, &pVertex[1].vPosition, &Wolrd);
		

		pVertex[2].vPosition = D3DXVECTOR3(0.5f, -0.5f, -0.5f);
		D3DXVec3Normalize(&pVertex[2].UV, &pVertex[2].vPosition);
		pVertex[2].vPosition += pTransform->GetPosition();
	//	D3DXVec3TransformCoord(&pVertex[2].vPosition, &pVertex[2].vPosition, &Wolrd);
		

		pVertex[3].vPosition = D3DXVECTOR3(-0.5f, -0.5f, -0.5f);
		D3DXVec3Normalize(&pVertex[3].UV, &pVertex[3].vPosition);
		pVertex[3].vPosition += pTransform->GetPosition();
	//	D3DXVec3TransformCoord(&pVertex[3].vPosition, &pVertex[3].vPosition, &Wolrd);
	
		pVertex[4].vPosition = D3DXVECTOR3(-0.5f, 0.5f, 0.5f);
		D3DXVec3Normalize(&pVertex[4].UV, &pVertex[4].vPosition);
		pVertex[4].vPosition += pTransform->GetPosition();
	//	D3DXVec3TransformCoord(&pVertex[4].vPosition, &pVertex[4].vPosition, &Wolrd);
	

		pVertex[5].vPosition = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
		D3DXVec3Normalize(&pVertex[5].UV, &pVertex[5].vPosition);
		pVertex[5].vPosition += pTransform->GetPosition();
	//	D3DXVec3TransformCoord(&pVertex[5].vPosition, &pVertex[5].vPosition, &Wolrd);
		

		pVertex[6].vPosition = D3DXVECTOR3(0.5f, -0.5f, 0.5f);
		D3DXVec3Normalize(&pVertex[6].UV, &pVertex[6].vPosition);
		pVertex[6].vPosition += pTransform->GetPosition();
	//	D3DXVec3TransformCoord(&pVertex[6].vPosition, &pVertex[6].vPosition, &Wolrd);
		

		pVertex[7].vPosition = D3DXVECTOR3(-0.5f, -0.5f, 0.5f);
		D3DXVec3Normalize(&pVertex[7].UV, &pVertex[7].vPosition);
		pVertex[7].vPosition += pTransform->GetPosition();
	//	D3DXVec3TransformCoord(&pVertex[7].vPosition, &pVertex[7].vPosition, &Wolrd);
		




		VB->Unlock();
	}
	m_pGraphicDev->SetStreamSource(0, VB, 0, sizeof(VertexCubeUV));
	m_pGraphicDev->SetIndices(IB);
	m_pGraphicDev->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0));

	m_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, iVertexSize, 0, 12);

	return NOERROR;
}

CCube * CCube::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CCube*	pInstance = new CCube(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CCube Created Failed");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CCube::Clone()
{
	return new CCube(*this);
}

void CCube::Free()
{
	CVIBuffer::Free();
}
