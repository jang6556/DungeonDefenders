#pragma once
#include "StaticMapObject.h"

_BEGIN(Client)
class CLightObject :
	public CStaticMapObject
{
public:
	typedef struct tagLightSave
	{
		D3DXVECTOR3 vPosition;
		D3DXVECTOR3 vColor;
		float		fRange;

	}LIGHTDATA;

protected:
	list<LIGHTDATA*> m_pLightList;

	virtual HRESULT Initialize() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT	AddComponent();

	HRESULT LoadLightData(TCHAR * szFilePath);
	HRESULT SetPointLight(SCENEID eType);

	explicit CLightObject(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CLightObject(const CLightObject & rhs);
	virtual ~CLightObject() = default;
public:
	virtual _int	Progress(const _float& fTimeDelta) override;
	virtual _int	LateProgress(const _float& fTimeDelta) override;
	virtual HRESULT Render() override;

	virtual CGameObject* Clone(void* pArg = nullptr) override;

	virtual void Free() override;
};
_END
