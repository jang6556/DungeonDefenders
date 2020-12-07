#include "..\Header\Cell.h"




HRESULT CCell::Initialize(D3DXVECTOR3 _PointA, D3DXVECTOR3 _PointB, D3DXVECTOR3 _PointC, _uint _iIndex)
{
	m_vPoint[POINT_A] = _PointA;
	m_vPoint[POINT_B] = _PointB;
	m_vPoint[POINT_C] = _PointC;

	m_vEdge[EDGE_AB] = m_vPoint[POINT_B] - m_vPoint[POINT_A];
	m_vEdge[EDGE_BC] = m_vPoint[POINT_C] - m_vPoint[POINT_B];
	m_vEdge[EDGE_CA] = m_vPoint[POINT_A] - m_vPoint[POINT_C];

	m_pNeightbor[NEIGHBOR_AB] = nullptr;
	m_pNeightbor[NEIGHBOR_BC] = nullptr;
	m_pNeightbor[NEIGHBOR_CA] = nullptr;

	m_iIndex = _iIndex;

	D3DXCreateLine(m_pGraphicDevice, &m_pLine);

	return NOERROR;
}

CCell::CCell(LPDIRECT3DDEVICE9 _m_pGraphicDevice)
	:m_pGraphicDevice(_m_pGraphicDevice)
{
	m_pGraphicDevice->AddRef();
}



bool CCell::IsNeighbor(const D3DXVECTOR3 * pFirst, const D3DXVECTOR3 * pSecond, CCell * pCell)
{
	if (*pFirst == pCell->m_vPoint[POINT_A])
	{
		if (*pSecond == pCell->m_vPoint[POINT_B])
		{
			return true;
		}
		if (*pSecond == pCell->m_vPoint[POINT_C])
		{
			return true;
		}
	}

	if (*pFirst == pCell->m_vPoint[POINT_B])
	{
		if (*pSecond == pCell->m_vPoint[POINT_A])
		{
			return true;
		}
		if (*pSecond == pCell->m_vPoint[POINT_C])
		{
			return true;
		}
	}

	if (*pFirst == pCell->m_vPoint[POINT_C])
	{
		if (*pSecond == pCell->m_vPoint[POINT_A])
		{
			return true;
		}
		if (*pSecond == pCell->m_vPoint[POINT_B])
		{
			return true;
		}
	}




	return false;
}

bool CCell::IsIn(D3DXVECTOR3 _vPosition, _uint * iOutputEdge)
{
	for (int i = 0; i < EDGE_END; ++i)
	{
		D3DXVECTOR3 vDir = m_vEdge[i];
		D3DXMATRIX matRoatate;
		D3DXMatrixRotationY(&matRoatate, D3DXToRadian(-90));
	
		vDir.y = 0;
		D3DXVec3TransformNormal(&vDir, &vDir, &matRoatate);

		D3DXVECTOR3 vCompute = _vPosition - m_vPoint[i];

		D3DXVec3Normalize(&vDir, &vDir);
		D3DXVec3Normalize(&vCompute, &vCompute);

		if (D3DXVec3Dot(&vDir, &vCompute) > 0.f)
		{
			*iOutputEdge = i;
			return false;
		}
	}

	return true;
}

HRESULT CCell::Render()
{
	D3DXVECTOR3 vPoint[4];

	vPoint[0] = m_vPoint[POINT_A];
	vPoint[1] = m_vPoint[POINT_B];
	vPoint[2] = m_vPoint[POINT_C];
	vPoint[3] = m_vPoint[POINT_A];

	D3DXMATRIX matView, matProj;

	m_pGraphicDevice->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDevice->GetTransform(D3DTS_PROJECTION, &matProj);

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&vPoint[i], &vPoint[i], &matView);

		if (vPoint[i].z <= 0)
			vPoint[i].z = 0;

		D3DXVec3TransformCoord(&vPoint[i], &vPoint[i], &matProj);
	}
	m_pLine->SetWidth(2.f);
	D3DXMATRIX matIdentity;
	D3DXMatrixIdentity(&matIdentity);

	m_pLine->DrawTransform(vPoint, 4, &matIdentity, D3DXCOLOR(1.f, 0.f, 0.f, 1.f));
	
	return NOERROR;
}

void CCell::Free()
{
	Safe_Release(m_pLine);
	Safe_Release(m_pGraphicDevice);
}

CCell * CCell::Create(LPDIRECT3DDEVICE9 _m_pGraphicDevice, D3DXVECTOR3 _PointA, D3DXVECTOR3 _PointB, D3DXVECTOR3 _PointC, _uint _iIndex)
{
	CCell* pInstance = new CCell(_m_pGraphicDevice);

	if (FAILED(pInstance->Initialize(_PointA, _PointB, _PointC, _iIndex)))
	{
		_MSGBOX("CCell Created Failed");
		Safe_Release(pInstance);
	}

	return pInstance;
}
