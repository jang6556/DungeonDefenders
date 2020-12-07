#pragma once
#include "Component.h"



_BEGIN(Engine)
class CHierachyLoader;
class CAnimaitionCtrl;
class _DLLEXPORTS CMeshDynamic :
	public CComponent
{
private:
	CHierachyLoader*			m_pLoader		= nullptr;
	D3DXFRAME*					m_pRootFrame	= nullptr;
	vector<LPEXMESHCONTAINER>	m_MeshContainer;
	D3DXMATRIX					m_matPivot;
	CAnimaitionCtrl*			m_pAniCtrl		= nullptr;	

	HRESULT Initialize(const TCHAR* szFilePath, const TCHAR* szFileName);
	
	HRESULT UpdateCombinedMatrix(D3DXFRAME* pFrame, const D3DXMATRIX* matParents);
	HRESULT SetUpCombinedMatrixPointer(D3DXFRAME* pFrame);


	explicit	CMeshDynamic(LPDIRECT3DDEVICE9	_m_pGraphicDevice);
	explicit	CMeshDynamic(const CMeshDynamic& rhs);
	virtual		~CMeshDynamic() = default;
public:	
	HRESULT	SetShaderMeshTex(LPD3DXEFFECT pEffect, int iContainerNum, const long& SubsetNum, const char* ShaderTexName, MESHTEXTURE::MESHTEXTYPE eType);
	HRESULT	Render(int iContainerNum, int iSubsetNum);
	HRESULT UpdateSkinnedMesh(int iContainerNum);

	int		GetMaterialNum(int iContainerNum) { return m_MeshContainer[iContainerNum]->NumMaterials; }
	HRESULT SetAnimationSet(int iIndex);
	HRESULT PlayAnimation(const float& fTimeDelta);
	bool	AnimationEnd(float fOffset = 0.f);
	double  GetTimeTrack();
	
	D3DXMATRIX*	GetBoneMatrix(TCHAR* szBoneName);

	static CMeshDynamic* Create(LPDIRECT3DDEVICE9	_m_pGraphicDevice, const TCHAR* szFilePath, const TCHAR* szFileName);
	virtual CComponent* Clone();
	void virtual Free();


};
_END
