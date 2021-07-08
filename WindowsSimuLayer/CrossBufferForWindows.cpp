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

// Message Processing Function Declaration
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

struct WinMouse {
	i32 realx;
	i32 realy;
	i32 pagex;
	i32 pagey;
	csbool nowInfinityState;
};

WinMouse winMouse;

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

	// Initialize CrossBufferLayer and WIndowsSimuLayer Objects
	windowsHelper = WSL_WindowsHelper(MsgProc, hInstance, (wchar_t*)WindowTitle, (wchar_t*)WindowTitle);
	d3dHelper = WSL_D3DHelper(windowsHelper.hWnd);
	keyboardHelper = WSL_KeyboardHelper();
	fb = CS_FrameBuffer(windowsHelper.windowWidth, windowsHelper.windowHeight);
	mouse = CS_Mouse(windowsHelper.windowWidth, windowsHelper.windowHeight);

	winMouse.realx = 0;
	winMouse.realy = 0;
	winMouse.pagex = 0;
	winMouse.pagey = 0;
	winMouse.nowInfinityState = csFalse;

	// Initialize Time Counting Variables
	FirstTimeRunning = csTrue;

	// Initialize Windows.h Loop Message Variable
	ZeroMemory(&msg, sizeof(msg));


	/* Main Loop */
	while (msg.message != WM_QUIT)
	{
		if (winMouse.nowInfinityState == csFalse) {
			if (mouse.infinityMode == csTrue) {
				winMouse.nowInfinityState = csTrue;
				RECT rect;
				rect.left = windowsHelper.leftMargin;
				rect.top = windowsHelper.topMargin;
				rect.right = windowsHelper.leftMargin + windowsHelper.windowWidth - 1;
				rect.bottom = windowsHelper.topMargin + windowsHelper.windowHeight - 1;
				ClipCursor(&rect);
			}
		}

		if (winMouse.nowInfinityState == csTrue) {
			if (mouse.infinityMode == csFalse) {
				winMouse.pagex = 0;
				winMouse.pagey = 0;
				winMouse.realx = 0;
				winMouse.realy = 0;
				winMouse.nowInfinityState = csFalse;
				ClipCursor(NULL);
				
				i32 newCursorPosX = mouse.x;
				i32 newCursorPosY = mouse.y;
				if (newCursorPosX < 0) newCursorPosX = 0;
				if (newCursorPosY < 0) newCursorPosY = 0;
				if (newCursorPosX > windowsHelper.windowWidth - 1) {
					newCursorPosX = windowsHelper.windowWidth - 1;
				}
				if (newCursorPosY > windowsHelper.windowHeight - 1) {
					newCursorPosY = windowsHelper.windowHeight - 1;
				}
				SetLocalCursorPos(newCursorPosX, newCursorPosY);
			}
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
	}

	/* After the Main Loop */
	{
		// Release All the Variables
		windowsHelper.Unregister((wchar_t*)WindowTitle);
		d3dHelper.Release();
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
		if (mouse.infinityMode == csTrue) {
			winMouse.realx = LOWORD(lParam);  // MouseX
			winMouse.realy = HIWORD(lParam);  // MouseY

			if (winMouse.realx == 0) {
				SetLocalCursorPos(windowsHelper.windowWidth - 2, winMouse.realy);
				winMouse.pagex -= 1;
			}

			if (winMouse.realx == windowsHelper.windowWidth - 1) {
				SetLocalCursorPos(1, winMouse.realy);
				winMouse.pagex += 1;
			}

			if (winMouse.realy == 0) {
				SetLocalCursorPos(winMouse.realx, windowsHelper.windowHeight - 2);
				winMouse.pagey -= 1;
			}

			if (winMouse.realy == windowsHelper.windowHeight - 1) {
				SetLocalCursorPos(winMouse.realx, 1);
				winMouse.pagey += 1;
			}

			mouse.x = winMouse.realx + winMouse.pagex * (windowsHelper.windowWidth - 2);
			mouse.y = winMouse.realy + winMouse.pagey * (windowsHelper.windowHeight - 2);
		}
		else {
			mouse.x = LOWORD(lParam);
			mouse.y = HIWORD(lParam);
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}
