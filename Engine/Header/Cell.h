
#include "Base.h"

_BEGIN(Engine)
class _DLLEXPORTS CCell :
	public CBase
{
public:
	enum POINT    { POINT_A, POINT_B, POINT_C, POINT_END };
	enum EDGE	  { EDGE_AB, EDGE_BC, EDGE_CA, EDGE_END  };
	enum NEIGHBOR { NEIGHBOR_AB, NEIGHBOR_BC, NEIGHBOR_CA, NEIGHBOR_END };
private:
	LPDIRECT3DDEVICE9	m_pGraphicDevice;
	LPD3DXLINE			m_pLine;

	D3DXVECTOR3			m_vPoint[POINT_END];
	D3DXVECTOR3			m_vEdge[EDGE_END];
	CCell*				m_pNeightbor[NEIGHBOR_END];

	_uint				m_iIndex;

	HRESULT	 Initialize(D3DXVECTOR3 _PointA, D3DXVECTOR3 _PointB, D3DXVECTOR3 _PointC, _uint _iIndex);

	explicit CCell(LPDIRECT3DDEVICE9	_m_pGraphicDevice);
	virtual ~CCell() = default;
public:

	bool	IsNeighbor(const D3DXVECTOR3* pFirst, const D3DXVECTOR3* pSecond, CCell* pCell);
	void	SetNeighbor(NEIGHBOR eType, CCell* pInstance) { if(pInstance!=nullptr) m_pNeightbor[eType] = pInstance; }
	const	D3DXVECTOR3	GetPoint(POINT eType) { return m_vPoint[eType]; }
	bool	IsIn(D3DXVECTOR3 _vPosition,_uint* iOutputEdge);
	CCell*	GetNeighbor(NEIGHBOR eType) { return m_pNeightbor[eType]; }
	_uint	GetIndex() { return m_iIndex; }

	HRESULT Render();
	virtual void Free();

	static CCell* Create(LPDIRECT3DDEVICE9 _m_pGraphicDevice, D3DXVECTOR3 _PointA, D3DXVECTOR3 _PointB, D3DXVECTOR3 _PointC, _uint _iIndex);
};
_END