// Include Hardware Simulation Parts
#include "WindowsHelper.h"
#include "D3DHelper.h"
#include "KeyboardHelper.h"

// Include Standard Libraries
#include <time.h>

// Include the CrossBufferLayer
#include "../Main.h"
#include "../CrossBufferLayer/CrossBuffer.h"

// WindowsSimuLayer Variables
WSL_WindowsHelper   windowsHelper;
WSL_D3DHelper       d3dHelper;
WSL_KeyboardHelper  keyboardHelper;

// CrossBufferLayer Variables
CS_FrameBuffer fb;
CS_Mouse       mouse;

// Time Counting Variables
csbool FirstTimeRunning;
clock_t lastTime;
clock_t thisTime;

// Windows.h Loop Message Variable
MSG msg;
csbool isCursorShowingNow = csTrue;

// Message Processing Function Declaration
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

csbool lastFrameInfinityState = csFalse;

void SetLocalCursorPos(i32 x, i32 y) {
	SetCursorPos
	(
		windowsHelper.leftMargin + x,
		windowsHelper.topMargin + y
	);
}


/*
** Main Function
*/

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	extern string CS_OperatingSystem;
	CS_OperatingSystem = "Windows";

	// Initialize CrossBufferLayer and WIndowsSimuLayer Objects
	windowsHelper = WSL_WindowsHelper(MsgProc, hInstance, (wchar_t*)WindowTitle, (wchar_t*)WindowTitle);

	// Determine the DPI Scaling Factor
	// Continue to increase until logical width is <= 1200
	HIGH_DPI_SCALING_FACTOR = 1;
	while (true) {
		if ((windowsHelper.windowWidth / HIGH_DPI_SCALING_FACTOR) > 1200) {
			HIGH_DPI_SCALING_FACTOR++;
		}
		else {
			break;
		}
	}

	// IMPORTANT! Lowered the logical resolution to speedup when HighDPI
	windowsHelper.windowWidth /= HIGH_DPI_SCALING_FACTOR;
	windowsHelper.windowHeight /= HIGH_DPI_SCALING_FACTOR;

	d3dHelper = WSL_D3DHelper(windowsHelper.hWnd);
	keyboardHelper = WSL_KeyboardHelper();
	fb = CS_FrameBuffer(windowsHelper.windowWidth, windowsHelper.windowHeight);
	mouse = CS_Mouse(windowsHelper.windowWidth, windowsHelper.windowHeight);

	i32 CenterX = windowsHelper.leftMargin;
	i32 CenterY = windowsHelper.topMargin;
	i32 GlobalCenterX = windowsHelper.leftMargin + (windowsHelper.windowWidth  / 2);
	i32 GlobalCenterY = windowsHelper.topMargin  + (windowsHelper.windowHeight / 2);

	mouse = CS_Mouse(windowsHelper.windowWidth, windowsHelper.windowHeight);

	// Initialize Time Counting Variables
	FirstTimeRunning = csTrue;

	// Initialize Windows.h Loop Message Variable
	ZeroMemory(&msg, sizeof(msg));


	/* Main Loop */
	while (msg.message != WM_QUIT)
	{
		if (isCursorShowingNow == csTrue && mouse.IsInfinityModeOpened() == csTrue) {
			isCursorShowingNow = csFalse;
			ShowCursor(csFalse);
		}

		if (isCursorShowingNow == csFalse && mouse.IsInfinityModeOpened() == csFalse) {
			isCursorShowingNow = csTrue;
			ShowCursor(csTrue);
		}

		if (mouse.GetX() == 0 || mouse.GetY() == 0) {
			POINT pt;
			GetCursorPos(&pt);

			mouse.__DONT_USE__SetX(pt.x - windowsHelper.leftMargin);
			mouse.__DONT_USE__SetY(pt.y - windowsHelper.topMargin);
			mouse.__DONT_USE__SetLastX(mouse.GetX());
			mouse.__DONT_USE__SetLastY(mouse.GetY());
		}

		if (lastFrameInfinityState == csFalse && mouse.IsInfinityModeOpened() == csTrue) {
			// Make the next frame mouse.x|y equals to this frame
			SetCursorPos(GlobalCenterX, GlobalCenterY);

			lastFrameInfinityState = csTrue;
		}

		else if (lastFrameInfinityState == csTrue && mouse.IsInfinityModeOpened() == csFalse) {
			SetLocalCursorPos
			(
				CS_iclamp(0, mouse.GetX(), windowsHelper.windowWidth),
				CS_iclamp(0, mouse.GetY(), windowsHelper.windowHeight)
			);
			lastFrameInfinityState = csFalse;
		}

		else if (lastFrameInfinityState == csTrue && mouse.IsInfinityModeOpened() == csTrue) {
			POINT pt;
			GetCursorPos(&pt);

			mouse.__DONT_USE__SetX(mouse.GetX() + (pt.x - GlobalCenterX));
			mouse.__DONT_USE__SetY(mouse.GetY() + (pt.y - GlobalCenterY));

			SetCursorPos(GlobalCenterX, GlobalCenterY);
		}
		

		// If there is a Message
		if (PeekMessage(&msg, csNull, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		/* Process our Game Loop */

		// Update Keyboard Status when there is or isn't a message
		keyboardHelper.MoveWinBufIntoKeyBuf();
		if (keyboardHelper.kb.IsKeyPressed(CSK_Esc)) {
			SendMessage(windowsHelper.hWnd, WM_CLOSE, 0, 0);
		}

		mouse.__DONT_USE__SetDeltaX(mouse.GetX() - mouse.GetLastX());
		mouse.__DONT_USE__SetDeltaY(mouse.GetY() - mouse.GetLastY());

		// Update Time Counting Variables
		thisTime = clock();

		// Lock System BackBuffer and Clear the FrameBuffer
		d3dHelper.LockBuffer();
		fb = CS_FrameBuffer
		(
			windowsHelper.windowWidth, windowsHelper.windowHeight
		);

		// If it is the First Time Running
		if (FirstTimeRunning) {
			Setup(fb, keyboardHelper.kb, mouse, 0);                     // Call the Setup()  in Main.h
			FirstTimeRunning = csFalse;
		}

		// If it is not the First Time Running
		else {
			Update(fb, keyboardHelper.kb, mouse, thisTime - lastTime);  // Call the Update() in Main.h
		}

		// Paint Our FrameBuffer to System BackBuffer
		d3dHelper.PaintFrameBufferHere(fb);

		// Release Back Buffer and Swap it as the FrontBuffer
		d3dHelper.UnlockBuffer();

		// Update Time Counting Variables
		// lastTime in next frame = thisTime in this frame
		lastTime = thisTime;

		mouse.__DONT_USE__SetLastX(mouse.GetX());
		mouse.__DONT_USE__SetLastY(mouse.GetY());
	}

	/* After the Main Loop */
	{
		// Release All the Variables
		windowsHelper.Unregister((wchar_t*)WindowTitle);
		d3dHelper.Release();
		if (isCursorShowingNow == csFalse) {
			isCursorShowingNow = csTrue;
			ShowCursor(csTrue);
		}
		return 0;
	}
}


/*
** Message Loop
*/

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		ClipCursor(NULL);
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN:
		keyboardHelper.windowsKeyBuffer[wParam] = 1;
		return DefWindowProc(hWnd, msg, wParam, lParam);

	case WM_KEYUP:
		keyboardHelper.windowsKeyBuffer[wParam] = 0;
		return DefWindowProc(hWnd, msg, wParam, lParam);

	case WM_LBUTTONDOWN:
		mouse.__DONT_USE__SetLBtnState(csTrue);
		return DefWindowProc(hWnd, msg, wParam, lParam);

	case WM_LBUTTONUP:
		mouse.__DONT_USE__SetLBtnState(csFalse);
		return DefWindowProc(hWnd, msg, wParam, lParam);

	case WM_MBUTTONDOWN:
		mouse.__DONT_USE__SetMBtnState(csTrue);
		return DefWindowProc(hWnd, msg, wParam, lParam);

	case WM_MBUTTONUP:
		mouse.__DONT_USE__SetMBtnState(csFalse);
		return DefWindowProc(hWnd, msg, wParam, lParam);

	case WM_RBUTTONDOWN:
		mouse.__DONT_USE__SetRBtnState(csTrue);
		return DefWindowProc(hWnd, msg, wParam, lParam);

	case WM_RBUTTONUP:
		mouse.__DONT_USE__SetRBtnState(csFalse);
		return DefWindowProc(hWnd, msg, wParam, lParam);

	case WM_MOUSEMOVE:
		if (mouse.IsInfinityModeOpened() == csFalse) {
			mouse.__DONT_USE__SetX(LOWORD(lParam));
			mouse.__DONT_USE__SetY(HIWORD(lParam));
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}
