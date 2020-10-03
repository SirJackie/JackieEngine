#include <iostream>
#include <Windows.h>
#include <d3d9.h>
#include "resource.h"
#include <time.h>
#include "Main.h"
using namespace std;

IDirect3D9* pDirect3D;
IDirect3DDevice9* pDevice;
BOOL FirstTimeRunning = TRUE;

int WindowLeftMargin;
int WindowTopMargin;
int WindowWidth;
int WindowHeight;

/*
** Functions
*/

void GetScreenResolution(int* resultX, int* resultY) {
	// Get Screen HDC
	HDC hdcScreen;
	hdcScreen = CreateDC(L"DISPLAY", NULL, NULL, NULL);

	// Get X and Y
	*resultX = GetDeviceCaps(hdcScreen, HORZRES);    // pixel
	*resultY = GetDeviceCaps(hdcScreen, VERTRES);    // pixel

	// Release HDC
	if (NULL != hdcScreen)
	{
		DeleteDC(hdcScreen);
	}
}

BOOL IsKeyPressing;
int KeyCode;
BOOL IsMousePressing;
int MouseX;
int MouseY;

BOOL FirstTimeGettingInput = TRUE;

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN:
		IsKeyPressing = TRUE;
		KeyCode = wParam;
		break;

	case WM_KEYUP:
		IsKeyPressing = FALSE;

	case WM_LBUTTONDOWN:
		IsMousePressing = TRUE;
		break;

	case WM_MOUSEMOVE:
		MouseX = LOWORD(lParam);
		MouseY = HIWORD(lParam);
		break;

	default:
		if (FirstTimeGettingInput) {
			MouseX = LOWORD(lParam);
			MouseY = HIWORD(lParam);
			FirstTimeGettingInput = FALSE;
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}


int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	/*
	** Calculate Window Width And Height
	*/
	int ScreenX, ScreenY;
	GetScreenResolution(&ScreenX, &ScreenY);

	int Unit = ScreenY / 30;

	WindowTopMargin = 2 * Unit;
	WindowHeight = 26 * Unit;

	WindowLeftMargin = Unit;
	WindowWidth = ScreenX - 2 * Unit;

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
	wr.left   = WindowLeftMargin;
	wr.right  = WindowWidth + wr.left;
	wr.top    = WindowTopMargin;
	wr.bottom = WindowHeight + wr.top;
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

	clock_t lastTime, thisTime;

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
				thisTime = clock();
				Setup(rect, WindowWidth, WindowHeight);
				FirstTimeRunning = FALSE;
				lastTime = thisTime;
			}
			else {
				thisTime = clock();
				Update(rect, WindowWidth, WindowHeight, thisTime - lastTime, IsKeyPressing, KeyCode, IsMousePressing, MouseX, MouseY);
				lastTime = thisTime;
			}

			if (IsMousePressing) {
				IsMousePressing = FALSE;
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