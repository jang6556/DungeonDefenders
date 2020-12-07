#pragma once
#include "VIBuffer.h"
class _DLLEXPORTS CTerrain :
	public CVIBuffer
{
private:
	explicit CTerrain(LPDIRECT3DDEVICE9	_m_pGraphicDev);
	explicit CTerrain(const CTerrain& rhs);
	virtual ~CTerrain() = default;
public:
	virtual HRESULT Initialize();
	virtual _int	Progress(const _float& fTimeDelta);
	virtual _int	LateProgress(const _float& fTimeDelta);
	virtual HRESULT Render(CTransform* pTransform=nullptr);

	static CTerrain* Create(LPDIRECT3DDEVICE9	_m_pGraphicDev);
	virtual CComponent* Clone();
	virtual void Free();
};

