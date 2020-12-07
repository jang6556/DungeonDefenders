#include "stdafx.h"
#include "..\Header\ManaToken.h"


_USING(Client)

HRESULT CManaToken::Initialize()
{
	
	return NOERROR;
}

HRESULT CManaToken::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	if (FAILED(CItem::Initialize(pArg)))
		return E_FAIL;	

	
	m_iShaderPass = 2;

	m_vSpeed = D3DXVECTOR3(rand() % 200 / 100.f-1.0f, rand() % 100 / 100.f+2.5f, rand() % 200 / 100.f - 1.0f);
	m_vAngle = D3DXVECTOR3(rand() % 90+90, rand() % 90 + 90, rand() % 90 + 90);

	if (FAILED(SetManaInfo()))
		return E_FAIL;

	m_pTransform->Scaling(m_vScale.x, m_vScale.y, m_vScale.z);

	return NOERROR;
}

HRESULT CManaToken::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CManaToken::AddComponent()
{
	if (FAILED(CItem::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"MANA_TOKEN", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"FILTER", (CComponent**)&m_pTexture)))
		return E_FAIL;

	return NOERROR;
}

bool CManaToken::CalculateAngle()
{
	D3DXVECTOR3 vDir[3];

	vDir[0] = m_pTransform->GetRight();
	vDir[1] = m_pTransform->GetUp();
	vDir[2] = m_pTransform->GetLook();

	D3DXVec3Normalize(&vDir[0], &vDir[0]);
	D3DXVec3Normalize(&vDir[1], &vDir[1]);
	D3DXVec3Normalize(&vDir[2], &vDir[2]);

	for (size_t i = 0; i < 3; ++i)
	{
		float fCos = D3DXVec3Dot(&vDir[i], &D3DXVECTOR3(0, 1, 0));
	
		if (fCos >= 0.98f || fCos <= -0.98f)
		{
			m_eRotateDir =(ROTATE_DIR)i;		

			D3DXVECTOR3 vUp;
			
			D3DXVec3Cross(&vUp,  &D3DXVECTOR3(0, 1, 0),&vDir[i]);
			
			float fAngle = acos(fCos);

			m_pTransform->RotationAxis(vUp, -fAngle, 1);

			return true;
		}
	}
	
	return false;
}

void CManaToken::ReSetTransform(ROTATE_DIR eType)
{
	
}

HRESULT CManaToken::SetManaInfo()
{
	int iRand = rand()%100;

	if (iRand >= 0 && iRand < 10)
	{
		m_eMana = MANA_BLUE;

		m_vColor = { 0.0275f,0.3922f,1.f };

		m_vScale = { 0.008f,0.005f,0.013f };
	}
	else if (iRand >= 10 && iRand < 50)
	{
		m_eMana = MANA_RED;

		m_vColor = { 1.f,0.3725f,0.251f };

		m_vScale = { 0.013f,0.01f,0.013f };
	}
	else if (iRand >= 50 && iRand < 90)
	{
		m_eMana = MANA_GREEN;

		m_vColor = { 0.3176f,1.f,0.051f };

		m_vScale = { 0.015f,0.01f,0.015f };
	}
	else if (iRand >= 90 && iRand < 95)
	{
		m_eMana = MANA_PURPLE;

		m_vColor = { 0.6824f,0.f,0.949f };

		m_vScale = { 0.015f,0.013f,0.015f };
	}
	else if (iRand >= 95 && iRand < 98)
	{
		m_eMana = MANA_SKY;

		m_vColor = { 0.1922f,0.8941f,1.f };

		m_vScale = { 0.02f,0.017f,0.02f };
	}
	else if (iRand >= 98 && iRand < 100)
	{
		m_eMana = MANA_YELLOW;

		m_vColor = { 0.9686f,0.902f,0.f};

		m_vScale = { 0.025f,0.02f,0.025f };
	}

	return NOERROR;
}

