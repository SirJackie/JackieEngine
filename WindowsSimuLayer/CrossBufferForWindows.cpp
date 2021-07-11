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
		if (isCursorShowingNow == csTrue && mouse.infinityMode == csTrue) {
			isCursorShowingNow = csFalse;
			ShowCursor(csFalse);
		}

		if (isCursorShowingNow == csFalse && mouse.infinityMode == csFalse) {
			isCursorShowingNow = csTrue;
			ShowCursor(csTrue);
		}

		if (mouse.x == 0 || mouse.y == 0) {
			POINT pt;
			GetCursorPos(&pt);
			mouse.x = pt.x - windowsHelper.leftMargin;
			mouse.y = pt.y - windowsHelper.topMargin;
			mouse.lastX = mouse.x;
			mouse.lastY = mouse.y;
		}

		if (lastFrameInfinityState == csFalse && mouse.infinityMode == csTrue) {
			// Make the next frame mouse.x|y equals to this frame
			SetCursorPos(GlobalCenterX, GlobalCenterY);

			lastFrameInfinityState = csTrue;
		}

		else if (lastFrameInfinityState == csTrue && mouse.infinityMode == csFalse) {
			SetLocalCursorPos
			(
				CS_iclamp(0, mouse.x, windowsHelper.windowWidth),
				CS_iclamp(0, mouse.y, windowsHelper.windowHeight)
			);
			lastFrameInfinityState = csFalse;
		}

		else if (lastFrameInfinityState == csTrue && mouse.infinityMode == csTrue) {
			POINT pt;
			GetCursorPos(&pt);

			mouse.x += pt.x - GlobalCenterX;
			mouse.y += pt.y - GlobalCenterY;

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

		mouse.deltaX = mouse.x - mouse.lastX;
		mouse.deltaY = mouse.y - mouse.lastY;

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

		mouse.lastX = mouse.x;
		mouse.lastY = mouse.y;
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
		mouse.lBtnState = csTrue;
		return DefWindowProc(hWnd, msg, wParam, lParam);

	case WM_LBUTTONUP:
		mouse.lBtnState = csFalse;
		return DefWindowProc(hWnd, msg, wParam, lParam);

	case WM_MBUTTONDOWN:
		mouse.mBtnState = csTrue;
		return DefWindowProc(hWnd, msg, wParam, lParam);

	case WM_MBUTTONUP:
		mouse.mBtnState = csFalse;
		return DefWindowProc(hWnd, msg, wParam, lParam);

	case WM_RBUTTONDOWN:
		mouse.rBtnState = csTrue;
		return DefWindowProc(hWnd, msg, wParam, lParam);

	case WM_RBUTTONUP:
		mouse.rBtnState = csFalse;
		return DefWindowProc(hWnd, msg, wParam, lParam);

	case WM_MOUSEMOVE:
		if (mouse.infinityMode == csFalse) {
			mouse.x = LOWORD(lParam);
			mouse.y = HIWORD(lParam);
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}
