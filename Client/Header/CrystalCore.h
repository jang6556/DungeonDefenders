#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CCrystalCore :
	public CGameObject
{
private:
	CTransform*				m_pTransform = nullptr;
	CShader*				m_pShader = nullptr;	
	CMeshStatic*			m_pMeshStatic = nullptr;
	

	virtual HRESULT Initialize() override;
	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CCrystalCore(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CCrystalCore(const CCrystalCore & rhs);
	virtual ~CCrystalCore() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;
	virtual HRESULT RenderShadow() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CCrystalCore* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
