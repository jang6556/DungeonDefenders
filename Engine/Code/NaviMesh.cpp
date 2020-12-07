#include "..\Header\NaviMesh.h"
#include "Cell.h"
#include "MonSphere.h"


HRESULT CNaviMesh::Initialize(const TCHAR*	szFileName, const TCHAR* szMonFileName)
{


	HANDLE	hFile = CreateFile(szFileName,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	DWORD		dwByte;

	while (1)
	{
		D3DXVECTOR3 SavePointA;
		ReadFile(hFile, &SavePointA, sizeof(D3DXVECTOR3), &dwByte, NULL);
		if (dwByte == 0)
			break;

		D3DXVECTOR3 SavePointB;
		ReadFile(hFile, &SavePointB, sizeof(D3DXVECTOR3), &dwByte, NULL);
		if (dwByte == 0)
			break;

		D3DXVECTOR3 SavePointC;
		ReadFile(hFile, &SavePointC, sizeof(D3DXVECTOR3), &dwByte, NULL);
		if (dwByte == 0)
			break;


		CCell* pInstance = CCell::Create(m_pGraphicDev, SavePointA, SavePointB, SavePointC, m_pCell_Vector.size());
		
		m_pCell_Vector.push_back(pInstance);

	}
	CloseHandle(hFile);


	HANDLE	Mon_hFile = CreateFile(szMonFileName,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	dwByte;

	while (1)
	{	

		D3DXVECTOR3 vPosition;
		ReadFile(Mon_hFile, &vPosition, sizeof(D3DXVECTOR3), &dwByte, NULL);
		if (dwByte == 0)
			break;
		
		CMonSphere* pInstance = CMonSphere::Create(m_pGraphicDev, vPosition);

		m_MonNavi_Vector.push_back(pInstance);

	}
	CloseHandle(Mon_hFile);




	_uint	iSize = m_pCell_Vector.size();

	for (int i = 0; i < iSize; ++i)
	{
		for (int j = 0; j < iSize; ++j)
		{
			if (m_pCell_Vector[i] == m_pCell_Vector[j])
				continue;

			if (m_pCell_Vector[i]->IsNeighbor(&m_pCell_Vector[i]->GetPoint(CCell::POINT_A),
				&m_pCell_Vector[i]->GetPoint(CCell::POINT_B),
				m_pCell_Vector[j]) == true)
			{
				m_pCell_Vector[i]->SetNeighbor(CCell::NEIGHBOR_AB, m_pCell_Vector[j]);
				continue;
			}

			if (m_pCell_Vector[i]->IsNeighbor(&m_pCell_Vector[i]->GetPoint(CCell::POINT_B),
				&m_pCell_Vector[i]->GetPoint(CCell::POINT_C),
				m_pCell_Vector[j]) == true)
			{
				m_pCell_Vector[i]->SetNeighbor(CCell::NEIGHBOR_BC, m_pCell_Vector[j]);
				continue;
			}

			if (m_pCell_Vector[i]->IsNeighbor(&m_pCell_Vector[i]->GetPoint(CCell::POINT_C),
				&m_pCell_Vector[i]->GetPoint(CCell::POINT_A),
				m_pCell_Vector[j]) == true)
			{
				m_pCell_Vector[i]->SetNeighbor(CCell::NEIGHBOR_CA, m_pCell_Vector[j]);
				continue;
			}
		}
	}



	return NOERROR;
}

CNaviMesh::CNaviMesh(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CComponent(_m_pGraphicDev)
{
}

CNaviMesh::CNaviMesh(const CNaviMesh & rhs)
	:CComponent(rhs), m_pCell_Vector(rhs.m_pCell_Vector), m_MonNavi_Vector(rhs.m_MonNavi_Vector)
{
}

HRESULT CNaviMesh::Render()
{
	for (auto& iter : m_pCell_Vector)
		iter->Render();

	for (auto& iter : m_MonNavi_Vector)
		iter->Render();

	return NOERROR;
}

void CNaviMesh::SetIndex(D3DXVECTOR3 _vPosition)
{
	_uint iSize = m_pCell_Vector.size();

	for (int i = 0; i < iSize; ++i)
	{
		_uint iEdge;
		if (m_pCell_Vector[i]->IsIn(_vPosition, &iEdge))
		{
			m_iCurrnet_Index = i;
			return;
		}
	}
}

bool CNaviMesh::MoveNavigation(D3DXVECTOR3 _vPosition, D3DXVECTOR3 _vDir, float fSpeed, const float & fTimeDelta)
{
	D3DXVECTOR3 vNormalize = _vDir;
	D3DXVec3Normalize(&vNormalize, &vNormalize);

	D3DXVECTOR3 vComputePosition = _vPosition + vNormalize*fSpeed*fTimeDelta;
	vComputePosition.y = 0;
	_uint iEdge = 0;

	bool bIsIn = m_pCell_Vector[m_iCurrnet_Index]->IsIn(vComputePosition, &iEdge);
	CCell* pNeighbor = m_pCell_Vector[m_iCurrnet_Index]->GetNeighbor((CCell::NEIGHBOR)iEdge);

	if (bIsIn == true)
	{
		return true;
	}
	else
	{		
		if (pNeighbor != nullptr)
		{
			m_iCurrnet_Index = pNeighbor->GetIndex();
			
			return true;
		}
		else
			return false;
	}
	
	return bool();
}

float CNaviMesh::ComputeHeight(D3DXVECTOR3 _vPosition)
{
	D3DXVECTOR3 vNaviPosition[3];
	vNaviPosition[0]= m_pCell_Vector[m_iCurrnet_Index]->GetPoint(CCell::POINT_A);
	vNaviPosition[1] = m_pCell_Vector[m_iCurrnet_Index]->GetPoint(CCell::POINT_B);
	vNaviPosition[2] = m_pCell_Vector[m_iCurrnet_Index]->GetPoint(CCell::POINT_C);

	D3DXVECTOR3 vPosition = _vPosition;
	vPosition.y = 0;
	
	float fU, fV, fDist;

	if (D3DXIntersectTri(&vNaviPosition[0], &vNaviPosition[1], &vNaviPosition[2], &vPosition, &D3DXVECTOR3(0,-1,0), &fU, &fV, &fDist) == TRUE)
	{
		return -fDist;
	}

	return _vPosition.y;
}

float CNaviMesh::GetHeight(D3DXVECTOR3 _vPosition)
{
	_uint	iIndex = 0;
	_uint iSize = m_pCell_Vector.size();

	for (int i = 0; i < iSize; ++i)
	{
		_uint iEdge;
		if (m_pCell_Vector[i]->IsIn(_vPosition, &iEdge))
		{
			iIndex = i;

			D3DXVECTOR3 vNaviPosition[3];
			vNaviPosition[0] = m_pCell_Vector[iIndex]->GetPoint(CCell::POINT_A);
			vNaviPosition[1] = m_pCell_Vector[iIndex]->GetPoint(CCell::POINT_B);
			vNaviPosition[2] = m_pCell_Vector[iIndex]->GetPoint(CCell::POINT_C);

			D3DXVECTOR3 vPosition = _vPosition;
			vPosition.y = 0;

			float fU, fV, fDist;

			if (D3DXIntersectTri(&vNaviPosition[0], &vNaviPosition[1], &vNaviPosition[2], &vPosition, &D3DXVECTOR3(0, -1, 0), &fU, &fV, &fDist) == TRUE)
			{
				return -fDist;
			}

			
		}
	}

	return _vPosition.y;
}

bool CNaviMesh::NaviMeshPicking(POINT ptMouse,D3DXVECTOR3 * pOut)
{
	D3DVIEWPORT9		ViewPort;
	ZeroMemory(&ViewPort, sizeof(D3DVIEWPORT9));

	m_pGraphicDev->GetViewport(&ViewPort);

	D3DXVECTOR3		vMouse;

	vMouse.x = ptMouse.x / (ViewPort.Width * 0.5f) - 1.f;
	vMouse.y = ptMouse.y / (ViewPort.Height * -0.5f) + 1.f;
	vMouse.z = 0.f;


	D3DXMATRIX			matProj;
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMatrixInverse(&matProj, nullptr, &matProj);

	D3DXVec3TransformCoord(&vMouse, &vMouse, &matProj);

	D3DXVECTOR3			vRay, vPivot;

	vPivot = D3DXVECTOR3(0.f, 0.f, 0.f);
	vRay = vMouse - vPivot;

	D3DXMATRIX			matView;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, nullptr, &matView);

	D3DXVec3TransformCoord(&vPivot, &vPivot, &matView);
	D3DXVec3TransformNormal(&vRay, &vRay, &matView);


	D3DXVec3Normalize(&vRay, &vRay);


	_float		fU, fV, fDist;
	
	map<float, D3DXVECTOR3>	mapPoint;

	for (auto& iter : m_pCell_Vector)
	{
		D3DXVECTOR3 vPoint[3];

		vPoint[0] = iter->GetPoint(CCell::POINT_A);
		vPoint[1] = iter->GetPoint(CCell::POINT_B);
		vPoint[2] = iter->GetPoint(CCell::POINT_C);

		if (TRUE == D3DXIntersectTri(&vPoint[0], &vPoint[1], &vPoint[2], &vPivot, &vRay, &fU, &fV, &fDist))
		{
			D3DXVECTOR3 vPosition;

			vPosition = *D3DXVec3Normalize(&vRay, &vRay) * fDist + vPivot;			
			mapPoint.emplace(D3DXVec3Length(&(vPosition - vPivot)), vPosition);
		}
	}

	if (mapPoint.size() == 0)
		return false;
	else
	{
		*pOut = mapPoint.begin()->second;

		return true;
	}
}

D3DXVECTOR3 CNaviMesh::GetPosition(int _iIndex)
{
	return m_MonNavi_Vector[_iIndex]->GetPosition();
}

CNaviMesh * CNaviMesh::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev, const TCHAR* szFileName, const TCHAR* szMonFileName)
{
	CNaviMesh*	pInstance = new CNaviMesh(_m_pGraphicDev);
	if (FAILED(pInstance->Initialize(szFileName, szMonFileName)))
	{
		_MSGBOX("CNaviMesh Created Failed");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CNaviMesh::Clone()
{
	return new CNaviMesh(*this);
}

void CNaviMesh::Free()
{
	if (m_IsClone == false)
	{
		for (auto& iter : m_pCell_Vector)
			Safe_Release(iter);

		m_pCell_Vector.clear();

		for (auto& iter : m_MonNavi_Vector)
			Safe_Release(iter);

		m_MonNavi_Vector.clear();
	}
	CComponent::Free();
}
