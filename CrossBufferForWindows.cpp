#include <iostream>
#include <Windows.h>
#include <d3d9.h>
#include "resource.h"
#include "Main.h"
using namespace std;

IDirect3D9* pDirect3D;
IDirect3DDevice9* pDevice;
BOOL FirstTimeRunning = TRUE;


LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	OnCreate();

	//Register window class
	WNDCLASSEX wc = { sizeof(WNDCLASSEX),CS_CLASSDC,MsgProc,0,0,
					  GetModuleHandle(NULL),NULL,NULL,NULL,NULL,
					  L"DirectX Framework Window",NULL };
	wc.hIconSm = (HICON)LoadImage(hInst, MAKEINTRESOURCE(NULL), IMAGE_ICON, 16, 16, 0);
	wc.hIcon = (HICON)LoadImage(hInst, MAKEINTRESOURCE(NULL), IMAGE_ICON, 32, 32, 0);
	RegisterClassEx(&wc);

	//Create window
	RECT wr;
	wr.left = 100;
	wr.right = 800 + wr.left;
	wr.top = 100;
	wr.bottom = 600 + wr.top;
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
	HWND hWnd = CreateWindowW(L"DirectX Framework Window", L"DirectX Framework",
		WS_OVERLAPPEDWINDOW, wr.left, wr.top, wr.right - wr.left, wr.bottom - wr.top,
		NULL, NULL, wc.hInstance, NULL);

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	//Direct3D initialize
	pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE, &d3dpp, &pDevice);

	//Process messages
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 0.0f, 0);

			IDirect3DSurface9* pBackBuffer = NULL;
			D3DLOCKED_RECT rect;

			pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
			pBackBuffer->LockRect(&rect, NULL, NULL);

			if (FirstTimeRunning) {
				Setup(rect, 800, 600);
				FirstTimeRunning = FALSE;
			}
			else {
				Update(rect, 800, 600);
			}

			pBackBuffer->UnlockRect();
			pBackBuffer->Release();


			pDevice->Present(NULL, NULL, NULL, NULL);
		}
	}

	OnDestroy();

	//When WM_DESTROY,release all the variable
	UnregisterClass(L"DirectX Framework Window", wc.hInstance);

	if (pDevice)
	{
		pDevice->Release();
		pDevice = NULL;
	}
	if (pDirect3D)
	{
		pDirect3D->Release();
		pDirect3D = NULL;
	}

	return 0;
}