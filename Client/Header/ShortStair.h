#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CShortStair :
	public CGameObject
{
private:
	CTransform*		m_pTransform = nullptr;
	CShader*		m_pShader = nullptr;
	CRenderer*		m_pRenderer = nullptr;
	CMeshStatic*	m_pMeshStatic = nullptr;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CShortStair(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CShortStair(const CShortStair & rhs);
	virtual ~CShortStair() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CShortStair* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);

};
_END
