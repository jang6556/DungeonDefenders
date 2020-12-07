#pragma once
#include "GameObject.h"


_BEGIN(Client)
class CCrossBow :
	public CGameObject
{
private:
	CMeshDynamic*	m_pPlayerBone = nullptr;
	CTransform*		m_pPlayerWorld = nullptr;
	CTransform*		m_pTransform = nullptr;
	CShader*		m_pShader = nullptr;
	CRenderer*		m_pRenderer = nullptr;
	CMeshStatic*	m_pMeshStatic = nullptr;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CCrossBow(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CCrossBow(const CCrossBow & rhs);
	virtual ~CCrossBow() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;
	virtual HRESULT RenderShadow() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CCrossBow* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
