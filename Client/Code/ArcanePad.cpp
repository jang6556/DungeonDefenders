#include "stdafx.h"
#include "..\Header\ArcanePad.h"
#include "..\Header\MagnusController.h"

_USING(Client)


HRESULT CArcanePad::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	return NOERROR;
}

HRESULT CArcanePad::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CArcanePad::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	m_pTransform->SetWorldMatrix(*(D3DXMATRIX*)pArg);

	MakeRoot(m_pTransform->GetPosition());
	
	m_MonsterList.push_back(MONSTER_KOBOLD);
	/*m_MonsterList.push_back(MONSTER_ARCHER);
	m_MonsterList.push_back(MONSTER_GOBLIN);	
	m_MonsterList.push_back(MONSTER_ARCHER);
	m_MonsterList.push_back(MONSTER_GOBLIN);*/

	m_pMonsterController= (CMagnusController*)CGameObjectMgr::GetInstance()->FindGameObject(SCENE_MAGNUS, L"CONTROLLER");
	if (m_pMonsterController == nullptr)
		return E_FAIL;

	m_pMonsterController->AddRef();
	m_pMonsterController->AddLinkNum();

	return NOERROR;
}

HRESULT CArcanePad::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADER", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"ARCANEPAD", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"NAVIMESH", (CComponent**)&m_pNaviMesh)))
		return E_FAIL;

	return NOERROR;
}

void CArcanePad::MakeRoot(D3DXVECTOR3 _vPosition)
{
	if (D3DXVec3Length(&_vPosition) < 1.f)
		return;

	vector<CMonSphere*>* pMonNavi = m_pNaviMesh->GetMonNavi();

	int iSize = pMonNavi->size();
	float fLength = 0.f;
	int iIndex = 0;
	
	for (int i = 0; i < iSize; ++i)
	{
		
		float fCompare = D3DXVec3Length(&((*pMonNavi)[i]->GetPosition() - _vPosition));

		if (fCompare == 0)
			continue;

		if (fLength == 0.f || fLength > fCompare)
		{
			bool bFlag=false;
			for (auto& iter : m_vecRoot)
			{
				if (iter == i)
					bFlag = true;
			}

			if (bFlag)
				continue;

			fLength = fCompare;
			iIndex = i;
		}
		
	}


		m_vecRoot.push_back(iIndex);



	MakeRoot((*pMonNavi)[iIndex]->GetPosition());
}

CArcanePad::CArcanePad(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CArcanePad::CArcanePad(const CArcanePad & rhs)
	: CGameObject(rhs)
{
}

_int CArcanePad::Progress(const _float & fTimeDelta)
{
	CGameObjectMgr* Objmgr = CGameObjectMgr::GetInstance();

	m_fTimeDelta += fTimeDelta;
	if (m_iCurrIndex < m_MonsterList.size() && m_fTimeDelta >= 6.f )
	{
		m_fTimeDelta = 0.f;

		m_pMonsterController->CreateMonster(m_pTransform->GetPosition(), m_vecRoot);
	}
	return _int();
}

_int CArcanePad::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::NONALPHA, this)))
		return -1;

	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::DECAL_OBJECT, this)))
		return -1;

	return _int();
}

HRESULT CArcanePad::Render()
{
	LPD3DXEFFECT pEffect = m_pShader->GetEffect();
	if (pEffect == nullptr)
		return E_FAIL;
	D3DXMATRIX  matView, matProj;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matWorld", m_pTransform->GetWorldMatrix());
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);

	pEffect->Begin(nullptr, 0);
	unsigned long iSubsetNum = m_pMeshStatic->GetSubsetNum();

	for (int i = 0; i < iSubsetNum; ++i)
	{
		m_pMeshStatic->SetShaderMeshTex(pEffect, i, "g_Texture", MESHTEXTURE::MESH_DIFFUSE);

		pEffect->CommitChanges();
		pEffect->BeginPass(0);
		m_pMeshStatic->Render(i);
		pEffect->EndPass();
	}
	pEffect->End();
	return NOERROR;
}

CGameObject * CArcanePad::Clone(void * pArg)
{
	CArcanePad*	pInstance = new CArcanePad(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CArcanePad Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CArcanePad::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pShader);
	Safe_Release(m_pMeshStatic);
	Safe_Release(m_pNaviMesh);
	Safe_Release(m_pMonsterController);
	CGameObject::Free();
}

CArcanePad * CArcanePad::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CArcanePad*	pInstance = new CArcanePad(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CArcanePad Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
