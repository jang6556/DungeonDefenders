#include "stdafx.h"
#include "..\Header\LongStair.h"


_USING(Client)

HRESULT CLongStair::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	return NOERROR;
}

HRESULT CLongStair::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CLongStair::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"TRANSFORM", (CComponent**)&m_pTransform)))
		return E_FAIL;	

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADER", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"LONGSTAIR", (CComponent**)&m_pMeshStatic)))
		return E_FAIL;

	return NOERROR;
}

CLongStair::CLongStair(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CLongStair::CLongStair(const CLongStair & rhs)
	: CGameObject(rhs)
{
}

_int CLongStair::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CLongStair::LateProgress(const _float & fTimeDelta)
{
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::NONALPHA, this)))
		return -1;
	if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::DECAL_OBJECT, this)))
		return -1;
	return _int();
}

HRESULT CLongStair::Render()
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

CGameObject * CLongStair::Clone(void * pArg)
{
	CLongStair*	pInstance = new CLongStair(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CLongStair Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLongStair::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pShader);
	Safe_Release(m_pMeshStatic);
	CGameObject::Free();
}

CLongStair * CLongStair::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CLongStair*	pInstance = new CLongStair(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CLongStair Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
