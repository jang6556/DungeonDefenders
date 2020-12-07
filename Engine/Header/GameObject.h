#pragma once
#include "Base.h"


_BEGIN(Engine)
class CComponent;
class _DLLEXPORTS CGameObject : public CBase
{
private:
	bool	m_IsClone;
	float	m_fZlength = 0.f;

	map<const _tchar*, list<CComponent*>>	m_MapComponent;
	typedef map<const _tchar*, list<CComponent*>*> MAPCOMPONENT;

protected:
	LPDIRECT3DDEVICE9 m_pGraphicDev = nullptr;
	vector<OBJCOLLIDERDATA*>		m_ColliderData;

	virtual HRESULT Initialize();
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT LoadColliderData(TCHAR* szFilePath);
	HRESULT   ComputeZ(D3DXVECTOR3 _vPosition);

	explicit CGameObject(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CGameObject(const CGameObject& rhs);
	virtual ~CGameObject() = default;


	HRESULT AddComponent(const _uint & iSceneId,const _tchar* szProtoTag,CComponent** pComponentOut, const _tchar* szComponentTag = nullptr);
public:
	virtual _int	Progress(const _float& fTimeDelta);
	virtual _int	LateProgress(const _float& fTimeDelta);
	virtual HRESULT Render();
	virtual HRESULT Render(LPD3DXEFFECT pEffect);
	virtual HRESULT RenderShadow();

	CComponent*	GetComponent(const _tchar* szProtoTag);
	float		GetZlength() { return m_fZlength; }
	bool		GetIsClone() { return m_IsClone; }

	list<CComponent*>*	FindComponentList(const _tchar* szProtoTag);

	virtual CGameObject* Clone(void* pArg = nullptr) = 0;
	virtual void	Free();

	
};
_END
