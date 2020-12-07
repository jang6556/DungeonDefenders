#pragma once
#include "BuildObject.h"

_BEGIN(Client)
class CDecal;
class CPresentBomb :
	public CBuildObject
{
private:		
	float	m_fTimer=0.f;
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	CDecal*	m_pDecal = nullptr;

	explicit CPresentBomb(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CPresentBomb(const CPresentBomb & rhs);
	virtual ~CPresentBomb() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;
	virtual HRESULT RenderShadow() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CPresentBomb* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
