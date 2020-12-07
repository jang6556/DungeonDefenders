#include "..\Header\Transform.h"



CTransform::CTransform(LPDIRECT3DDEVICE9	_m_pGraphicDev)
	:CComponent(_m_pGraphicDev)
{

}

CTransform::CTransform(const CTransform & rhs)
	: CComponent(rhs.m_pGraphicDev)
	, matWorld(rhs.matWorld)

{

}

HRESULT CTransform::Initialize()
{
	D3DXMatrixIdentity(&matWorld);

	return NOERROR;
}

HRESULT CTransform::Scaling(const float & fX, const float & fY, const float & fZ)
{
	D3DXVECTOR3 vRight, vLook, vUp;
	memcpy(&vRight, &matWorld.m[0][0], sizeof(D3DXVECTOR3));
	memcpy(&vUp, &matWorld.m[1][0], sizeof(D3DXVECTOR3));
	memcpy(&vLook, &matWorld.m[2][0], sizeof(D3DXVECTOR3));

	D3DXVec3Normalize(&vRight, &vRight);
	D3DXVec3Normalize(&vLook, &vLook);
	D3DXVec3Normalize(&vUp, &vUp);

	vRight *= fX;
	vLook *= fZ;
	vUp *= fY;

	memcpy(&matWorld.m[0][0], &vRight, sizeof(D3DXVECTOR3));
	memcpy(&matWorld.m[1][0], &vUp, sizeof(D3DXVECTOR3));
	memcpy(&matWorld.m[2][0], &vLook, sizeof(D3DXVECTOR3));

	return NOERROR;
}

HRESULT CTransform::Scaling(const float & fX, const float & fY, const float & fZ, const _float & fTimeDelta)
{
	D3DXVECTOR3 vRight, vLook, vUp;
	memcpy(&vRight, &matWorld.m[0][0], sizeof(D3DXVECTOR3));
	memcpy(&vUp, &matWorld.m[1][0], sizeof(D3DXVECTOR3));
	memcpy(&vLook, &matWorld.m[2][0], sizeof(D3DXVECTOR3));

	float fX_Scale = 0.f, fY_Scale = 0.f, fZ_Scale = 0.f;

	fX_Scale = D3DXVec3Length(&vRight);
	fY_Scale = D3DXVec3Length(&vUp);
	fZ_Scale = D3DXVec3Length(&vLook);

	D3DXVec3Normalize(&vRight, &vRight);
	D3DXVec3Normalize(&vLook, &vLook);
	D3DXVec3Normalize(&vUp, &vUp);

	vRight *= (fX*fTimeDelta + fX_Scale);
	vLook *= (fZ*fTimeDelta + fZ_Scale);
	vUp *= (fY*fTimeDelta + fY_Scale);

	memcpy(&matWorld.m[0][0], &vRight, sizeof(D3DXVECTOR3));
	memcpy(&matWorld.m[1][0], &vUp, sizeof(D3DXVECTOR3));
	memcpy(&matWorld.m[2][0], &vLook, sizeof(D3DXVECTOR3));

	return NOERROR;
}

HRESULT CTransform::Rotation(const float & fX, const float & fY, const float & fZ)
{

	return NOERROR;
}

HRESULT CTransform::RotationX(_float _Radian, const _float & fTimeDelta)
{
	D3DXVECTOR3 vRight, vLook, vUp;
	memcpy(&vRight, &matWorld.m[0][0], sizeof(D3DXVECTOR3));
	memcpy(&vUp, &matWorld.m[1][0], sizeof(D3DXVECTOR3));
	memcpy(&vLook, &matWorld.m[2][0], sizeof(D3DXVECTOR3));
	

	D3DXMATRIX matRotateUp;
	D3DXMatrixRotationAxis(&matRotateUp, &vRight, _Radian*fTimeDelta);

	D3DXVec3TransformNormal(&vUp, &vUp, &matRotateUp);
	D3DXVec3TransformNormal(&vLook, &vLook, &matRotateUp);

	memcpy(&matWorld.m[1][0], &vUp, sizeof(D3DXVECTOR3));
	memcpy(&matWorld.m[2][0], &vLook, sizeof(D3DXVECTOR3));

	return NOERROR;
}

