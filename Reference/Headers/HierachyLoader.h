#pragma once
#include "Engine_Define.h"
#include "d3dx9anim.h"

_BEGIN(Engine)
class CHierachyLoader :
	public ID3DXAllocateHierarchy
{
private:
	LPDIRECT3DDEVICE9	m_pGraphicDevice;
	const TCHAR* m_pFilePath = nullptr;

	_uint	m_dwRef = 0;
	

	HRESULT Initialize(const TCHAR * pFilePath);
	HRESULT AllocateName(char** szDestName,const char* szSourName);
	HRESULT ChangeTextureFileName(TCHAR * pFilePath, TCHAR szSourName);
	CHierachyLoader(LPDIRECT3DDEVICE9	_m_pGraphicDevice);

	virtual ~CHierachyLoader() = default;
	
public:
	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame);
	STDMETHOD(CreateMeshContainer)(THIS_ LPCSTR Name, CONST D3DXMESHDATA *pMeshData, CONST D3DXMATERIAL *pMaterials, CONST D3DXEFFECTINSTANCE *pEffectInstances, DWORD NumMaterials, CONST DWORD *pAdjacency, LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER *ppNewMeshContainer);
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree);
	
	_ulong	AddRef();
	_ulong	Release();

	static CHierachyLoader* Create(LPDIRECT3DDEVICE9	_m_pGraphicDevice,const TCHAR* pFilePath);
	void Free();
	
};
_END
