#ifndef __CSBF_FrameBuffer__
#define __CSBF_FrameBuffer__

#include "BasicDataTypeDeclarations.h"
#include "FontSupport.h"
#include "FileSupport.h"

#define CS_FB_INIT_CURX 10
#define CS_FB_INIT_CURY 10

#pragma pack(push,1)


struct BitmapFileHeader {
    /*定义为'BM'，标识bmp文件*/
    ui16 bfType;
    /*整个BMP文件的大小*/
    ui32 bfSize;
    ui16 bfReserved1;
    ui16 bfReserved2;
    /*偏移数，即 位图文件头+位图信息头+调色板 的大小*/
    ui32 bfOffBits;
};

struct BitmapInfoHeader {
    /*位图信息头的大小，为40*/
    ui32 biSize;
    /*位图的宽度，单位是像素(像素结构体为tagRGBTRIPLE)*/
    ui64 biWidth;
    /*位图的高度，单位是像素(像素结构体为tagRGBTRIPLE)*/
    i64 biHeight;
    /*目标设备的级别，必须为1(2字节)*/
    ui16 biPlanes;
    /*每个像素的位数1-黑白图，4-16色，8-256色，24-真彩色*/
    /*应该是根据这个选择后面的像素结构体*/
    ui16 biBitCount;
    /*压缩方式，BI_RGB(0)为不压缩*/
    ui32 biCompression;
    /*位图全部像素占用的字节数(所有像素结构体总和)，BI_RGB时可设为0*/
    ui32 biSizeImage;
    /*水平分辨率(像素/米) 0即可*/
    ui64 biXPelsPerMeter;
    /*垂直分辨率(像素/米) 0即可*/
    ui64 biYPelsPerMeter;
    /*位图使用的颜色数,如果为0，则颜色数为2的biBitCount次方。0即可*/
    ui32 biClrUsed;
    /*重要的颜色数，0代表所有颜色都重要。0即可*/
    ui32 biClrImportant;
};

struct Pixel {
    ui8 b;
    ui8 g;
    ui8 r;
};

struct BitmapHeader {
    char id[2];
    long filesize;
    short reserved[2]; //int reserved[2];
    long headersize;
    long infoSize;
    long wd;
    long dp;
    short biPlanes; //int biPlans;
    short bits; //int bits;
    long biCompression;
    long biSizeImage;
    long biXPelsPerMeter;
    long biYPelsPerMeter;
    long biClrUsed;
    long biClrImportant;
};

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
    void ClearSelfBuffer
         (ui8 r, ui8 g, ui8 b);
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

    void DrawBuffer(CS_FrameBuffer& from, i32 toXStart, i32 toYStart);
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

    void LoadFromBMP(string fileName);
};

inline void CS_PutPixel
(
    CS_FrameBuffer& fb, const i32& x, const i32& y,
    const i32& r, const i32& g, const i32& b
)
{
    i32 pos = (y)*fb.width + (x);
    fb.redBuffer[pos] = r;
    fb.greenBuffer[pos] = g;
    fb.blueBuffer[pos] = b;
}

#endif
