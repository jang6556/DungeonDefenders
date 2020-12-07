#include "..\Header\Collider.h"
#include "Shader.h"


HRESULT CCollider::Initialize()
{
	return NOERROR;
}

HRESULT CCollider::Initialize_Prototype(COLLIDER eType)
{
	switch (eType)
	{
	case CCollider::AABB:
	case CCollider::OBB:
		if (FAILED(D3DXCreateBox(m_pGraphicDev, 1, 1, 1, &m_pMesh, nullptr)))
			return E_FAIL;
		break;
	case CCollider::SPHERE:
		if (FAILED(D3DXCreateSphere(m_pGraphicDev, 0.5f, 20, 20, &m_pMesh, nullptr)))
			return E_FAIL;
		break;

	default:
		break;
	}
	m_ColliderType = eType;
	void* pVertex = nullptr;

	m_pMesh->LockVertexBuffer(0, &pVertex);

	if (FAILED(D3DXComputeBoundingBox((D3DXVECTOR3*)pVertex, m_pMesh->GetNumVertices(), D3DXGetFVFVertexSize(m_pMesh->GetFVF()),&m_vMin,&m_vMax)))
		return E_FAIL;

	m_pMesh->UnlockVertexBuffer();

	m_pShader = CShader::Create(m_pGraphicDev, L"ShaderFile/ShaderCollider.fx");

	ZeroMemory(&m_ColliderInfo, sizeof(COLLIDERINFO));
	D3DXMatrixIdentity(&m_ColliderInfo.m_WorldMatrix);

	D3DXMatrixIdentity(&m_matWorld);

	if (m_ColliderType == AABB || m_ColliderType == OBB)
	{
		if (FAILED(CreateObbInfo()))
			return E_FAIL;
	}

	return NOERROR;
}

D3DXMATRIX CCollider::ComputeAABB(D3DXMATRIX matInput)
{
	D3DXMATRIX matOut;
	D3DXMatrixIdentity(&matOut);

	memcpy(&matOut.m[3][0], &matInput.m[3][0], sizeof(D3DXVECTOR3));

	return matOut;
}

D3DXMATRIX CCollider::ComputeOBB(D3DXMATRIX matInput)
{
	D3DXMATRIX matOut;
	D3DXMatrixIdentity(&matOut);

	matOut = matInput;

	D3DXVec3Normalize((D3DXVECTOR3*)&matOut.m[0][0], (D3DXVECTOR3*)&matOut.m[0][0]);
	D3DXVec3Normalize((D3DXVECTOR3*)&matOut.m[1][0], (D3DXVECTOR3*)&matOut.m[1][0]);
	D3DXVec3Normalize((D3DXVECTOR3*)&matOut.m[2][0], (D3DXVECTOR3*)&matOut.m[2][0]);	

	return matOut;
}

HRESULT CCollider::CreateObbInfo()
{
	m_pObbInfo = new OBBINFO;
	ZeroMemory(m_pObbInfo, sizeof(OBBINFO));	

	m_pObbInfo->vPoint[0] = D3DXVECTOR3(m_vMin.x, m_vMax.y, m_vMin.z);
	m_pObbInfo->vPoint[1] = D3DXVECTOR3(m_vMax.x, m_vMax.y, m_vMin.z);
	m_pObbInfo->vPoint[2] = D3DXVECTOR3(m_vMax.x, m_vMin.y, m_vMin.z);
	m_pObbInfo->vPoint[3] = D3DXVECTOR3(m_vMin.x, m_vMin.y, m_vMin.z);

	m_pObbInfo->vPoint[4] = D3DXVECTOR3(m_vMin.x, m_vMax.y, m_vMax.z);
	m_pObbInfo->vPoint[5] = D3DXVECTOR3(m_vMax.x, m_vMax.y, m_vMax.z);
	m_pObbInfo->vPoint[6] = D3DXVECTOR3(m_vMax.x, m_vMin.y, m_vMax.z);
	m_pObbInfo->vPoint[7] = D3DXVECTOR3(m_vMin.x, m_vMin.y, m_vMax.z);

	m_pObbInfo->vLine[0] = m_pObbInfo->vPoint[2] - m_pObbInfo->vPoint[3];
	m_pObbInfo->vLine[1] = m_pObbInfo->vPoint[0] - m_pObbInfo->vPoint[3];
	m_pObbInfo->vLine[2] = m_pObbInfo->vPoint[7] - m_pObbInfo->vPoint[3];

	for (int i = 0; i < 3; ++i)
		D3DXVec3Normalize(&m_pObbInfo->vLine[i], &m_pObbInfo->vLine[i]);

	m_pObbInfo->vPosition = (m_pObbInfo->vPoint[3] + m_pObbInfo->vPoint[5])*0.5f;


	m_pObbInfo->vAspectNormal[0] = (m_pObbInfo->vPoint[2] + m_pObbInfo->vPoint[5])*0.5f - m_pObbInfo->vPosition;
	m_pObbInfo->vAspectNormal[1] = (m_pObbInfo->vPoint[4] + m_pObbInfo->vPoint[6])*0.5f - m_pObbInfo->vPosition;
	m_pObbInfo->vAspectNormal[2] = (m_pObbInfo->vPoint[0] + m_pObbInfo->vPoint[5])*0.5f - m_pObbInfo->vPosition;
			
	return NOERROR;
}

