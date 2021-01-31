#ifndef __CSBF_FrameBufferSupport
#define __CSBF_FrameBufferSupport

struct FrameBuffer
{
    int Width;
    int Height;
    int Pitch;
    void* pBits;
};

#define Color                                unsigned long
#define CreateColor(r, g, b)                 ((Color) (( (0xff) << 24)  |  (((r)&0xff) << 16)  |  (((g)&0xff) << 8)  |  ((b) & 0xff) ))

#define GetColorR(color)                     ((color>>16) & 0xff)
#define GetColorG(color)                     ((color>>8)  & 0xff)
#define GetColorB(color)                     ((color)     & 0xff)

#define SetColorR(color, r)                  (color = (color & 0xFF00FFFF) | (((r)&0xff) << 16)   )
#define SetColorG(color, g)                  (color = (color & 0xFFFF00FF) | (((g)&0xff) << 8)    )
#define SetColorB(color, b)                  (color = (color & 0xFFFFFF00) | ((b) & 0xff)         )

#define GetPixel(fb, x, y)                   (((unsigned long*)fb.pBits)[x + (fb.Pitch >> 2) * y])
#define SetPixel(fb, x, y, color)            (((unsigned long*)fb.pBits)[x + (fb.Pitch >> 2) * y] = color)
#define GetPixelLB(fb, height, x, y)         (((unsigned long*)fb.pBits)[x + (fb.Pitch >> 2) * (height-y)])
#define SetPixelLB(fb, height, x, y, color)  (((unsigned long*)fb.pBits)[x + (fb.Pitch >> 2) * (height-y)] = color)

#endif
