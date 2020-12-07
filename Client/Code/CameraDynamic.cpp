#include "stdafx.h"
#include "..\Header\CameraDynamic.h"
#include "../Header/Define.h"
#include "../Header/Player.h"

_USING(Client)

CCameraDynamic::CCameraDynamic(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CCameraObject(_m_pGraphicDev), m_pInputDev(CInputDev::GetInstance())
{
	m_pInputDev->AddRef();
}

CCameraDynamic::CCameraDynamic(const CCameraDynamic & rhs)
	:CCameraObject(rhs), m_pInputDev(rhs.m_pInputDev),m_pPlayer(rhs.m_pPlayer)
{
	m_pInputDev->AddRef();
}

HRESULT CCameraDynamic::SetViewMatrix()
{
	if (m_Transform == nullptr)
		return E_FAIL;

	D3DXMATRIX V;

	D3DXMatrixInverse(&V, nullptr, &*m_Transform->GetWorldMatrix());

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &V);
	return NOERROR;
}

HRESULT CCameraDynamic::SetProjectionMatrix()
{
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		m_pCamerInfo.fFovY,
		m_pCamerInfo.fAspect,
		m_pCamerInfo.fNear,
		m_pCamerInfo.fFar
	);

	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &proj);
	return NOERROR;
}

HRESULT CCameraDynamic::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_Transform)))
		return E_FAIL;

	return NOERROR;
}

void CCameraDynamic::SetState()
{
	_uint	pPlayer_State=m_pPlayer->GetPlayerMode();

	if (m_eState == STATE_DEFAULT && pPlayer_State == 1)
	{
		m_eState = STATE_DEFAULT_TO_BUILD;		
		return;
	}

	if (m_eState == STATE_BUILD && pPlayer_State == 0)
	{
		m_eState = STATE_BUILD_TO_DEFAULT;		
		return;
	}

}

void CCameraDynamic::ReSetCamera()
{
	CTransform* pTransform = (CTransform*)CGameObjectMgr::GetInstance()->FindComponent(SCENESTATIC, L"PLAYER", L"TRANSFORM");

	D3DXVECTOR3 vRight, vUp, vLook;
	D3DXVECTOR3 vPlayerLook;
	D3DXVECTOR3 vPosition;

	vPlayerLook = pTransform->GetLook();	
	vPlayerLook.y = 0;
	D3DXVec3Normalize(&vPlayerLook, &vPlayerLook);
	
	vPosition = pTransform->GetPosition() - vPlayerLook * 5;
	vPosition.y += 5;


	vLook = pTransform->GetPosition() - vPosition;

	
	D3DXVec3Cross(&vRight, &(D3DXVECTOR3(0.f,1.f,0.f)), &vLook);
	D3DXVec3Cross(&vUp, &vLook, &vRight);

	D3DXVec3Normalize(&vRight, &vRight);
	D3DXVec3Normalize(&vLook, &vLook);
	D3DXVec3Normalize(&vUp, &vUp); 

	m_Transform->SetRight(vRight);
	m_Transform->SetUp(vUp);
	m_Transform->SetLook(vLook);
	
}

void CCameraDynamic::Default_Camera(const _float & fTimeDelta)
{
	if (GetAsyncKeyState('I') && m_bKeyFlag == false)
	{
		m_bKeyFlag = true;
		m_bIsStatPanelRender = m_bIsStatPanelRender ? false : true;		
	}

	if (!GetAsyncKeyState('I') && m_bKeyFlag == true)
	{
		m_bKeyFlag = false;
	}

	if (m_bIsStatPanelRender == true)
		return;


	long dwMouseMove = 0;

	if (dwMouseMove = m_pInputDev->GetMouseMove(CInputDev::DIMM_Y))
	{
		m_Transform->RotationAxis(m_Transform->GetRight(), D3DXToRadian(dwMouseMove) * 7.f, fTimeDelta);
	}

	if (dwMouseMove = m_pInputDev->GetMouseMove(CInputDev::DIMM_X))
	{
		m_Transform->RotationAxis(D3DXVECTOR3(0.f, 1.f, 0.f), D3DXToRadian(dwMouseMove) * 7.f, fTimeDelta);
	}

	D3DXVECTOR3 vLook, vPosition, vRight;
	CTransform* pTransform = (CTransform*)CGameObjectMgr::GetInstance()->FindComponent(SCENESTATIC, L"PLAYER", L"TRANSFORM");

	vLook = pTransform->GetLook();
	D3DXVec3Normalize(&vLook, &vLook);
	vPosition = pTransform->GetPosition();
	vPosition -= vLook*2.3f;
	vPosition.y += 2.4f;

	vRight = m_Transform->GetRight();
	D3DXVec3Normalize(&vRight, &vRight);
	vPosition += vRight*0.7f;

	/*m_Transform->SetPosition()*/
	m_Transform->SetPosition(vPosition);

	
}