void CCollider::ComputeMatrix(OBBINFO * _pObbInfo, D3DXMATRIX* _matWorld)
{
	if (_pObbInfo == nullptr || _matWorld == nullptr)
		return;


	D3DXVec3TransformCoord(&_pObbInfo->vPosition, &_pObbInfo->vPosition, _matWorld);

	for (int i = 0; i < 3; ++i)
	{
		D3DXVec3TransformNormal(&_pObbInfo->vLine[i], &_pObbInfo->vLine[i], _matWorld);
		D3DXVec3Normalize(&_pObbInfo->vLine[i], &_pObbInfo->vLine[i]);
		D3DXVec3TransformNormal(&_pObbInfo->vAspectNormal[i], &_pObbInfo->vAspectNormal[i], _matWorld);
	}
}

CCollider::CCollider(LPDIRECT3DDEVICE9 _m_pGraphicDevice)
	:CComponent(_m_pGraphicDevice)
{
}

CCollider::CCollider(const CCollider & rhs)
	: CComponent(rhs), 
	m_ColliderType(rhs.m_ColliderType), 
	m_pShader(rhs.m_pShader), 
	m_ColliderInfo(rhs.m_ColliderInfo),
	m_vMin(rhs.m_vMin),
	m_vMax(rhs.m_vMax),
	m_matWorld(rhs.m_matWorld),
	m_pObbInfo(rhs.m_pObbInfo)

{
	m_pShader->AddRef();
	rhs.m_pMesh->CloneMeshFVF(rhs.m_pMesh->GetOptions(), rhs.m_pMesh->GetFVF(), rhs.m_pGraphicDev, &m_pMesh);
}

HRESULT CCollider::Render()
{
	LPD3DXEFFECT pEffect = m_pShader->GetEffect();
	if (pEffect == nullptr)
		return E_FAIL;
	D3DXMATRIX matView, matProj;
	D3DXMATRIX matComputeMatirx;

	if (m_ColliderInfo.m_pBoneMatirx == nullptr)
		matComputeMatirx = (*m_ColliderInfo.m_pParentsTransform);
	else
		matComputeMatirx = (*m_ColliderInfo.m_pBoneMatirx)*(*m_ColliderInfo.m_pParentsTransform);


	switch (m_ColliderType)
	{
	case Engine::CCollider::AABB:
	case Engine::CCollider::SPHERE:
		m_matWorld = (m_ColliderInfo.m_WorldMatrix)*ComputeAABB(matComputeMatirx);
		break;
	case Engine::CCollider::OBB:
		m_matWorld = (m_ColliderInfo.m_WorldMatrix)*ComputeOBB(matComputeMatirx);
		break;
	}		

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matWorld", &m_matWorld);
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);
	pEffect->SetBool("g_IsCollision", m_IsCollision);

	pEffect->Begin(nullptr, 0);
	pEffect->BeginPass(0);
	m_pMesh->DrawSubset(0);
	pEffect->EndPass();
	pEffect->End();


	return NOERROR;
}

