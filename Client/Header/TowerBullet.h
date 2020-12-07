#pragma once
#include "GameObject.h"

_BEGIN(Client)
class CMonster;
class CTowerBullet :
	public CGameObject
{
public:
	typedef struct tagTowerBulletInfo
	{
		D3DXVECTOR3 vPosition;
		D3DXVECTOR3 vDir;

		tagTowerBulletInfo(){}
		
		tagTowerBulletInfo(D3DXVECTOR3 _vPosition, D3DXVECTOR3 _vDir)
			:vPosition(_vPosition), vDir(_vDir)
		{

		}

	}TOWER_BULLET_INFO;
protected:
	TOWER_BULLET_INFO		m_tBulletInfo;

	CTransform*		m_pTransform = nullptr;
	CShader*		m_pShader = nullptr;
	CRenderer*		m_pRenderer = nullptr;
	CMeshStatic*	m_pMeshStatic = nullptr;
	CCollider*		m_pCollider = nullptr;	

	CCollider*		m_pColliderExplosion = nullptr;

	float			m_fTimeDelta = 0.f;
	_uint			m_iShaderPass=0;
	_float			m_fDamge;


	bool    bCheckCollision();
	int		Explosion();


	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Initialize_Prototype() override;
	HRESULT	AddComponent();
	
	explicit CTowerBullet(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CTowerBullet(const CTowerBullet & rhs);
	virtual ~CTowerBullet() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;
};
_END

