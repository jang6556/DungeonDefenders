#pragma once
#include "Effect.h"

_BEGIN(Client)
class CSharpBulletExplosive :
	public CEffect
{
private:
	HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();


	explicit CSharpBulletExplosive(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CSharpBulletExplosive(const CSharpBulletExplosive & rhs);
	virtual ~CSharpBulletExplosive() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CSharpBulletExplosive* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);

};
_END
