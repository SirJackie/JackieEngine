#ifndef __CSBF_FrameBuffer__
#define __CSBF_FrameBuffer__

#include "BasicDataTypeDeclarations.h"
#include "FontSupport.h"
#include "FileSupport.h"

#define CS_FB_INIT_CURX 10
#define CS_FB_INIT_CURY 10

#pragma pack(push,1)


struct BitmapHeader {
    /*����Ϊ'BM'����ʶbmp�ļ�*/
    ui8 bfID[2];
    /*����BMP�ļ��Ĵ�С*/
    ui32 bfFileSize;
    ui16 bfReserved[2];
    /*ƫ�������� λͼ�ļ�ͷ+λͼ��Ϣͷ+��ɫ�� �Ĵ�С*/
    ui32 bfHeaderSize;

    /*λͼ��Ϣͷ�Ĵ�С��Ϊ40*/
    ui32 biInfoSize;
    /*λͼ�Ŀ�ȣ���λ������(���ؽṹ��ΪtagRGBTRIPLE)*/
    ui32 biWidth;
    /*λͼ�ĸ߶ȣ���λ������(���ؽṹ��ΪtagRGBTRIPLE)*/
    i32 biHeight;
    /*Ŀ���豸�ļ��𣬱���Ϊ1(2�ֽ�)*/
    ui16 biPlanes;
    /*ÿ�����ص�λ��1-�ڰ�ͼ��4-16ɫ��8-256ɫ��24-���ɫ*/
    /*Ӧ���Ǹ������ѡ���������ؽṹ��*/
    ui16 biBitMode;
    /*ѹ����ʽ��BI_RGB(0)Ϊ��ѹ��*/
    ui32 biCompression;
    /*λͼȫ������ռ�õ��ֽ���(�������ؽṹ���ܺ�)��BI_RGBʱ����Ϊ0*/
    ui32 biSizeImage;
    /*ˮƽ�ֱ���(����/��) 0����*/
    ui32 biXPelsPerMeter;
    /*��ֱ�ֱ���(����/��) 0����*/
    ui32 biYPelsPerMeter;
    /*λͼʹ�õ���ɫ��,���Ϊ0������ɫ��Ϊ2��biBitCount�η���0����*/
    ui32 biClrUsed;
    /*��Ҫ����ɫ����0����������ɫ����Ҫ��0����*/
    ui32 biClrImportant;
};

struct Pixel {
    ui8 b;
    ui8 g;
    ui8 r;
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
