#pragma once
#include "Tower.h"
_BEGIN(Client)
class CGlowBall;
class CLightningBolt;
class CLightningTower :
	public CTower
{
private:
	int			m_iTargetNum = 2;
	float		m_fDamage = 1.f;
	
	float		m_fEffectCoolTime=0.f;

	CGlowBall*		m_pGlowBall = nullptr;
	vector<CLightningBolt*>		m_vecLightningBolt;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();

	HRESULT AttackChainLightning();
	bool FindEnemy(D3DXVECTOR3 _vPosition, vector<CGameObject*>* _TargetList ,CGameObject** pOut,float _fRange);

	explicit CLightningTower(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CLightningTower(const CLightningTower & rhs);
	virtual ~CLightningTower() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;

	static CLightningTower* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
};
_END
