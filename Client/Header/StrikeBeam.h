#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CStrikeBeam :
	public CGameObject
{
private:
	CTransform*				m_pTransform = nullptr;
	CShader*				m_pShader = nullptr;
	CMeshStatic*			m_pMeshStatic = nullptr;
	CRenderer*				m_pRenderer = nullptr;

	float					m_fScale = 0.f;
	bool					m_IsRender = false;

	float					m_fTimeDelta = 0.f;

	virtual HRESULT Initialize() override;
	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	explicit CStrikeBeam(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CStrikeBeam(const CStrikeBeam & rhs);
	virtual ~CStrikeBeam() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	HRESULT SetTarget(POS_TARGET vPosTarget, bool IsRender = true);
	void	OffRender() { m_IsRender = false; }

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CStrikeBeam* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