HRESULT CTransform::RotationY(_float _Radian, const _float & fTimeDelta)
{
	D3DXVECTOR3 vRight, vLook, vUp;
	memcpy(&vRight, &matWorld.m[0][0], sizeof(D3DXVECTOR3));
	memcpy(&vUp, &matWorld.m[1][0], sizeof(D3DXVECTOR3));
	memcpy(&vLook, &matWorld.m[2][0], sizeof(D3DXVECTOR3));
	

	D3DXMATRIX matRotateUp;
	D3DXMatrixRotationAxis(&matRotateUp, &vUp, _Radian*fTimeDelta);

	D3DXVec3TransformNormal(&vRight, &vRight, &matRotateUp);
	D3DXVec3TransformNormal(&vLook, &vLook, &matRotateUp);

	memcpy(&matWorld.m[0][0], &vRight, sizeof(D3DXVECTOR3));
	memcpy(&matWorld.m[2][0], &vLook, sizeof(D3DXVECTOR3));

	return NOERROR;
}

HRESULT CTransform::RotationAxis(D3DXVECTOR3 vAxis, _float _Radian, const _float & fTimeDelta)
{
	if (D3DXVec3Length(&vAxis) == 0)
		return NOERROR;

	D3DXVECTOR3 vRight, vLook, vUp;
	memcpy(&vRight, &matWorld.m[0][0], sizeof(D3DXVECTOR3));
	memcpy(&vUp, &matWorld.m[1][0], sizeof(D3DXVECTOR3));
	memcpy(&vLook, &matWorld.m[2][0], sizeof(D3DXVECTOR3));

	D3DXMATRIX matRotateUp;
	D3DXMatrixIdentity(&matRotateUp);
	
	
	
	D3DXMatrixRotationAxis(&matRotateUp, &vAxis, _Radian*fTimeDelta);

	D3DXVec3TransformNormal(&vRight, &vRight, &matRotateUp);
	D3DXVec3TransformNormal(&vUp, &vUp, &matRotateUp);
	D3DXVec3TransformNormal(&vLook, &vLook, &matRotateUp);

	if (isnan(vRight[0]) || isnan(vUp[0]) || isnan(vLook[0]))
		return NOERROR;

	if (D3DXVec3Length(&vRight) <= 0)
		return NOERROR;

	if (D3DXVec3Length(&vLook) <= 0)
		return NOERROR;

	if (D3DXVec3Length(&vUp) <= 0)
		return NOERROR;


	memcpy(&matWorld.m[0][0], &vRight, sizeof(D3DXVECTOR3));
	memcpy(&matWorld.m[1][0], &vUp, sizeof(D3DXVECTOR3));
	memcpy(&matWorld.m[2][0], &vLook, sizeof(D3DXVECTOR3));

	return NOERROR;
}

HRESULT CTransform::Move(const float & fX, const float & fY, const float & fZ, const float & fSpeed, const _float & fTimeDelta)
{
	D3DXVECTOR3 vPos = matWorld.m[3];
	

	vPos += D3DXVECTOR3(fX*fSpeed*fTimeDelta, fY*fSpeed*fTimeDelta, fZ*fSpeed*fTimeDelta);

	memcpy(&matWorld.m[3][0], vPos, sizeof(D3DXVECTOR3));

	return NOERROR;
}

HRESULT CTransform::MoveStraight(const float & fSpeed, const _float & fTimeDelta)
{
	D3DXVECTOR3 vRight, vLook, vUp, vPos;
	memcpy(&vRight, &matWorld.m[0][0], sizeof(D3DXVECTOR3));
	memcpy(&vUp, &matWorld.m[1][0], sizeof(D3DXVECTOR3));
	memcpy(&vLook, &matWorld.m[2][0], sizeof(D3DXVECTOR3));
	memcpy(&vPos, &matWorld.m[3][0], sizeof(D3DXVECTOR3));

	D3DXVec3Normalize(&vLook, &vLook);
	vPos += vLook*fSpeed*fTimeDelta;	

	
	memcpy(&matWorld.m[3][0], vPos, sizeof(D3DXVECTOR3));

	return NOERROR;
}

