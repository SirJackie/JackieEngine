#include <iostream>
#include <Windows.h>
#include <d3d9.h>
#include <time.h>
#include "resource.h"
#include "Main.h"
using namespace std;

/* DirectX Objects */
IDirect3D9* pDirect3D;
IDirect3DDevice9* pDevice;

/* Window Properties */
int WindowLeftMargin;
int WindowTopMargin;
int WindowWidth;
int WindowHeight;

/* Input Objects */
int keyboard[256];
Mouse mouse;

/* Flags */
BOOL FirstTimeRunning      = TRUE;
BOOL FirstTimeGettingInput = TRUE;

/* Timer */
clock_t lastTime = NULL;
clock_t thisTime = NULL;


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

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


/*
** Main Function
*/

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	/*
	** Initialize All The Variables
	*/
	ZeroMemory(keyboard, 256 * sizeof(int));
	InitMouse(&mouse);
	thisTime = clock();
	lastTime = thisTime;


	/*
	** Calculate Window Width And Height
	*/
	int ScreenX, ScreenY;
	GetScreenResolution(&ScreenX, &ScreenY);

	int Unit = ScreenY / 30;

	WindowHeight     = 26 * Unit;
	WindowTopMargin  = 2 * Unit;

	WindowWidth      = WindowHeight / 9 * 16;
	WindowLeftMargin = (ScreenX - WindowWidth) / 2;
	

	/*
	** Call the OnCreate() in Main.h
	*/
	OnCreate();


	/*
	** Register Window Class
	*/
	WNDCLASSEX wc = {
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0, 0,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"DirectX Framework Window", NULL
	};

	wc.hIconSm = (HICON)LoadImage(
		hInst, MAKEINTRESOURCE(NULL), IMAGE_ICON, 16, 16, 0
	);

	wc.hIcon   = (HICON)LoadImage(
		hInst, MAKEINTRESOURCE(NULL), IMAGE_ICON, 32, 32, 0
	);

	RegisterClassEx(&wc);


	/*
	** Create Window
	*/
	RECT wr;
	wr.left   = WindowLeftMargin;
	wr.right  = WindowWidth  + wr.left;
	wr.top    = WindowTopMargin;
	wr.bottom = WindowHeight + wr.top;

	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
	HWND hWnd = CreateWindowW(
		L"DirectX Framework Window", L"DirectX Framework",
		WS_OVERLAPPEDWINDOW,
		wr.left, wr.top, wr.right - wr.left, wr.bottom - wr.top,
		NULL, NULL, wc.hInstance, NULL
	);

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);


	/*
	** Direct3D Initialize
	*/
	pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	pDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE,
		&d3dpp, &pDevice
	);


	/*
	** Process Messages From Windows
	*/
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		/*
		** Main Loop
		*/

		/* Calculate the Time */
		thisTime = clock();

		/*if (!FirstTimeRunning) {
			while ((thisTime - lastTime) < 20) {
				thisTime = clock();
			}
		}*/

		/* If there is a Message from Windows*/
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			/* Then Process it */
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		/* Else, Process the Game Loop */
		else
		{
			IDirect3DSurface9* pBackBuffer = NULL;
			D3DLOCKED_RECT rect;
			/*
			** Clear Back Buffer And Get It
			*/
			pDevice->Clear(
				0, NULL, D3DCLEAR_TARGET,
				D3DCOLOR_XRGB(0, 0, 0), 0.0f, 0
			);
			pBackBuffer = NULL;

			pDevice->GetBackBuffer(
				0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer
			);
			pBackBuffer->LockRect(&rect, NULL, NULL);


			/* If it is the First Time Running */
			if (FirstTimeRunning) {
				/* Call the Setup() in Main.h */
				Setup(rect, WindowWidth, WindowHeight);
				FirstTimeRunning = FALSE;
			}

			/* If it is not the First Time Running */
			else {
				/* Call the Update() in Main.h */
				Update(rect, WindowWidth, WindowHeight, thisTime - lastTime, keyboard, mouse);
			}

			
			/*
			** Release Back Buffer
			*/
			pBackBuffer->UnlockRect();
			pBackBuffer->Release();


			/*
			** Swap the Front and the Back Buffer
			*/
			pDevice->Present(NULL, NULL, NULL, NULL);
		}

		/* Calculate the Time*/
		lastTime = thisTime;
	}

	//clock_t lastTime = NULL, thisTime = NULL;

	//while (msg.message != WM_QUIT)
	//{
	//	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	//	{
	//		TranslateMessage(&msg);
	//		DispatchMessage(&msg);
	//	}
	//	else
	//	{
	//		pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 0.0f, 0);

	//		IDirect3DSurface9* pBackBuffer = NULL;
	//		D3DLOCKED_RECT rect;

	//		pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	//		pBackBuffer->LockRect(&rect, NULL, NULL);

	//		if (FirstTimeRunning) {
	//			thisTime = clock();
	//			Setup(rect, WindowWidth, WindowHeight);
	//			FirstTimeRunning = FALSE;
	//			lastTime = thisTime;
	//		}
	//		else {
	//			thisTime = clock();
	//			Update(rect, WindowWidth, WindowHeight, thisTime - lastTime, keyboard, mouse);
	//			lastTime = thisTime;
	//		}


	//		pBackBuffer->UnlockRect();
	//		pBackBuffer->Release();


	//		pDevice->Present(NULL, NULL, NULL, NULL);
	//	}
	//}


	/*
	** After the Main Loop
	*/

	/* Call OnDestroy() in Main.h */
	OnDestroy();

	/* Release All the Variables */
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


/*
** Message Loop
*/

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN:
		keyboard[wParam] = 1;
		break;

	case WM_KEYUP:
		keyboard[wParam] = 0;
		break;

	case WM_LBUTTONDOWN:
		mouse.LButtonState = PRESSED;
		break;

	case WM_LBUTTONUP:
		mouse.LButtonState = UNPRESSED;
		break;

	case WM_RBUTTONDOWN:
		mouse.RButtonState = PRESSED;
		break;

	case WM_RBUTTONUP:
		mouse.RButtonState = UNPRESSED;
		break;

	case WM_MOUSEMOVE:
		mouse.X = LOWORD(lParam);
		mouse.Y = HIWORD(lParam);
		break;

	default:
		if (FirstTimeGettingInput) {
			mouse.X = LOWORD(lParam);
			mouse.Y = HIWORD(lParam);
			FirstTimeGettingInput = FALSE;
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}
