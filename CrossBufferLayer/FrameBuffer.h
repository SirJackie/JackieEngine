#ifndef __CSBF_FrameBuffer__
#define __CSBF_FrameBuffer__

#include "BasicDataTypeDeclarations.h"
#include "FontSupport.h"
#include "FileSupport.h"

#define CS_FB_INIT_CURX 10
#define CS_FB_INIT_CURY 10

// Make sure the struct 'BitmapHeader' has no empty line-up things between two member variables
#pragma pack(push,1)

struct BitmapHeader {
    /*定义为'BM'，标识bmp文件*/
    ui8 bfID[2];
    /*整个BMP文件的大小*/
    ui32 bfFileSize;
    ui16 bfReserved[2];
    /*偏移数，即 位图文件头+位图信息头+调色板 的大小*/
    ui32 bfHeaderSize;

    /*位图信息头的大小，为40*/
    ui32 biInfoSize;
    /*位图的宽度，单位是像素(像素结构体为tagRGBTRIPLE)*/
    ui32 biWidth;
    /*位图的高度，单位是像素(像素结构体为tagRGBTRIPLE)*/
    i32 biHeight;
    /*目标设备的级别，必须为1(2字节)*/
    ui16 biPlanes;
    /*每个像素的位数1-黑白图，4-16色，8-256色，24-真彩色*/
    /*应该是根据这个选择后面的像素结构体*/
    ui16 biBitMode;
    /*压缩方式，BI_RGB(0)为不压缩*/
    ui32 biCompression;
    /*位图全部像素占用的字节数(所有像素结构体总和)，BI_RGB时可设为0*/
    ui32 biSizeImage;
    /*水平分辨率(像素/米) 0即可*/
    ui32 biXPelsPerMeter;
    /*垂直分辨率(像素/米) 0即可*/
    ui32 biYPelsPerMeter;
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

class CS_FrameBuffer
{

private:
	// Private Member Variables for Internal Useages
    i32 curX;
    i32 curY;

public:
	// It's pretty dirty here to expose these buffers to the outside
	// But I just gonna do it because it can make the program runs faster
	// Than create a Getter Function seperately
	i32 width;
	i32 height;

	ui8* redBuffer;
	ui8* greenBuffer;
	ui8* blueBuffer;

private:
	// Private Member Function for Internal Usages
    void AllocateBuffer
         (i32 width, i32 height);
    void DisAllocateBuffer
         ();
	void CopySameSizeBuffer
		 (const CS_FrameBuffer& from, CS_FrameBuffer& to);

public:
	// Constructors and Destructors
	CS_FrameBuffer();
	CS_FrameBuffer(i32 Width_, i32 Height_);
	CS_FrameBuffer(const CS_FrameBuffer& fb);
	CS_FrameBuffer& operator=(const CS_FrameBuffer& fb);
	~CS_FrameBuffer();

public:
	// Member Functions for Users
	i32 GetWidth();
	i32 GetHeight();

	inline void PutPixel
	(
		const i32& x, const i32& y,
		const i32& r, const i32& g, const i32& b
	)
	{
		i32 pos = y * width + x;
		redBuffer[pos] = r;
		greenBuffer[pos] = g;
		blueBuffer[pos] = b;
	}

    void ClearSelfBuffer
         ();
    void ClearSelfBuffer
         (ui8 r, ui8 g, ui8 b);
    
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
    void Print(const i8* str);  // Print C-String
    void Print(string str);     // Print std::string
    void Print(csbool csb);     // Print Cross-Buffer-Standard Boolean Variable

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

#endif