HRESULT CTransform::MoveSide(const float & fSpeed, const _float & fTimeDelta)
{
	D3DXVECTOR3 vRight, vLook, vUp, vPos;
	memcpy(&vRight, &matWorld.m[0][0], sizeof(D3DXVECTOR3));
	memcpy(&vUp, &matWorld.m[1][0], sizeof(D3DXVECTOR3));
	memcpy(&vLook, &matWorld.m[2][0], sizeof(D3DXVECTOR3));
	memcpy(&vPos, &matWorld.m[3][0], sizeof(D3DXVECTOR3));

	D3DXVec3Normalize(&vRight, &vRight);
	vPos += vRight*fSpeed*fTimeDelta;


	memcpy(&matWorld.m[3][0], vPos, sizeof(D3DXVECTOR3));

	return NOERROR;
}

HRESULT CTransform::SetRight(D3DXVECTOR3 _vRight)
{
	memcpy(&matWorld.m[0][0], &_vRight, sizeof(D3DXVECTOR3));

	return NOERROR;
}

HRESULT CTransform::SetUp(D3DXVECTOR3 _vUp)
{
	memcpy(&matWorld.m[1][0], &_vUp, sizeof(D3DXVECTOR3));

	return NOERROR;
}

HRESULT CTransform::SetLook(D3DXVECTOR3 _vLook)
{
	memcpy(&matWorld.m[2][0], &_vLook, sizeof(D3DXVECTOR3));

	return NOERROR;
}

HRESULT CTransform::SetPosition(D3DXVECTOR3 _vPosition)
{
	memcpy(&matWorld.m[3][0], &_vPosition, sizeof(D3DXVECTOR3));

	return NOERROR;
}

D3DXVECTOR3 CTransform::GetRight()
{
	D3DXVECTOR3 vRight;
	memcpy(&vRight, &matWorld.m[0][0], sizeof(D3DXVECTOR3));
	return vRight;
}

D3DXVECTOR3 CTransform::GetUp()
{
	D3DXVECTOR3 vUp;
	memcpy(&vUp, &matWorld.m[1][0], sizeof(D3DXVECTOR3));
	return vUp;
}

D3DXVECTOR3 CTransform::GetLook()
{
	D3DXVECTOR3 vLook;
	memcpy(&vLook, &matWorld.m[2][0], sizeof(D3DXVECTOR3));
	return vLook;
}

D3DXVECTOR3 CTransform::GetPosition()
{
	D3DXVECTOR3 vPosition;
	memcpy(&vPosition, &matWorld.m[3][0], sizeof(D3DXVECTOR3));
	return vPosition;
}

D3DXVECTOR3 CTransform::GetScale()
{
	D3DXVECTOR3 vRight, vLook, vUp;
	memcpy(&vRight, &matWorld.m[0][0], sizeof(D3DXVECTOR3));
	memcpy(&vUp, &matWorld.m[1][0], sizeof(D3DXVECTOR3));
	memcpy(&vLook, &matWorld.m[2][0], sizeof(D3DXVECTOR3));

	float fX_Scale = 0.f, fY_Scale = 0.f, fZ_Scale = 0.f;

	fX_Scale = D3DXVec3Length(&vRight);
	fY_Scale = D3DXVec3Length(&vUp);
	fZ_Scale = D3DXVec3Length(&vLook);

	return D3DXVECTOR3(fX_Scale, fY_Scale, fZ_Scale);
}

HRESULT CTransform::SetTransform()
{
	if (m_pGraphicDev == nullptr)
		return E_FAIL;

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);

	return NOERROR;
}

CTransform * CTransform::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CTransform* pInstance = new CTransform(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CTransform Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent * CTransform::Clone()
{
	return new CTransform(*this);
}

void CTransform::Free()
{
	CComponent::Free();
}



