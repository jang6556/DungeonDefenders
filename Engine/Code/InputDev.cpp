#include "..\Header\InputDev.h"


IMPLEMENT_SINGLETON(CInputDev)

HRESULT CInputDev::KeyBoard_Initialize(HWND hWnd)
{
	if (FAILED(m_SDK->CreateDevice(GUID_SysKeyboard, &m_pKeyBoard, nullptr)))
		return E_FAIL;

	if (FAILED(m_pKeyBoard->SetDataFormat(&c_dfDIKeyboard)))
		return E_FAIL;

	if (FAILED(m_pKeyBoard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
		return E_FAIL;

	if (FAILED(m_pKeyBoard->Acquire()))
		return E_FAIL;
}

HRESULT CInputDev::Mouse_Initialize(HWND hWnd)
{
	if (FAILED(m_SDK->CreateDevice(GUID_SysMouse, &m_pMouse, nullptr)))
		return E_FAIL;

	if (FAILED(m_pMouse->SetDataFormat(&c_dfDIMouse)))
		return E_FAIL;

	if (FAILED(m_pMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
		return E_FAIL;

	if (FAILED(m_pMouse->Acquire()))
		return E_FAIL;

	return NOERROR;
}

CInputDev::CInputDev()
{
}

HRESULT CInputDev::Initialize(HINSTANCE hInst, HWND hWnd)
{
	if(FAILED(DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_SDK, nullptr)))
		return E_FAIL;

	if (FAILED(Mouse_Initialize(hWnd)))
		return E_FAIL;

	if (FAILED(KeyBoard_Initialize(hWnd)))
		return E_FAIL;


	return NOERROR;
}

HRESULT CInputDev::SetInputDev()
{
	if (m_pKeyBoard == nullptr ||
		m_pMouse == nullptr)
		return E_FAIL;

	m_pKeyBoard->GetDeviceState(sizeof(KeyState), &KeyState);
	m_pMouse->GetDeviceState(sizeof(MouseState), &MouseState);

	return NOERROR;
}

void CInputDev::Free()
{
	Safe_Release(m_SDK);

	Safe_Release(m_pKeyBoard);
	Safe_Release(m_pMouse);
}
