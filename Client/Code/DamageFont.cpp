#include "stdafx.h"
#include "..\Header\DamageFont.h"


_USING(Client)

HRESULT CDamageFont::Initialize()
{
	return NOERROR;
}

HRESULT CDamageFont::Initialize(void * pArg)
{
	if (FAILED(AddComponent()))
		return E_FAIL;

	D3DXVECTOR4 iDamage = *(D3DXVECTOR4*)pArg;

	if (FAILED(CreateDamageBuffer(iDamage)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CDamageFont::Initialize_Prototype()
{
	return NOERROR;
}

HRESULT CDamageFont::AddComponent()
{
	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"RENDERER", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	if (FAILED(CGameObject::AddComponent(SCENESTATIC, L"FRUSTUM", (CComponent**)&m_pFrustum)))
		return E_FAIL;

	return NOERROR;
}

HRESULT CDamageFont::CreateDamageBuffer(D3DXVECTOR4 _iDamage)
{
	D3DXVECTOR4 vPosition = _iDamage;
	m_vPosition = D3DXVECTOR3(vPosition.x, vPosition.y, vPosition.z);

	vPosition.x += (float)(rand() % 100)/100.f - 0.5f;
	vPosition.y += (float)(rand() % 100)/100.f - 0.5f;
	vPosition.z += (float)(rand() % 100)/100.f - 0.5f;

	vPosition.w *= -1.f;
	int iDamage = vPosition.w;

	int iSize = 0;

	for (int i = 0; i < 5; ++i)
	{
		int iNum = vPosition.w / (pow(10,(4 - i)));
		if (iNum > 0)
		{
			iSize = 5 - i;
			break;
		}
	}

	for (int i = 0; i < iSize; ++i)
	{
		switch (iSize%2)
		{
		case 0:
			vPosition.w = GetNum(iDamage, iSize, i);
			m_FontList.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"DAMAGE_BUFFER", &vPosition));
			dynamic_cast<CDamageBuffer*>(m_FontList.back())->Set_Type_Pos(CDamageBuffer::TYPE_EVEN, CDamageBuffer::NUM_POS((iSize / 2 +1 - i)));
			break;
		case 1:	
			vPosition.w = GetNum(iDamage, iSize, i);
			m_FontList.push_back(CGameObjectMgr::GetInstance()->GetGameObject(SCENESTATIC, L"DAMAGE_BUFFER", &vPosition));
			dynamic_cast<CDamageBuffer*>(m_FontList.back())->Set_Type_Pos(CDamageBuffer::TYPE_ODD, CDamageBuffer::NUM_POS((iSize/2 + 2 - i)));
			break;
		}
	}
	
	m_FontList.reverse();

	return NOERROR;
}

int CDamageFont::GetNum(float fNum, int iSize, int iPos)
{
	int iNum = fNum;

	for (int i = 0; i < iPos; ++i)
	{
		int iPow = pow(10, (iSize - i - 1));
		iNum %= iPow;
	}	

	return iNum /= pow(10, (iSize - iPos - 1));
}

CDamageFont::CDamageFont(LPDIRECT3DDEVICE9 _m_pGraphicDev)
	:CGameObject(_m_pGraphicDev)
{
}

CDamageFont::CDamageFont(const CDamageFont & rhs)
	: CGameObject(rhs)
{
}

_int CDamageFont::Progress(const _float & fTimeDelta)
{
	m_fTimeDelta += fTimeDelta;
	if (m_fTimeDelta >= 0.5f)
		return -1;

	for (auto& iter : m_FontList)
		iter->Progress(fTimeDelta);

	return _int();
}

_int CDamageFont::LateProgress(const _float & fTimeDelta)
{
	for (auto& iter : m_FontList)
		iter->LateProgress(fTimeDelta);

	if (m_pFrustum->IsInFrustumLight(m_vPosition, 2) == true)
	{
		if (FAILED(m_pRenderer->AddRenderGroup(CRenderer::UI, this)))
			return -1;
	}

	return _int();
}

HRESULT CDamageFont::Render()
{
	for (auto& iter : m_FontList)
		iter->Render();

	return NOERROR;
}

CGameObject * CDamageFont::Clone(void * pArg)
{
	CDamageFont*	pInstance = new CDamageFont(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		_MSGBOX("CDamageFont Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CDamageFont::Free()
{
	Safe_Release(m_pRenderer);
	Safe_Release(m_pFrustum);
	
	for (auto& iter : m_FontList)
		Safe_Release(iter);

	m_FontList.clear();

	CGameObject::Free();
}

CDamageFont * CDamageFont::Create(LPDIRECT3DDEVICE9 _m_pGraphicDev)
{
	CDamageFont*	pInstance = new CDamageFont(_m_pGraphicDev);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		_MSGBOX("CDamageFont Created Failed");
		Safe_Release(pInstance);
	}
	return pInstance;
}
