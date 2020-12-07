#include "stdafx.h"
#include "..\Header\LightObject.h"

_USING(Client)

HRESULT CLightObject::Initialize()
{
	return NOERROR;
}

HRESULT CLightObject::Initialize(void * pArg)
{
	return NOERROR;
}

HRESULT CLightObject::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CLightObject::AddComponent()
{
	if (CStaticMapObject::AddComponent())
		return E_FAIL;
	
	return NOERROR;
}

HRESULT CLightObject::LoadLightData(TCHAR * szFilePath)
{
	HANDLE	hFile = CreateFile(szFilePath,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hFile == 0)
		return E_FAIL;

	DWORD		dwByte;

	while (1)
	{
		LIGHTDATA* pInstance = new LIGHTDATA;
		if (pInstance == nullptr)
			break;

		ReadFile(hFile, pInstance, sizeof(LIGHTDATA), &dwByte, NULL);
		if (dwByte == 0)
		{
			Safe_Delete(pInstance);
			break;
		}

		m_pLightList.push_back(pInstance);

	}
	CloseHandle(hFile);

	return NOERROR;	
}

HRESULT CLightObject::SetPointLight(SCENEID eType)
{
	//return NOERROR;

	if (m_pTransform == nullptr)
		return E_FAIL;

	D3DXVECTOR3 vRight, vUp, vLook,vPosition;

	vRight  = m_pTransform->GetRight();
	vUp		= m_pTransform->GetUp();
	vLook   = m_pTransform->GetLook();
	vPosition = m_pTransform->GetPosition();

	D3DXVec3Normalize(&vRight, &vRight);
	D3DXVec3Normalize(&vUp, &vUp);
	D3DXVec3Normalize(&vLook, &vLook);

	D3DXMATRIX matWolrd;
	D3DXMatrixIdentity(&matWolrd);

	memcpy(&matWolrd.m[0][0], &vRight, sizeof(D3DXVECTOR3));
	memcpy(&matWolrd.m[1][0], &vUp, sizeof(D3DXVECTOR3));
	memcpy(&matWolrd.m[2][0], &vLook, sizeof(D3DXVECTOR3));
	memcpy(&matWolrd.m[3][0], &vPosition, sizeof(D3DXVECTOR3));
		
	for (auto& iter : m_pLightList)
	{
		D3DXVECTOR3 vLightPosition;
		D3DXVec3TransformCoord(&vLightPosition, &iter->vPosition, &matWolrd);	

		D3DLIGHT9 Light;
		
		ZeroMemory(&Light, sizeof(D3DLIGHT9));

		Light.Type = D3DLIGHT_POINT;
		Light.Position = vLightPosition;
		Light.Range = iter->fRange;

		Light.Diffuse = D3DXCOLOR(iter->vColor.x, iter->vColor.y, iter->vColor.z, 1.f);
		Light.Ambient = D3DXCOLOR(0.1f+0.4f*Light.Diffuse.r, 0.1f + 0.4f*Light.Diffuse.g, 0.1f + 0.4f*Light.Diffuse.b, 1.f);
		Light.Specular = Light.Diffuse;

		if (FAILED(CLightMgr::GetInstance()->AddLight(eType, m_pGraphicDev, &Light)))
			return E_FAIL;
	}

	return NOERROR;
}

CLightObject::CLightObject(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CStaticMapObject(_m_pGraphicDev)
{
}

CLightObject::CLightObject(const CLightObject & rhs)
	: CStaticMapObject(rhs),m_pLightList(rhs.m_pLightList)
{
}

_int CLightObject::Progress(const _float & fTimeDelta)
{
	return CStaticMapObject::Progress(fTimeDelta);
}

_int CLightObject::LateProgress(const _float & fTimeDelta)
{
	return CStaticMapObject::LateProgress(fTimeDelta);
}

HRESULT CLightObject::Render()
{
	return CStaticMapObject::Render();
}

CGameObject * CLightObject::Clone(void * pArg)
{
	return nullptr;
}

void CLightObject::Free()
{
	if (CGameObject::GetIsClone() == false)
	{
		for (auto& iter : m_pLightList)
		{
			if (iter != nullptr)
				Safe_Delete(iter);
		}
	}

	CStaticMapObject::Free();
}
