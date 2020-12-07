#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CItem :
	public CGameObject
{
protected:
	CTransform*		m_pTransform = nullptr;
	CShader*		m_pShader = nullptr;
	CRenderer*		m_pRenderer = nullptr;
	CMeshStatic*	m_pMeshStatic = nullptr;
	CNaviMesh*		m_pNaviMesh = nullptr;
	_uint			m_iShaderPass = 0;

	float			m_fTimeDelta = 0.f;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();


	explicit CItem(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CItem(const CItem & rhs);
	virtual ~CItem() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual void Free() override;
};
_END
