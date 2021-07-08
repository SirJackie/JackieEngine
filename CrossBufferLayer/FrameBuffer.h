#ifndef __CSBF_FrameBuffer__
#define __CSBF_FrameBuffer__

#include "BasicDataTypeDeclarations.h"
#include "FontSupport.h"

#include <string>
using std::string;
#include <sstream>
using std::stringstream;

#define CS_FB_INIT_CURX 10
#define CS_FB_INIT_CURY 10


class CS_FrameBuffer
{
public:

    // Properties
    i32 width;
    i32 height;

    ui8* redBuffer;
    ui8* greenBuffer;
    ui8* blueBuffer;

    i32 curX;
    i32 curY;


    // Methods
    void AllocateBuffer
         (i32 width, i32 height);
    void DisAllocateBuffer
         ();
    void ClearSelfBuffer
         ();
    void CopySameSizeBuffer
         (const CS_FrameBuffer& from, CS_FrameBuffer& to);

    CS_FrameBuffer();
    CS_FrameBuffer(i32 Width_, i32 Height_);
    CS_FrameBuffer(const CS_FrameBuffer& fb);
    CS_FrameBuffer& operator=(const CS_FrameBuffer& fb);
    ~CS_FrameBuffer();

    void DrawChar
    (
        const char& ch, const i32 xStart, const i32 yStart,
        const ui8 r, const ui8 g, const ui8 b
    );
    void DrawString
    (
        const i8* str, const i32 x, const i32 y,
        const ui8 r, const ui8 g, const ui8 b
    );
    void Print(const i8* str);
    void Print(string str);
    void Print(csbool csb);
    template<class T>
    void Print(T x)
    {
        stringstream ss;
        ss.clear();
        ss.str("");
        ss << x;
        Print(ss.str());
    }

    template<class T>
    void PrintLn(T x)
    {
        Print(x);
        Print("\n");
    }
};

#define SetPixel(fb, x, y, r, g, b) ({    i32 framebuffer_setpixel_temp_pos = (y) * fb.width + (x); (fb).redBuffer[framebuffer_setpixel_temp_pos] = (r); (fb).greenBuffer[framebuffer_setpixel_temp_pos] = (g); (fb).blueBuffer[framebuffer_setpixel_temp_pos] = (b);    })

#endif