HRESULT CCollider::SetBoneMatrix(D3DXMATRIX* pParentsMatirx, D3DXMATRIX* pWorldMatirx,D3DXMATRIX * pBoneMatirx)
{
	if(pParentsMatirx!=nullptr)
		m_ColliderInfo.m_pParentsTransform = pParentsMatirx;
	
	if(pWorldMatirx != nullptr)
		m_ColliderInfo.m_WorldMatrix = *pWorldMatirx;	

	m_ColliderInfo.m_pBoneMatirx = pBoneMatirx;

	return NOERROR;
}

HRESULT CCollider::ChangeColliderType(COLLIDER eType)
{
	return NOERROR;
}

D3DXMATRIX * CCollider::GetWorldMatrix()
{
	D3DXMATRIX matComputeMatirx;

	if (m_ColliderInfo.m_pBoneMatirx == nullptr)
		matComputeMatirx = (*m_ColliderInfo.m_pParentsTransform);
	else
		matComputeMatirx = (*m_ColliderInfo.m_pBoneMatirx)*(*m_ColliderInfo.m_pParentsTransform);


	switch (m_ColliderType)
	{
	case Engine::CCollider::AABB:
	case Engine::CCollider::SPHERE:
		m_matWorld = (m_ColliderInfo.m_WorldMatrix)*ComputeAABB(matComputeMatirx);
		break;
	case Engine::CCollider::OBB:
		m_matWorld = (m_ColliderInfo.m_WorldMatrix)*ComputeOBB(matComputeMatirx);
		break;
	}

	return &m_matWorld;
}

bool CCollider::CheckCollision_SPHERE(CCollider * pInputCollider)
{
	if (m_ColliderType != SPHERE || pInputCollider->m_ColliderType != SPHERE || pInputCollider->m_IsCollision == true)
		return false;

	
	D3DXMATRIX matWorld = *GetWorldMatrix();
	D3DXMATRIX matInputWorld= *pInputCollider->GetWorldMatrix();

	D3DXVECTOR3 vPosition, vInputPosition;
	
	memcpy(&vPosition, &matWorld.m[3][0], sizeof(D3DXVECTOR3));
	memcpy(&vInputPosition, &matInputWorld.m[3][0], sizeof(D3DXVECTOR3));

	D3DXVECTOR3 vRange, vInputRange;

	memcpy(&vRange, &matWorld.m[0][0], sizeof(D3DXVECTOR3));
	memcpy(&vInputRange, &matInputWorld.m[0][0], sizeof(D3DXVECTOR3));

	float fRange = D3DXVec3Length(&(vRange))/2.f + D3DXVec3Length(&(vInputRange))/2.f;
	float fLength= D3DXVec3Length(&(vPosition - vInputPosition));
	
	if (fLength <= fRange)
	{
		return true;
	}
	return false;
}

bool CCollider::CheckCollision_AABB(CCollider * pInputCollider)
{
	D3DXVECTOR3 vMin, vMax;
	D3DXVECTOR3 vInputMin, vInputMax;

	D3DXVec3TransformCoord(&vMin, &m_vMin, GetWorldMatrix());
	D3DXVec3TransformCoord(&vMax, &m_vMax, GetWorldMatrix());

	D3DXVec3TransformCoord(&vInputMin, &pInputCollider->m_vMin, pInputCollider->GetWorldMatrix());
	D3DXVec3TransformCoord(&vInputMax, &pInputCollider->m_vMax, pInputCollider->GetWorldMatrix());

	
	if (max(vMin.x, vInputMin.x) > min(vMax.x, vInputMax.x))
		return false;			
								
	if (max(vMin.y, vInputMin.y) > min(vMax.y, vInputMax.y))
		return false;			
								
	if (max(vMin.z, vInputMin.z) > min(vMax.z, vInputMax.z))
		return false;

	return true;
}

