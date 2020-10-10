#ifndef __D3D9_H__
#define __D3D9_H__
#include <d3d9.h>
#endif

#ifndef __WINDOWS_H__
#define __WINDOWS_H__
#include <Windows.h>
#endif

#define FrameBuffer D3DLOCKED_RECT
#define GetPixel(fb, x, y)        (((D3DCOLOR*)fb.pBits)[x + (fb.Pitch >> 2) * y])
#define SetPixel(fb, x, y, color) (((D3DCOLOR*)fb.pBits)[x + (fb.Pitch >> 2) * y] = color)
#define RGB888(r, g, b) (D3DCOLOR_XRGB(r, g, b))