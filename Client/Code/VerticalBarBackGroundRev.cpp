#include "stdafx.h"
#include "..\Header\VerticalBarBackGroundRev.h"

_USING(Client)


HRESULT CVerticalBarBackGroundRev::Initialize()
{
	if (FAILED(AddComponent()))
		return E_FAIL;


	m_pTransform->Scaling(-55, 110, 0);
	m_pTransform->SetPosition(D3DXVECTOR3(-600.f, -260, 0));
	
	return NOERROR;
}

HRESULT CVerticalBarBackGroundRev::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CVerticalBarBackGroundRev::AddComponent()
{
	if (FAILED(CPlayerUI::AddComponent()))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"SHADERUI", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"VERTICALBAR", (CComponent**)&m_Texture)))
		return E_FAIL;

	return NOERROR;
}

CVerticalBarBackGroundRev::CVerticalBarBackGroundRev(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CPlayerUI(_m_pGraphicDev)
{
}

CVerticalBarBackGroundRev::CVerticalBarBackGroundRev(const CVerticalBarBackGroundRev & rhs)
	: CPlayerUI(rhs)
{
}

_int CVerticalBarBackGroundRev::Progress(const _float & fTimeDelta)
{
	
	return _int(CPlayerUI::Progress(fTimeDelta));
}

_int CVerticalBarBackGroundRev::LateProgress(const _float & fTimeDelta)
{
	return _int(CPlayerUI::LateProgress(fTimeDelta));
}

HRESULT CVerticalBarBackGroundRev::Render()
{
	return CPlayerUI::Render();
}

CGameObject * CVerticalBarBackGroundRev::Clone(void * pArg)
{
	CVerticalBarBackGroundRev*	pInstance = new CVerticalBarBackGroundRev(*this);

	if (FAILED(pInstance->Initialize()))
	{
		_MSGBOX("CVerticalBarBackGroundRev Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CVerticalBarBackGroundRev::Free()
{
	CPlayerUI::Free();
}

CVerticalBarBackGroundRev * CVerticalBarBackGroundRev::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CVerticalBarBackGroundRev*	pInstance = new CVerticalBarBackGroundRev(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CVerticalBarBackGroundRev Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
