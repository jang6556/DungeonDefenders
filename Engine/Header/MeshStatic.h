#pragma once
#include "Component.h"
_BEGIN(Engine)
class _DLLEXPORTS CMeshStatic :
	public CComponent
{
private:
	LPD3DXMESH		m_pMesh = nullptr;
	LPD3DXBUFFER	m_pMaterials = nullptr;
	LPD3DXBUFFER	m_pAdsjacency = nullptr;
	unsigned long	m_iSubSetNum = 0;

	MESHTEXTURE*	m_pMeshTexture = nullptr;
	D3DXMATERIAL*	m_pSubsetMaterial = nullptr;

	HRESULT Initialize(TCHAR* szFilePath, TCHAR* szFileName);
	HRESULT	ChangeFileName(TCHAR* szFileName, TCHAR szText);

	explicit CMeshStatic(LPDIRECT3DDEVICE9	_m_pGraphicDevice);
	explicit CMeshStatic(const CMeshStatic& rhs);
	virtual ~CMeshStatic() = default;
public:	
	HRESULT	SetShaderMeshTex(LPD3DXEFFECT pEffect, const long& SubsetNum, const char* ShaderTexName, MESHTEXTURE::MESHTEXTYPE eType);
	HRESULT	Render(int iSubsetNum);
	unsigned long GetSubsetNum() const { return m_iSubSetNum; }

	static CMeshStatic* Create(LPDIRECT3DDEVICE9	_m_pGraphicDevice,TCHAR* szFilePath, TCHAR* szFileName);
	virtual CComponent* Clone();
	void virtual Free();
};
_END
