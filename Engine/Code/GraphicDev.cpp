
#include "../Header/GraphicDev.h"

_USING(Engine)

IMPLEMENT_SINGLETON(CGraphicDev)

void CGraphicDev::Free()
{
	int test = Safe_Release(m_pDevice);
	if (0 != test)
	{	
		_MSGBOX("m_pGraphic_Device Release Failed");
	}
	if (0 != Safe_Release(m_pSDK))
	{	
		_MSGBOX("m_pSDK Release Failed");
	}

}

CGraphicDev::CGraphicDev()
{
}

HRESULT CGraphicDev::Initialize(HWND _g_hWnd, const _uint iWINCX, const _uint iWINCY, LPDIRECT3DDEVICE9* ppGraphicDev)
{
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION); // ��ü���� �İ�ü �Ҵ��Լ�

	D3DCAPS9		DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		//MessageBox(NULL, L"��ġ ��������", L"System Error", NULL);
		return E_FAIL;
	}

	DWORD		vp;

	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	vp |= D3DCREATE_MULTITHREADED;

	D3DPRESENT_PARAMETERS		d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));


	///////////////////////////////////////////////////////////////////
	d3dpp.BackBufferWidth = iWINCX;
	d3dpp.BackBufferHeight = iWINCY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = _g_hWnd;

	d3dpp.Windowed = TRUE;	 // â ���� ��üȭ�� ����		

	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	///////////////////////////////////////////////////////////////////
	

	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _g_hWnd, vp, &d3dpp, &m_pDevice)))
	{
		_MSGBOX("����̽� ��ġ ���� ����");
		return E_FAIL;
	}

	if (ppGraphicDev != nullptr)
	{
		*ppGraphicDev = m_pDevice;
		m_pDevice->AddRef();
	}
	
	
	return S_OK;
}




void CGraphicDev::Render_Begin(void)
{
	m_pDevice->Clear(0,	  // ����� ���� ��Ʈ�� ����
					NULL, // ��Ʈ�� �ּ� ��
					D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
					D3DCOLOR_ARGB(255, 0, 0, 1), // ������� ����
					1.f, // Ÿ���� ����� �� ��, z������ �ʱ�ȭ ��
					0);	 // Ÿ���� ����� �� ��, ���ٽ� ������ �ʱ�ȭ ��

	m_pDevice->BeginScene();
	
}

void CGraphicDev::Render_End(void)
{
	
	m_pDevice->EndScene();
	m_pDevice->Present(NULL, NULL, NULL, NULL);
	// 1, 2���� : ��Ʈ �ְ� ��, �� ���� ������ŭ Ȯ�� / ��Ҹ� ���� �� ����(EX : 1���� ���� ��Ʈ, 2���� ū ��Ʈ�� ������ Ȯ�� ������ ����)
	// 3���� : ��� ������ ���� ���ΰ�
	// 4���� : �������� ���� ���� �����ϴ� ����

}
