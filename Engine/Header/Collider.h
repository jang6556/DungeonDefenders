#pragma once
#include "Component.h"

_BEGIN(Engine)
class CShader;
class _DLLEXPORTS CCollider :
	public CComponent
{
public:
	enum COLLIDER { AABB, OBB,  SPHERE, COLLIDEREND };
	typedef struct tagColliderInfo
	{
		D3DXMATRIX	m_WorldMatrix;
		D3DXMATRIX* m_pParentsTransform;
		D3DXMATRIX* m_pBoneMatirx;
	}COLLIDERINFO;

	typedef struct tagObbInfo
	{
		D3DXVECTOR3 vPosition;
		D3DXVECTOR3 vPoint[8];
		D3DXVECTOR3 vLine[3];
		D3DXVECTOR3 vAspectNormal[3];
	}OBBINFO;



private:
	COLLIDERINFO m_ColliderInfo;
	COLLIDER     m_ColliderType;
	OBBINFO*	 m_pObbInfo = nullptr;
	D3DXMATRIX	 m_matWorld;
	D3DXVECTOR3  m_vMin;
	D3DXVECTOR3  m_vMax;
	LPD3DXMESH   m_pMesh	= nullptr;
	CShader*	 m_pShader = nullptr;
	bool		 m_IsCollision = false;
	bool		 m_IsRender = false;

	HRESULT			Initialize();
	HRESULT			Initialize_Prototype(COLLIDER eType);
	D3DXMATRIX		ComputeAABB(D3DXMATRIX matInput);
	D3DXMATRIX		ComputeOBB(D3DXMATRIX matInput);
	HRESULT			CreateObbInfo();
	void			ComputeMatrix(OBBINFO* _pObbInfo, D3DXMATRIX* _matWorld);


	explicit	CCollider(LPDIRECT3DDEVICE9	_m_pGraphicDevice);
	explicit	CCollider(const CCollider& rhs);
	virtual		~CCollider() = default;

public:
	HRESULT Render();	
	HRESULT SetBoneMatrix(D3DXMATRIX* pParentsMatirx, D3DXMATRIX* pWorldMatirx = nullptr,D3DXMATRIX* pBoneMatirx = nullptr);
	void	SetIsRender(bool IsRender) { m_IsRender = IsRender; }

	HRESULT ChangeColliderType(COLLIDER eType);
	COLLIDERINFO GetColliderInfo() { return m_ColliderInfo; }
	bool	GetIsRender() { return m_IsRender; }
	COLLIDER GetColliderType() { return m_ColliderType; }  
	D3DXMATRIX* GetWorldMatrix();

	bool	GetIsCollision() { return m_IsCollision; }
	void	SetIsCollision(bool _IsCollision) {	m_IsCollision = _IsCollision; }

	D3DXVECTOR3	GetMin() { return m_vMin; }
	D3DXVECTOR3	GetMax() { return m_vMax; }

	bool	CheckCollision_SPHERE(CCollider* pInputCollider);
	bool	CheckCollision_AABB(CCollider* pInputCollider);
	bool	CheckCollision_OBB(CCollider* pInputCollider);

	static CCollider* Create(LPDIRECT3DDEVICE9	_m_pGraphicDevice, COLLIDER eType);
	virtual CComponent* Clone();
	void virtual Free();
};
_END
