#pragma once
#include "Component.h"

_BEGIN(Engine)
class CCell;
class CMonSphere;
class _DLLEXPORTS CNaviMesh :
	public CComponent
{
private:
	vector<CCell*>		m_pCell_Vector;
	vector<CMonSphere*> m_MonNavi_Vector;
	_uint				m_iCurrnet_Index = 0;

	virtual HRESULT Initialize(const TCHAR*	szFileName, const TCHAR* szMonFileName);
	

	explicit CNaviMesh(LPDIRECT3DDEVICE9	_m_pGraphicDev);
	explicit CNaviMesh(const CNaviMesh& rhs);
	virtual ~CNaviMesh() = default;
public:	
	virtual HRESULT Render();	

	void	SetIndex(D3DXVECTOR3 _vPosition);
	bool	MoveNavigation(D3DXVECTOR3 _vPosition, D3DXVECTOR3 _vDir,float fSpeed, const float& fTimeDelta);
	float	ComputeHeight(D3DXVECTOR3 _vPosition);
	float	GetHeight(D3DXVECTOR3 _vPosition);
	bool	NaviMeshPicking(POINT ptMouse, D3DXVECTOR3* pOut);
	_uint	GetCurrIndex() { return m_iCurrnet_Index; }
	vector<CMonSphere*>*	GetMonNavi() { return &m_MonNavi_Vector; }
	D3DXVECTOR3				GetPosition(int _iIndex);

	static CNaviMesh* Create(LPDIRECT3DDEVICE9	_m_pGraphicDev,const TCHAR*	szFileName, const TCHAR* szMonFileName);
	virtual CComponent* Clone();
	virtual void Free();
};
_END
