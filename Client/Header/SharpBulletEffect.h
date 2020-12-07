#pragma once
#include "Effect.h"

_BEGIN(Client)
class CSharpBulletEffect :
	public CEffect
{
private:
	CTransform* m_pParentTransform = nullptr;
	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CSharpBulletEffect(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CSharpBulletEffect(const CSharpBulletEffect & rhs);
	virtual ~CSharpBulletEffect() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CSharpBulletEffect* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END