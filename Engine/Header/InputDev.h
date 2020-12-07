#pragma once
#include "Base.h"
_BEGIN(Engine)
class _DLLEXPORTS CInputDev final :
	public CBase
{
	DECLARE_SINGLETON(CInputDev)
private:
	LPDIRECTINPUT8				m_SDK = nullptr;
	LPDIRECTINPUTDEVICE8		m_pMouse = nullptr;
	LPDIRECTINPUTDEVICE8		m_pKeyBoard = nullptr;

	_byte						KeyState[256];
	_DIMOUSESTATE				MouseState;

	HRESULT	KeyBoard_Initialize(HWND hWnd);
	HRESULT	Mouse_Initialize(HWND hWnd);

	explicit CInputDev();
	virtual ~CInputDev() = default;

public:
	enum MOUSEBUTTON { DIM_LBUTTON, DIM_RBUTTON, DIM_WHEELBUTTON, DIM_XBUTTON };
	enum MOUSEMOVE { DIMM_X, DIMM_Y, DIMM_WHEEL };

	HRESULT	Initialize(HINSTANCE hInst,HWND hWnd);
	HRESULT	SetInputDev();

	long GetMouseMove(MOUSEMOVE eMouseMove)
	{
		return *((long*)&MouseState + eMouseMove);
	}

	virtual void Free();
};
_END
