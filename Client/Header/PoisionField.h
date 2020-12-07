#pragma once
#include "BuildObject.h"

_BEGIN(Client)
class CFogEffect;
class CDecal;
class CPoisionField :
	public CBuildObject
{
private:
	CFogEffect*		m_pFogEffect = nullptr;	
	float			m_fEffect = 0.f;
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	CDecal*	m_pDecal = nullptr;

	explicit CPoisionField(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CPoisionField(const CPoisionField & rhs);
	virtual ~CPoisionField() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CPoisionField* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
