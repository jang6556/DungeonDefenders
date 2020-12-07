#include "..\Header\Frustum.h"
#include "Transform.h"



HRESULT CFrustum::Initialize()
{
	m_vPoint[0] = D3DXVECTOR3(-1.f,-1.f, 0);
	m_vPoint[1] = D3DXVECTOR3(-1.f, 1.f, 0);
	m_vPoint[2] = D3DXVECTOR3( 1.f, 1.f, 0);
	m_vPoint[3] = D3DXVECTOR3( 1.f,-1.f, 0);
			   
	m_vPoint[4] = D3DXVECTOR3(-1.f, -1.f, 1);
	m_vPoint[5] = D3DXVECTOR3(-1.f,  1.f, 1);
	m_vPoint[6] = D3DXVECTOR3( 1.f,  1.f, 1);
	m_vPoint[7] = D3DXVECTOR3( 1.f, -1.f, 1);

	return NOERROR;
}

HRESULT CFrustum::TransformLocal(D3DXMATRIX _matWorldInv, D3DXVECTOR3 * _PointArray)
{
	if (m_pGraphicDev == nullptr)
		return E_FAIL;

	D3DXMATRIX matViewInv, matProjInv;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matViewInv);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProjInv);

	D3DXMatrixInverse(&matViewInv, nullptr, &matViewInv);
	D3DXMatrixInverse(&matProjInv, nullptr, &matProjInv);

	for (size_t i = 0; i < 8; ++i)
		D3DXVec3TransformCoord(&_PointArray[i], &m_vPoint[i], &matProjInv);

	for (size_t i = 0; i < 8; ++i)
		D3DXVec3TransformCoord(&_PointArray[i], &_PointArray[i], &matViewInv);

	for (size_t i = 0; i < 8; ++i)
		D3DXVec3TransformCoord(&_PointArray[i], &_PointArray[i], &_matWorldInv);

	return NOERROR;
}

HRESULT CFrustum::MakePlane(D3DXVECTOR3 * _PointArray, D3DXPLANE * _pPlane)
{
	D3DXPlaneFromPoints(&_pPlane[0], &_PointArray[0], &_PointArray[1], &_PointArray[2]);
	D3DXPlaneFromPoints(&_pPlane[1], &_PointArray[3], &_PointArray[2], &_PointArray[6]);
	D3DXPlaneFromPoints(&_pPlane[2], &_PointArray[1], &_PointArray[5], &_PointArray[2]);
	D3DXPlaneFromPoints(&_pPlane[3], &_PointArray[0], &_PointArray[3], &_PointArray[7]);
	D3DXPlaneFromPoints(&_pPlane[4], &_PointArray[5], &_PointArray[1], &_PointArray[0]);
	D3DXPlaneFromPoints(&_pPlane[5], &_PointArray[5], &_PointArray[6], &_PointArray[2]);
	
	return NOERROR;
}

CFrustum::CFrustum(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CComponent(_m_pGraphicDev)
{
}

CFrustum::CFrustum(const CFrustum & rhs)
	: CComponent(rhs)
{
	memcpy(m_vPoint, rhs.m_vPoint, sizeof(D3DXVECTOR3) * 8);
}

bool CFrustum::IsInFrustum(D3DXVECTOR3 _vPosition, CTransform * _pTransform, float _fRadius)
{
	D3DXVECTOR3 vPoint[8];
	D3DXVECTOR3 vLocalPosition;
	
	D3DXMATRIX matWorldInv = *_pTransform->GetWorldMatrix();

	D3DXVec3Normalize((D3DXVECTOR3*)&matWorldInv.m[0][0], (D3DXVECTOR3*)&matWorldInv.m[0][0]);
	D3DXVec3Normalize((D3DXVECTOR3*)&matWorldInv.m[1][0], (D3DXVECTOR3*)&matWorldInv.m[1][0]);
	D3DXVec3Normalize((D3DXVECTOR3*)&matWorldInv.m[2][0], (D3DXVECTOR3*)&matWorldInv.m[2][0]);

	D3DXMatrixInverse(&matWorldInv, nullptr, &matWorldInv);
	D3DXVec3TransformCoord(&vLocalPosition, &_vPosition, &matWorldInv);


	if (FAILED(TransformLocal(matWorldInv, vPoint)))
		return false;	

	D3DXPLANE Plane[6];

	if (FAILED(MakePlane(vPoint, Plane)))
		return false;

	for (size_t i = 0; i < 6; ++i)
	{
		float fDistance = D3DXPlaneDotCoord(&Plane[i], &vLocalPosition);

		if (fDistance > _fRadius)
			return false;
	}

	return true;
}

bool CFrustum::IsInFrustumLight(D3DXVECTOR3 _vPosition, float _fRadius)
{
	D3DXVECTOR3 vPoint[8];
	D3DXVECTOR3 vLocalPosition;

	D3DXMATRIX matWorldInv;
	D3DXMatrixIdentity(&matWorldInv);
	
	memcpy(&matWorldInv.m[3][0], &_vPosition, sizeof(D3DXVECTOR3));

	D3DXMatrixInverse(&matWorldInv, nullptr, &matWorldInv);
	D3DXVec3TransformCoord(&vLocalPosition, &_vPosition, &matWorldInv);

	if (FAILED(TransformLocal(matWorldInv, vPoint)))
		return false;

	D3DXPLANE Plane[6];

	if (FAILED(MakePlane(vPoint, Plane)))
		return false;

	for (size_t i = 0; i < 6; ++i)
	{
		float fDistance = D3DXPlaneDotCoord(&Plane[i], &vLocalPosition);

		if (fDistance > _fRadius)
			return false;
	}

	return true;
}

CFrustum * CFrustum::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CFrustum* pInstance = new CFrustum(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CFrustum Created Failed");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CFrustum::Clone()
{
	return new CFrustum(*this);
}

void CFrustum::Free()
{
	CComponent::Free();
}
