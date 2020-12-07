#pragma once
#include "Component.h"

_BEGIN(Engine)
class _DLLEXPORTS CShader :
	public CComponent
{
private:
	LPD3DXEFFECT		m_pEffect = nullptr;

	HRESULT Initialize(TCHAR* szFilePath);

	explicit	CShader(LPDIRECT3DDEVICE9	_m_pGraphicDevice);
	explicit	CShader(const CShader& rhs);
	virtual ~CShader() = default;
public:
	HRESULT LoadShaderFile(TCHAR* szFileName);
	LPD3DXEFFECT	GetEffect() { return m_pEffect; }

	static CShader* Create(LPDIRECT3DDEVICE9	_m_pGraphicDevice,TCHAR* szFilePath);
	virtual CComponent* Clone();
	void virtual Free();
};
_END
