#pragma once
#include "GameObject.h"

_BEGIN(Engine)
class _DLLEXPORTS CCameraObject :
	public CGameObject
{
public:
	typedef struct tagCameraInfo {

		D3DXVECTOR3 vEye;
		D3DXVECTOR3 vAt;
		D3DXVECTOR3 vAxisY;

		_float		fFovY;
		_float		fAspect;
		_float		fNear;
		_float		fFar;

		tagCameraInfo() {}

		tagCameraInfo(const D3DXVECTOR3 _vEye,
			const D3DXVECTOR3 _vAt,
			const D3DXVECTOR3 _vAxisY,
			_float _fFovY,
			_float	_fAspect,
			_float _fNear,
			_float _fFar)
			:vEye(_vEye), vAt(_vAt), vAxisY(_vAxisY), fFovY(_fFovY), fAspect(_fAspect), fNear(_fNear), fFar(_fFar)
		{

		}

	}CAMERAINFO;
protected:
	CAMERAINFO		m_pCamerInfo;

	explicit CCameraObject(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CCameraObject(const CCameraObject& rhs);
	virtual ~CCameraObject() = default;

public:
	virtual HRESULT Initialize();
	virtual HRESULT Initialize_Prototype();
	virtual _int	Progress(const _float& fTimeDelta);
	virtual _int	LateProgress(const _float& fTimeDelta);
	virtual HRESULT Render();


	virtual CGameObject* Clone(void* pArg = nullptr);
	virtual void	Free();



};
_END
