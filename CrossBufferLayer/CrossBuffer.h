struct FrameBuffer
{
    int Width;
    int Height;
    int Pitch;
    void* pBits;
};

#define GetPixel(fb, x, y)                   (((unsigned long*)fb.pBits)[x + (fb.Pitch >> 2) * y])
#define SetPixel(fb, x, y, color)            (((unsigned long*)fb.pBits)[x + (fb.Pitch >> 2) * y] = color)
#define GetPixelLB(fb, height, x, y)         (((unsigned long*)fb.pBits)[x + (fb.Pitch >> 2) * (height-y)])
#define SetPixelLB(fb, height, x, y, color)  (((unsigned long*)fb.pBits)[x + (fb.Pitch >> 2) * (height-y)] = color)

#define Color                      unsigned long
#define CreateColor(r, g, b, a)    ((Color)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#define GetColorR(color)           (char)(color>>16) & 0xff
#define GetColorG(color)           (char)(color>>8)  & 0xff
#define GetColorB(color)           (char)(color)     & 0xff
#define GetColorA(color)           (char)(color>>24) & 0xff
#define SetColorR(color, r)        (color = CreateColor(r, GetColorG(color), GetColorB(color), GetColorA(color)))
#define SetColorG(color, g)        (color = CreateColor(GetColorR(color), g, GetColorB(color), GetColorA(color)))
#define SetColorB(color, b)        (color = CreateColor(GetColorR(color), GetColorG(color), b, GetColorA(color)))
#define SetColorA(color, a)        (color = CreateColor(GetColorR(color), GetColorG(color), GetColorB(color), a))