bool CCollider::CheckCollision_OBB(CCollider * pInputCollider)
{
	if (m_pObbInfo == nullptr || pInputCollider->m_pObbInfo == nullptr)
		return false;

	m_IsCollision = false;

	OBBINFO OBB_Info[2];

	OBB_Info[0] = *m_pObbInfo;
	OBB_Info[1] = *pInputCollider->m_pObbInfo;

	ComputeMatrix(&OBB_Info[0], GetWorldMatrix());
	ComputeMatrix(&OBB_Info[1], pInputCollider->GetWorldMatrix());

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			D3DXVECTOR3 vCenterDir;

			vCenterDir = OBB_Info[1].vPosition - OBB_Info[0].vPosition;
			
			float fDistance[3];

			fDistance[0] = fabs(D3DXVec3Dot(&vCenterDir, &OBB_Info[i].vLine[j]));

			fDistance[1] = fabs(D3DXVec3Dot(&OBB_Info[0].vAspectNormal[0], &OBB_Info[i].vLine[j])) +
						   fabs(D3DXVec3Dot(&OBB_Info[0].vAspectNormal[1], &OBB_Info[i].vLine[j])) +
			               fabs(D3DXVec3Dot(&OBB_Info[0].vAspectNormal[2], &OBB_Info[i].vLine[j]));		

			fDistance[2] = fabs(D3DXVec3Dot(&OBB_Info[1].vAspectNormal[0], &OBB_Info[i].vLine[j])) +
						   fabs(D3DXVec3Dot(&OBB_Info[1].vAspectNormal[1], &OBB_Info[i].vLine[j])) +
				           fabs(D3DXVec3Dot(&OBB_Info[1].vAspectNormal[2], &OBB_Info[i].vLine[j]));

			if (fDistance[0] > fDistance[1] + fDistance[2])
				return false;
		}
	}

	D3DXVECTOR3 vCross[9];

	D3DXVec3Cross(&vCross[0], &OBB_Info[0].vLine[0], &OBB_Info[1].vLine[0]);
	D3DXVec3Cross(&vCross[1], &OBB_Info[0].vLine[0], &OBB_Info[1].vLine[1]);
	D3DXVec3Cross(&vCross[2], &OBB_Info[0].vLine[0], &OBB_Info[1].vLine[2]);

	D3DXVec3Cross(&vCross[3], &OBB_Info[0].vLine[1], &OBB_Info[1].vLine[0]);
	D3DXVec3Cross(&vCross[4], &OBB_Info[0].vLine[1], &OBB_Info[1].vLine[1]);
	D3DXVec3Cross(&vCross[5], &OBB_Info[0].vLine[1], &OBB_Info[1].vLine[2]);

	D3DXVec3Cross(&vCross[6], &OBB_Info[0].vLine[2], &OBB_Info[1].vLine[0]);
	D3DXVec3Cross(&vCross[7], &OBB_Info[0].vLine[2], &OBB_Info[1].vLine[1]);
	D3DXVec3Cross(&vCross[8], &OBB_Info[0].vLine[2], &OBB_Info[1].vLine[2]);

	for (int i = 0; i < 9; ++i)
	{		
		D3DXVECTOR3 vCenterDir;
		
		vCenterDir = OBB_Info[1].vPosition - OBB_Info[0].vPosition;
		
		float fDistance[3];
		
		fDistance[0] = fabs(D3DXVec3Dot(&vCenterDir, &vCross[i]));
		
		
		fDistance[1] = fabs(D3DXVec3Dot(&OBB_Info[0].vAspectNormal[1], &vCross[i])) +
					   fabs(D3DXVec3Dot(&OBB_Info[0].vAspectNormal[2], &vCross[i])) +
					   fabs(D3DXVec3Dot(&OBB_Info[0].vAspectNormal[3], &vCross[i]));
																		
		fDistance[2] = fabs(D3DXVec3Dot(&OBB_Info[1].vAspectNormal[1], &vCross[i])) +
					   fabs(D3DXVec3Dot(&OBB_Info[1].vAspectNormal[2], &vCross[i])) +
					   fabs(D3DXVec3Dot(&OBB_Info[1].vAspectNormal[3], &vCross[i]));
		
		if (fDistance[0] > fDistance[1] + fDistance[2])
			return false;		
	}
	
	m_IsCollision = true;
	
	return true;
}

CCollider * CCollider::Create(LPDIRECT3DDEVICE9 _m_pGraphicDevice, COLLIDER eType)
{
	CCollider* pInstance = new CCollider(_m_pGraphicDevice);

	if (FAILED(pInstance->Initialize_Prototype(eType)))
	{
		_MSGBOX("CCollider Created Failed");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CCollider::Clone()
{
	CCollider* pInstance = new CCollider(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CCollider Created Failed");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CCollider::Free()
{
	if (m_IsClone == false)
		Safe_Delete(m_pObbInfo);

	Safe_Release(m_pMesh);
	Safe_Release(m_pShader);
	CComponent::Free();
}
