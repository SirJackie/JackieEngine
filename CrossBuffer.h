#pragma once

#include <d3d9.h>
#include <Windows.h>

#define FrameBuffer D3DLOCKED_RECT
#define Pixel(fb, x, y) ((D3DCOLOR*)fb.pBits)[x + (fb.Pitch >> 2) * y]
#define RGB888(r, g, b) (D3DCOLOR_XRGB(r, g, b))