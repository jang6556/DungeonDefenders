//#include "stdafx.h"
//#include "..\Header\Camera.h"
//#include "../Header/Define.h"
//
//_USING(Client)
//
//CCamera::CCamera(LPDIRECT3DDEVICE9 _m_pGraphicDev)
//	:CGameObject(_m_pGraphicDev)
//{
//}
//
//CCamera::CCamera(const CCamera & rhs)
//	: CGameObject(rhs.m_pGraphicDev)
//{
//
//}
//
//HRESULT CCamera::Initialize()
//{
//	return NOERROR;
//}
//
//_int CCamera::Progress(const _float & fTimeDelta)
//{
//	D3DXVECTOR3 Position(0.f, 0.f, -5.f);
//	D3DXVECTOR3 Target(0.f, 0.f, 0.f);
//	D3DXVECTOR3 Up(0.f, 1.f, 0.f);
//	D3DXMATRIX V;
//
//	if (GetAsyncKeyState(VK_UP))
//	{
//		fAngleX += 0.01f;
//	}
//
//	if (GetAsyncKeyState(VK_DOWN))
//	{
//		fAngleX -= 0.01f;
//	}
//
//	if (GetAsyncKeyState(VK_RIGHT))
//	{
//		fAngleY += 0.01f;
//	}
//
//	if (GetAsyncKeyState(VK_LEFT))
//	{
//		fAngleY -= 0.01f;
//	}
//
//
//	D3DXMATRIX CameraAngleX, CameraAngleY;
//
//	D3DXMatrixRotationX(&CameraAngleX, fAngleX);
//	D3DXMatrixRotationY(&CameraAngleY, fAngleY);
//
//	D3DXMATRIX matAngle = CameraAngleX* CameraAngleY;
//
//	D3DXVec3TransformCoord(&Position, &Position, &matAngle);
//
//	D3DXMatrixLookAtLH(&V, &Position, &Target, &Up);
//	m_pGraphicDev->SetTransform(D3DTS_VIEW, &V);
//
//	D3DXMATRIX proj;
//	D3DXMatrixPerspectiveFovLH(
//		&proj,
//		D3DX_PI*0.5f,
//		float(iWINCX) / float(iWINCY),
//		1.0f,
//		10000.f
//	);
//
//	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &proj);
//	return 0;
//}
//
//CCamera * CCamera::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
//{
//	CCamera* pInstance = new CCamera(_m_pGraphicDev);
//
//	if (FAILED(pInstance->Initialize()))
//	{
//		_MSGBOX("CCamera Created Failed");
//		Safe_Release(pInstance);
//	}
//	return pInstance;
//}
//
//CGameObject * CCamera::Clone()
//{
//	return new CCamera(*this);
//}
//
//void CCamera::Free()
//{
//	CGameObject::Free();
//}
