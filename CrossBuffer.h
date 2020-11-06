#ifndef __D3D9_H__
#define __D3D9_H__
#include <d3d9.h>
#endif

#ifndef __WINDOWS_H__
#define __WINDOWS_H__
#include <Windows.h>
#endif

#define FrameBuffer                D3DLOCKED_RECT
#define GetPixel(fb, x, y)         (((D3DCOLOR*)fb.pBits)[x + (fb.Pitch >> 2) * y])
#define SetPixel(fb, x, y, color)  (((D3DCOLOR*)fb.pBits)[x + (fb.Pitch >> 2) * y] = color)

#define Color                      D3DCOLOR
#define CreateColor(r, g, b, a)    (D3DCOLOR_ARGB(a, r, g, b))
#define GetColorR(color)           (char)(color>>16) & 0xff
#define GetColorG(color)           (char)(color>>8)  & 0xff
#define GetColorB(color)           (char)(color)     & 0xff
#define GetColorA(color)           (char)(color>>24) & 0xff
#define SetColorR(color, r)        (color = CreateColor(r, GetColorG(color), GetColorB(color), GetColorA(color)))
#define SetColorG(color, g)        (color = CreateColor(GetColorR(color), g, GetColorB(color), GetColorA(color)))
#define SetColorB(color, b)        (color = CreateColor(GetColorR(color), GetColorG(color), b, GetColorA(color)))
#define SetColorA(color, a)        (color = CreateColor(GetColorR(color), GetColorG(color), GetColorB(color), a))