CManaToken::CManaToken(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CItem(_m_pGraphicDev)
{

}

CManaToken::CManaToken(const CManaToken & rhs)
	: CItem(rhs)
{

}

_int CManaToken::Progress(const _float & fTimeDelta)
{
	
	m_fTimeDrop += fTimeDelta;
	
	if (m_bFinish == false)
	{
		m_fTimeDelta += fTimeDelta*60.f;
		
		if (m_pNaviMesh->MoveNavigation(m_pTransform->GetPosition(), D3DXVECTOR3(m_vSpeed.x,0,0),5, fTimeDelta))
			m_pTransform->Move(m_vSpeed.x, 0, 0, 3, fTimeDelta);

		if (m_pNaviMesh->MoveNavigation(m_pTransform->GetPosition(), D3DXVECTOR3(0, 0, m_vSpeed.z), 5, fTimeDelta))
			m_pTransform->Move(0, 0, m_vSpeed.z, 3, fTimeDelta);
		cout << fTimeDelta << endl;
		m_pTransform->Move(0, m_vSpeed.y - m_fTimeDelta*m_fTimeDelta*0.5f*0.0098f, 0 , 3, fTimeDelta);

		m_pTransform->RotationAxis(m_pTransform->GetRight(), D3DXToRadian(m_vAngle.x), fTimeDelta);		
		m_pTransform->RotationAxis(m_pTransform->GetUp(), D3DXToRadian(m_vAngle.y), fTimeDelta);	
		m_pTransform->RotationAxis(m_pTransform->GetLook(), D3DXToRadian(m_vAngle.z), fTimeDelta);

		if (m_pNaviMesh != nullptr)
			m_pNaviMesh->SetIndex(m_pTransform->GetPosition());
	}
	else
	{
		m_pTransform->RotationAxis(D3DXVECTOR3(0,1,0), D3DXToRadian(m_vAngle.x), fTimeDelta * 1.5f);
	}

	CTransform* pTransform = (CTransform*)CGameObjectMgr::GetInstance()->FindComponent(SCENESTATIC, L"PLAYER", L"TRANSFORM");
	if (pTransform == nullptr)
		return 0;

	D3DXVECTOR3 vDir = pTransform->GetPosition() - m_pTransform->GetPosition();
	float fLength = D3DXVec3Length(&vDir);
	
	if (m_fTimeDrop>0.3f && fLength <= 3.f)
	{	
		

		CPlayer* pPlayer = (CPlayer*)CGameObjectMgr::GetInstance()->FindGameObject(SCENESTATIC, L"PLAYER");
		if (pPlayer->GetPlayerInfo().iCurrMp >= pPlayer->GetPlayerInfo().iMaxMp)
			return _int();

		if (m_bFlag == false)
			m_bFlag = true;

		if (fLength <= 1.f)
		{
			pPlayer->AddCurrMp(m_eMana);
			D3DXVECTOR4 vPosition = D3DXVECTOR4(m_pTransform->GetPosition(), m_eMana);
			CGameObjectMgr::GetInstance()->AddObejct(SCENESTATIC, L"ITEM_EFFECT", SCENESTATIC, L"EFFECT", &vPosition);
			return -1;
		}


		D3DXVec3Normalize(&vDir, &vDir);

		m_pTransform->Move(vDir.x, vDir.y, vDir.z, 8, fTimeDelta);
		
	}

	return _int();
}

_int CManaToken::LateProgress(const _float & fTimeDelta)
{	
	float fHeight = m_pNaviMesh->ComputeHeight(m_pTransform->GetPosition());
	

	if (m_bFlag==false && m_pTransform->GetPosition().y <= fHeight + 0.35f)
	{
		m_pTransform->SetPosition(D3DXVECTOR3(m_pTransform->GetPosition().x, fHeight + 0.35f, m_pTransform->GetPosition().z));
		m_fTimeDelta = 0;
		m_vSpeed *= 0.5f;
		
		if (m_vSpeed.y <= 0.1f)
		{
			m_bFinish = true;			
		}
	}

	CGameObject::ComputeZ(m_pTransform->GetPosition());

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::NONALPHA, this)))
		return -1;

	return _int();
}

HRESULT CManaToken::Render()
{
	LPD3DXEFFECT pEffect = m_pShader->GetEffect();
	if (pEffect == nullptr)
		return E_FAIL;
	D3DXMATRIX matView, matProj;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matWorld", m_pTransform->GetWorldMatrix());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);
	pEffect->SetVector("g_vColor", &D3DXVECTOR4(m_vColor,1));

	pEffect->Begin(nullptr, 0);
	unsigned long iSubsetNum = m_pMeshStatic->GetSubsetNum();

	for (int i = 0; i < iSubsetNum; ++i)
	{
		m_pMeshStatic->SetShaderMeshTex(pEffect, i, "g_Texture", MESHTEXTURE::MESH_DIFFUSE);
		m_pTexture->SetTexture(pEffect, "g_FilterTexture", 0);

		pEffect->CommitChanges();
		pEffect->BeginPass(m_iShaderPass);
		m_pMeshStatic->Render(i);
		pEffect->EndPass();
	}
	pEffect->End();

	return NOERROR;
}



CGameObject * CManaToken::Clone(void * pArg)
{
	CManaToken*	pInstance = new CManaToken(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CManaToken Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CManaToken::Free()
{
	Safe_Release(m_pTexture);

	CItem::Free();
}

CManaToken * CManaToken::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CManaToken*	pInstance = new CManaToken(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CManaToken Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
