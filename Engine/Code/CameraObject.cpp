#include "..\Header\CameraObject.h"





CCameraObject::CCameraObject(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{

}

CCameraObject::CCameraObject(const CCameraObject & rhs)
	:CGameObject(rhs)
{

}

HRESULT CCameraObject::Initialize()
{
	return NOERROR;
}

HRESULT CCameraObject::Initialize_Prototype()
{
	return NOERROR;
}

_int CCameraObject::Progress(const _float & fTimeDelta)
{
	return _int();
}

_int CCameraObject::LateProgress(const _float & fTimeDelta)
{
	return _int();
}

HRESULT CCameraObject::Render()
{
	return NOERROR;
}

CGameObject * CCameraObject::Clone(void* pArg)
{
	return nullptr;
}

void CCameraObject::Free()
{
	CGameObject::Free();
}