void CCameraDynamic::Default_To_Build_Camera(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta;
	if (m_fTimeDelta >= 0.5f)
	{
		m_fTimeDelta = 0;
		m_eState = STATE_BUILD;
		return;
	}	

	m_Transform->Move(0, 1.5f, 0, 3, fTimeDelta);


	D3DXVECTOR3 vPosition = m_Transform->GetPosition();
	D3DXVECTOR3 vPlayer_Position=((CTransform*)m_pPlayer->GetComponent(L"TRANSFORM"))->GetPosition();
	
	D3DXVECTOR3 vComputePosition = vPosition - vPlayer_Position;

	D3DXMATRIX matRotate;
	D3DXMatrixIdentity(&matRotate);
	D3DXMatrixRotationAxis(&matRotate, &(m_Transform->GetRight()), D3DXToRadian(60)*fTimeDelta);

	D3DXVec3TransformCoord(&vComputePosition, &vComputePosition, &matRotate);

	vPosition = vComputePosition + vPlayer_Position;

	D3DXVECTOR3 vLook = vPlayer_Position - vPosition;

	D3DXVECTOR3 vRight;
	D3DXVec3Cross(&vRight, &D3DXVECTOR3(0, 1, 0), &vLook);

	D3DXVECTOR3 vUp;
	D3DXVec3Cross(&vUp, &vLook, &vRight);

	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	D3DXVec3Normalize(&vRight, &vRight);
	D3DXVec3Normalize(&vUp, &vUp);
	D3DXVec3Normalize(&vLook, &vLook);
	memcpy(&matWorld.m[0][0], &vRight, sizeof(D3DXVECTOR3));
	memcpy(&matWorld.m[1][0], &vUp, sizeof(D3DXVECTOR3));
	memcpy(&matWorld.m[2][0], &vLook, sizeof(D3DXVECTOR3));
	memcpy(&matWorld.m[3][0], &vPosition, sizeof(D3DXVECTOR3));

	m_Transform->SetWorldMatrix(matWorld);
}

void CCameraDynamic::Build_Camera(const _float & fTimeDelta)
{
	int iPlayerBuildState = m_pPlayer->GetBuildState();

	if (iPlayerBuildState == CPlayer::BUILD_ING)
	{
		if (m_fTimeDelta >= 0.3f)
			return;
		m_fTimeDelta += fTimeDelta;		

		m_Transform->Move(0, -1.5f, 0, 3, fTimeDelta);
		
		D3DXVECTOR3 vPosition = m_Transform->GetPosition();
		D3DXVECTOR3 vPlayer_Position = ((CTransform*)m_pPlayer->GetComponent(L"TRANSFORM"))->GetPosition();

		D3DXVECTOR3 vComputePosition = vPosition - vPlayer_Position;

		D3DXMATRIX matRotate;
		D3DXMatrixRotationAxis(&matRotate, &(m_Transform->GetRight()), -D3DXToRadian(60)*fTimeDelta);

		D3DXVec3TransformCoord(&vComputePosition, &vComputePosition, &matRotate);

		vPosition = vComputePosition + vPlayer_Position;

		D3DXVECTOR3 vLook = vPlayer_Position - vPosition;

		D3DXVECTOR3 vRight;
		D3DXVec3Cross(&vRight, &D3DXVECTOR3(0, 1, 0), &vLook);

		D3DXVECTOR3 vUp;
		D3DXVec3Cross(&vUp, &vLook, &vRight);

		D3DXMATRIX matWorld;
		D3DXMatrixIdentity(&matWorld);

		D3DXVec3Normalize(&vRight, &vRight);
		D3DXVec3Normalize(&vUp, &vUp);
		D3DXVec3Normalize(&vLook, &vLook);

		memcpy(&matWorld.m[0][0], &vRight, sizeof(D3DXVECTOR3));
		memcpy(&matWorld.m[1][0], &vUp, sizeof(D3DXVECTOR3));
		memcpy(&matWorld.m[2][0], &vLook, sizeof(D3DXVECTOR3));
		memcpy(&matWorld.m[3][0], &vPosition, sizeof(D3DXVECTOR3));

		m_Transform->SetWorldMatrix(matWorld);
	}
}

