#pragma once
#include "Component.h"

_BEGIN(Engine)
class _DLLEXPORTS CTransform final :
	public CComponent
{
private:
	D3DXMATRIX	matWorld;

	explicit CTransform(LPDIRECT3DDEVICE9	_m_pGraphicDev);
	explicit CTransform(const CTransform&	rhs);
	virtual ~CTransform() = default;

public:
	virtual HRESULT Initialize() override;

	HRESULT Scaling(const float& fX, const float& fY, const float& fZ);
	HRESULT Scaling(const float& fX, const float& fY, const float& fZ, const _float& fTimeDelta);
	HRESULT Rotation(const float& fX, const float& fY, const float& fZ);
	HRESULT RotationX(_float _Radian,const _float& fTimeDelta);
	HRESULT RotationY(_float _Radian,const _float& fTimeDelta);
	HRESULT RotationAxis(D3DXVECTOR3 vAxis, _float _Radian, const _float& fTimeDelta);
	HRESULT Move(const float& fX, const float& fY, const float& fZ, const float & fSpeed, const _float & fTimeDelta);
	HRESULT MoveStraight(const float& fSpeed, const _float& fTimeDelta);
	HRESULT MoveSide(const float& fSpeed, const _float& fTimeDelta);

	HRESULT SetRight(D3DXVECTOR3 _vRight);
	HRESULT SetUp(D3DXVECTOR3 _vUp);
	HRESULT SetLook(D3DXVECTOR3 _vLook);
	HRESULT SetPosition(D3DXVECTOR3 _vPosition);
	void SetWorldMatrix(D3DXMATRIX	_matWorld) { matWorld = _matWorld; }

	D3DXVECTOR3 GetRight();
	D3DXVECTOR3 GetUp();
	D3DXVECTOR3 GetLook();
	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetScale();

	D3DXMATRIX* GetWorldMatrix() { return &matWorld; }

	HRESULT SetTransform();

	static CTransform* Create(LPDIRECT3DDEVICE9	_m_pGraphicDev);
	virtual CComponent* Clone();
	virtual void Free() override;
};
_END
