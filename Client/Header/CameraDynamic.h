#pragma once
#include "CameraObject.h"
#include "Transform.h"
#include "InputDev.h"


_BEGIN(Client)
class CPlayer;
class CCameraDynamic :
	public CCameraObject
{
public:
	enum STATE { STATE_DEFAULT, STATE_DEFAULT_TO_BUILD,STATE_BUILD,STATE_BUILD_TO_DEFAULT,STATE_END };
private:
	STATE		m_eState = STATE_DEFAULT;
	CTransform* m_Transform = nullptr;
	CInputDev*	m_pInputDev = nullptr;
	CPlayer*	m_pPlayer = nullptr;

	float		m_fTimeDelta = 0.f;
	bool		m_bIsStatPanelRender = false;
	bool		m_bKeyFlag = false;

	explicit CCameraDynamic(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	explicit CCameraDynamic(const CCameraDynamic& rhs);
	virtual ~CCameraDynamic() = default;

	HRESULT SetViewMatrix();
	HRESULT SetProjectionMatrix();
	HRESULT AddComponent();
	
	void SetState();
	void ReSetCamera();
	void Default_Camera(const _float& fTimeDelta);
	void Default_To_Build_Camera(const _float& fTimeDelta);
	void Build_Camera(const _float& fTimeDelta);
	void Build_To_Default_Camera(const _float& fTimeDelta);
public:
	virtual HRESULT Initialize();
	virtual HRESULT Initialize_Prototype(void* pInfo);
	virtual _int	Progress(const _float& fTimeDelta);
	virtual _int	LateProgress(const _float& fTimeDelta);
	virtual HRESULT Render();


	static CCameraDynamic* Create(LPDIRECT3DDEVICE9 _m_pGraphicDev);
	virtual CGameObject* Clone(void* pInfo);
	virtual void	Free();
};
_END