void CCameraDynamic::Build_To_Default_Camera(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta;
	if (m_fTimeDelta >= 0.5f)
	{
		m_fTimeDelta = 0;
		m_eState = STATE_DEFAULT;

		ReSetCamera();
		return;
	}

	m_Transform->Move(0, -1.5f, 0, 3, fTimeDelta);


	D3DXVECTOR3 vPosition = m_Transform->GetPosition();
	D3DXVECTOR3 vPlayer_Position = ((CTransform*)m_pPlayer->GetComponent(L"TRANSFORM"))->GetPosition();

	D3DXVECTOR3 vComputePosition = vPosition - vPlayer_Position;

	D3DXMATRIX matRotate;
	D3DXMatrixRotationAxis(&matRotate, &(m_Transform->GetRight()), -D3DXToRadian(60)*fTimeDelta);

	D3DXVec3TransformCoord(&vComputePosition, &vComputePosition, &matRotate);

	vPosition = vComputePosition + vPlayer_Position;

	D3DXVECTOR3 vLook = vPlayer_Position - vPosition;

	D3DXVECTOR3 vRight;
	D3DXVec3Cross(&vRight, &D3DXVECTOR3(0, 1, 0), &vLook);

	D3DXVECTOR3 vUp;
	D3DXVec3Cross(&vUp, &vLook, &vRight);

	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	D3DXVec3Normalize(&vRight, &vRight);
	D3DXVec3Normalize(&vUp, &vUp);
	D3DXVec3Normalize(&vLook, &vLook);

	memcpy(&matWorld.m[0][0], &vRight, sizeof(D3DXVECTOR3));
	memcpy(&matWorld.m[1][0], &vUp, sizeof(D3DXVECTOR3));
	memcpy(&matWorld.m[2][0], &vLook, sizeof(D3DXVECTOR3));
	memcpy(&matWorld.m[3][0], &vPosition, sizeof(D3DXVECTOR3));

	m_Transform->SetWorldMatrix(matWorld);
}

HRESULT CCameraDynamic::Initialize()
{
	return NOERROR;
}

HRESULT CCameraDynamic::Initialize_Prototype(void* pInfo)
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	CCameraObject::CAMERAINFO*		pCameraInfo = (CCameraObject::CAMERAINFO*)pInfo;

	D3DXVECTOR3 vRight,vUp,vLook;
	vLook = pCameraInfo->vAt - pCameraInfo->vEye;
	D3DXVec3Cross(&vRight, &pCameraInfo->vAxisY, &vLook);
	D3DXVec3Cross(&vUp, &vLook, &vRight);

	D3DXVec3Normalize(&vRight, &vRight);
	D3DXVec3Normalize(&vLook, &vLook);
	D3DXVec3Normalize(&vUp, &vUp);

	m_Transform->SetRight(vRight);
	m_Transform->SetUp(vUp);
	m_Transform->SetLook(vLook);
	m_Transform->SetPosition(pCameraInfo->vEye);

	m_pCamerInfo = *pCameraInfo;


	SetViewMatrix();
	SetProjectionMatrix();

	m_pPlayer = (CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
	if (m_pPlayer == nullptr)
		return E_FAIL;

	return NOERROR;
}

_int CCameraDynamic::Progress(const _float & fTimeDelta)
{
	if (nullptr == m_pInputDev)
		return -1;	              
	
	
	SetState();

	if (m_eState == STATE_BUILD_TO_DEFAULT)
		Build_To_Default_Camera(fTimeDelta);

	if (m_eState == STATE_DEFAULT)
		Default_Camera(fTimeDelta);

	if (m_eState == STATE_DEFAULT_TO_BUILD)
		Default_To_Build_Camera(fTimeDelta);

	if (m_eState == STATE_BUILD)
		Build_Camera(fTimeDelta);

	
	
	
	return _int();
}

_int CCameraDynamic::LateProgress(const _float & fTimeDelta)
{
	SetViewMatrix();
	SetProjectionMatrix();
	return _int();
}

HRESULT CCameraDynamic::Render()
{
	return NOERROR;
}

CGameObject * CCameraDynamic::Clone(void* pInfo)
{
	CCameraDynamic* pInstance = new CCameraDynamic(*this);

	if (FAILED(pInstance->Initialize_Prototype(pInfo)))
	{
		_MSGBOX("CCameraDynamic Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CCameraDynamic * CCameraDynamic::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CCameraDynamic* pInstance = new CCameraDynamic(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CCameraDynamic Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCameraDynamic::Free()
{
	Safe_Release(m_Transform);
	Safe_Release(m_pInputDev);
	CCameraObject::Free();
}
