#include "stdafx.h"
#include "..\Header\VerticalBarBackGround.h"


_USING(Client)

HRESULT CVerticalBarBackGround::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	m_pTransform->Scaling(55, 110, 0);
	m_pTransform->SetPosition(D3DXVECTOR3(-545.f, -260, 0));

	return NOERROR;
}

HRESULT CVerticalBarBackGround::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CVerticalBarBackGround::AddComponent()
{
	if (FAILED(CPlayerUI::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADERUI", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"VERTICALBAR", (CComponent**)&m_Texture)))
		return E_FAIL;

	return NOERROR;
	
}

CVerticalBarBackGround::CVerticalBarBackGround(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CPlayerUI(_m_pGraphicDev)
{
}

CVerticalBarBackGround::CVerticalBarBackGround(const CVerticalBarBackGround & rhs)
	: CPlayerUI(rhs)
{
}

_int CVerticalBarBackGround::Progress(const _float & fTimeDelta)
{
	return _int(CPlayerUI::Progress(fTimeDelta));
}

_int CVerticalBarBackGround::LateProgress(const _float & fTimeDelta)
{
	return _int(CPlayerUI::LateProgress(fTimeDelta));
}

HRESULT CVerticalBarBackGround::Render()
{
	return CPlayerUI::Render();
}

CGameObject * CVerticalBarBackGround::Clone(void * pArg)
{
	CVerticalBarBackGround*	pInstance = new CVerticalBarBackGround(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CVerticalBarBackGround Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CVerticalBarBackGround::Free()
{
	CPlayerUI::Free();
}

CVerticalBarBackGround * CVerticalBarBackGround::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CVerticalBarBackGround*	pInstance = new CVerticalBarBackGround(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CVerticalBarBackGround Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
