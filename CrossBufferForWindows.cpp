#ifndef __IOSTREAM__
#define __IOSTREAM__
#include <iostream>
#endif

#ifndef __WINDOWS_H__
#define __WINDOWS_H__
#include <Windows.h>
#endif

#ifndef __D3D9_H__
#define __D3D9_H__
#include <d3d9.h>
#endif

#ifndef __TIME_H__
#define __TIME_H__
#include <time.h>
#endif

#ifndef __INPUT_H__
#define __INPUT_H__
#include "Input.h"
#endif

#include "resource.h"
#include "Main.h"

using namespace std;

/* Window Class Properties */
#define WindowClassName L"CrossBuffer For Windows Class"
#define WindowTitle     L"CrossBuffer For Windows"

/* DirectX Objects */
IDirect3D9* pDirect3D;
IDirect3DDevice9* pDevice;
IDirect3DSurface9* pBackBuffer;
D3DLOCKED_RECT rect;

/* Window Properties */
int WindowLeftMargin;
int WindowTopMargin;
int WindowWidth;
int WindowHeight;

/* Input Objects */
int keyboard[256];
Mouse mouse;
int MouseX;
int MouseY;
int MouseInitX;
int MouseInitY;
int MouseLastX;
int MouseLastY;
BOOL WantToLockOrNot = FALSE;
BOOL NowLockingOrNot = FALSE;
BOOL HideCursorOrNot = FALSE;

/* Flags */
BOOL FirstTimeRunning = TRUE;

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
	ZeroMemory(keyboard, 256 * sizeof(int) );
	ZeroMemory(&mouse,   sizeof(Mouse)     );
	mouse.WantToLockOrNot = &WantToLockOrNot;
	mouse.NowLockingOrNot = &NowLockingOrNot;
	mouse.HideCursorOrNot = &HideCursorOrNot;
	thisTime = clock();
	lastTime = thisTime;


	/*
	** Calculate Window Width And Height
	*/
	int ScreenX, ScreenY;
	GetScreenResolution(&ScreenX, &ScreenY);

	int Unit = ScreenY / 30;

	WindowHeight     = 26 * Unit;
	WindowTopMargin  = 2  * Unit;

	WindowWidth      = WindowHeight / 9 * 16;
	WindowLeftMargin = (ScreenX - WindowWidth) / 2;

	mouse.DeltaRatio = min(WindowWidth, WindowHeight);
	MouseX = WindowWidth / 2;
	MouseY = WindowHeight / 2;
	MouseInitX = MouseX;
	MouseInitY = MouseY;
	

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
		WindowClassName, NULL
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
		WindowClassName, WindowTitle,
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

		/* If there is a Message from Windows*/
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			/* Then Process it */
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			ShowCursor(!HideCursorOrNot);
		}

		/* Else, Process the Game Loop */
		else
		{
			ShowCursor(!HideCursorOrNot);

			/*
			** Calculate the Time
			** thisTime = the time from the beginning of the program to the present
			*/
			thisTime = clock();


			/*
			** Clear Back Buffer
			*/
			pDevice->Clear(
				0, NULL, D3DCLEAR_TARGET,
				D3DCOLOR_XRGB(0, 0, 0), 0.0f, 0
			);


			/*
			** Get Back Buffer
			*/
			pBackBuffer = NULL;
			pDevice->GetBackBuffer(
				0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer
			);
			pBackBuffer->LockRect(&rect, NULL, NULL);


			/*
			** Call Main.h
			*/

			/* If it is the First Time Running */
			if (FirstTimeRunning) {
				/* Set The Mouse's Initialize Position */
				mouse.RealX = MouseInitX;
				mouse.RealY = MouseInitY;
				SetCursorPos(WindowLeftMargin + MouseInitX, WindowTopMargin + MouseInitY);

				/* Call the Setup() in Main.h */
				Setup(rect, WindowWidth, WindowHeight, 0, keyboard, mouse);
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


			/*
			** Calculate the Time
			** lastTime in next frame = thisTime in this frame
			*/
			lastTime = thisTime;

			/*
			** Clear Mouse Delta
			*/
			mouse.RealDeltaX = 0;
			mouse.RealDeltaY = 0;
			mouse.DeltaX = 0.0f;
			mouse.DeltaY = 0.0f;
		}
	}


	/*
	** After the Main Loop
	*/

	/* Call OnDestroy() in Main.h */
	OnDestroy();

	/* Release All the Variables */
	UnregisterClass(WindowClassName, wc.hInstance);

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
		if (wParam == KEY_ESCAPE) {
			NowLockingOrNot = FALSE;
			HideCursorOrNot = FALSE;
		}
		break;

	case WM_KEYUP:
		keyboard[wParam] = 0;
		break;

	case WM_LBUTTONDOWN:
		mouse.LButtonState = PRESSED;
		if(WantToLockOrNot == TRUE){
			NowLockingOrNot = TRUE;
			HideCursorOrNot = TRUE;
		}
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
		/* If First Time Running, MouseXY = MouseInitXY, DeltaXY = 0 */
		if (FirstTimeRunning == TRUE) {
			break;
		}

		/* Refresh MouseLastX and MouseLastY */
		if (NowLockingOrNot == TRUE) {
			MouseLastX = MouseInitX;
			MouseLastY = MouseInitY;
		}
		else {
			MouseLastX = MouseX;
			MouseLastY = MouseY;
		}
		
		/* Get Mouse Position */
		MouseX = LOWORD(lParam);
		MouseY = HIWORD(lParam);

		/* Calculate Delta */
		mouse.RealX = MouseX;
		mouse.RealY = MouseY;
		mouse.RealDeltaX = MouseX - MouseLastX;
		mouse.RealDeltaY = MouseY - MouseLastY;
		mouse.DeltaX = 1.0f * mouse.RealDeltaX / mouse.DeltaRatio;
		mouse.DeltaY = 1.0f * mouse.RealDeltaY / mouse.DeltaRatio;

		/* Lock Action */
		if (NowLockingOrNot == TRUE) {
			SetCursorPos(WindowLeftMargin + MouseInitX, WindowTopMargin + MouseInitY);
		}
		else {
			SetCursorPos(WindowLeftMargin + mouse.RealX, WindowTopMargin + mouse.RealY);
		}
		break;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}
