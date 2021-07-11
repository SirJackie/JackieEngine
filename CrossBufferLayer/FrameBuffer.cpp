#include "FrameBuffer.h"
#include "FontSupport.h"
#pragma pack(push,1)

void CS_FrameBuffer::AllocateBuffer(i32 width, i32 height)
{
    redBuffer   = new ui8[width * height];
    greenBuffer = new ui8[width * height];
    blueBuffer  = new ui8[width * height];
}

void CS_FrameBuffer::DisAllocateBuffer()
{
    delete[] redBuffer;
    delete[] greenBuffer;
    delete[] blueBuffer;
}

void CS_FrameBuffer::ClearSelfBuffer()
{
    CS_Memset(redBuffer, 0, width * height);
    CS_Memset(greenBuffer, 0, width * height);
    CS_Memset(blueBuffer, 0, width * height);
}

void CS_FrameBuffer::ClearSelfBuffer(ui8 r, ui8 g, ui8 b)
{
    CS_Memset(redBuffer, r, width * height);
    CS_Memset(greenBuffer, g, width * height);
    CS_Memset(blueBuffer, b, width * height);
}

void CS_FrameBuffer::CopySameSizeBuffer(const CS_FrameBuffer& from, CS_FrameBuffer& to)
{
    if(  (from.width * from.height)  <  (to.width * to.height)  ){
        return;  // Too small to copy
    }

    ui8* frEnd = (ui8*)(from.redBuffer + width * height);

    for(
        ui8 *fr = from.redBuffer,
            *fg = from.greenBuffer,
            *fb = from.blueBuffer,
            *tr = to.redBuffer,
            *tg = to.greenBuffer,
            *tb = to.blueBuffer;

        fr < frEnd;
        fr++ && fg++ && fb++ && tr++ && tg++ && tb++
    ){
        *tr = *fr;
        *tg = *fg;
        *tb = *fb;
    }
}

CS_FrameBuffer::CS_FrameBuffer()
{
    curX = CS_FB_INIT_CURX;
    curY = CS_FB_INIT_CURY;

    width = height = 1;

    AllocateBuffer(1, 1);
    ClearSelfBuffer();
}

CS_FrameBuffer::CS_FrameBuffer(i32 Width_, i32 Height_)
{
    curX = CS_FB_INIT_CURX;
    curY = CS_FB_INIT_CURY;

    width  = Width_;
    height = Height_;

    AllocateBuffer(width, height);
    ClearSelfBuffer();
}

CS_FrameBuffer::CS_FrameBuffer(const CS_FrameBuffer& fb)
{
    width  = fb.width;
    height = fb.height;

    curX = fb.curX;
    curY = fb.curY;

    AllocateBuffer(width, height);
    CopySameSizeBuffer(fb, (*this));
}

CS_FrameBuffer& CS_FrameBuffer::operator=(const CS_FrameBuffer& fb)
{
    DisAllocateBuffer();

    width = fb.width;
    height = fb.height;

    curX = fb.curX;
    curY = fb.curY;

    AllocateBuffer(width, height);
    CopySameSizeBuffer(fb, (*this));

    return (*this);  // Support a = b = c
}

CS_FrameBuffer::~CS_FrameBuffer()
{
    DisAllocateBuffer();
}

void CS_FrameBuffer::DrawChar
(
    const char& ch, const i32 xStart, const i32 yStart,
    const ui8 r, const ui8 g, const ui8 b
)
{
    ui8* chBmStartPtr = ((ui8*)CS_font + 16 * 8 * ch);
    ui8* redBufStartPtr = redBuffer;
    ui8* grnBufStartPtr = greenBuffer;
    ui8* bluBufStartPtr = blueBuffer;

    i32 xMin = CS_iclamp(0, xStart, width);
    i32 yMin = CS_iclamp(0, yStart, height);
    i32 xMax = CS_iclamp(0, xStart + CS_FONT_WIDTH, width);
    i32 yMax = CS_iclamp(0, yStart + CS_FONT_HEIGHT, height);

    i32 deltaY = yMin-yStart;
    ui8* chBmPtr = chBmStartPtr + deltaY * CS_FONT_WIDTH;
    ui8* redBufPtr = redBufStartPtr + deltaY * width;
    ui8* grnBufPtr = grnBufStartPtr + deltaY * width;
    ui8* bluBufPtr = bluBufStartPtr + deltaY * width;

    for (i32 y = yMin; y < yMax; y++) {
        i32 deltaY = (y - yStart);
        chBmPtr = chBmStartPtr + deltaY * CS_FONT_WIDTH;
        redBufPtr = redBufStartPtr + y * width + xMin;
        grnBufPtr = grnBufStartPtr + y * width + xMin;
        bluBufPtr = bluBufStartPtr + y * width + xMin;

        for (i32 x = xMin; x < xMax; x++) {
            if (*chBmPtr != 0) *redBufPtr = r;
            if (*chBmPtr != 0) *grnBufPtr = g;
            if (*chBmPtr != 0) *bluBufPtr = b;

            chBmPtr++;
            redBufPtr++;
            grnBufPtr++;
            bluBufPtr++;
        }
    }
}

void CS_FrameBuffer::DrawString
(
    const i8* str, const i32 x, const i32 y,
    const ui8 r, const ui8 g, const ui8 b
)
{
    i32 xNow = x, yNow = y;
    i8* charNow = (i8*)str;
    while (*charNow != 0) {
        DrawChar(*charNow, xNow, yNow, r, g, b);
        charNow++;
        if ((xNow + CS_FONT_WIDTH) > width) {
            yNow += CS_FONT_HEIGHT;
            xNow = x;
        }
        else {
            xNow+= CS_FONT_WIDTH;
        }
    }
}

void CS_FrameBuffer::DrawBuffer(CS_FrameBuffer& from, i32 toXStart, i32 toYStart){
    CS_FrameBuffer& to = *this;
    i32 fromXStart = 0;
    i32 fromYStart = 0;

    // Start Calculating Borders
    i32 toYEnd, toXEnd;

    if(toYStart < 0){
        i32 deltaY = -toYStart;
        toYStart = 0;
        fromYStart += deltaY;
        toYEnd = CS_iclamp(toYStart, toYStart + from.height - deltaY, to.height);
    }
    else{
        toYEnd = CS_iclamp(toYStart, toYStart + from.height, to.height);
    }

    if(toXStart < 0){
        i32 deltaX = -toXStart;
        toXStart = 0;
        fromXStart += deltaX;
        toXEnd = CS_iclamp(toXStart, toXStart + from.width - deltaX, to.width);
    }
    else{
        toXEnd = CS_iclamp(toXStart, toXStart + from.width, to.width);
    }

    // Drawing
    for(i32 toY = toYStart, fromY = fromYStart; toY < toYEnd; toY++ && fromY++){
        i32 toPosition = toY * to.width + toXStart;
        i32 fromPosition = fromY * from.width + fromXStart;
        i32 toPositionEnd = toY * to.width + toXEnd;
        ui8 *trEnd = to.redBuffer + toPositionEnd;
        for(
            ui8 *tr = to.redBuffer + toPosition,
                *tg = to.greenBuffer + toPosition,
                *tb = to.blueBuffer + toPosition,
                *fr = from.redBuffer + fromPosition,
                *fg = from.greenBuffer + fromPosition,
                *fb = from.blueBuffer + fromPosition;
            tr < trEnd;
            tr++ && tg++ && tb++ && fr++ && fg++ && fb++
        ){
            
            *tr = *fr; *tg = *fg; *tb = *fb;
        }
    }
}

void CS_FrameBuffer::Print(const i8* str)
{
    i8* charNow = (i8*)str;
    while (*charNow != 0) {
        if (*charNow == '\n') {
            curY += CS_FONT_HEIGHT;
            curX = CS_FB_INIT_CURX;
            charNow++;
        }
        else{
            DrawChar(*charNow, curX + 1, curY + 1, 0, 0, 0);
            DrawChar(*charNow, curX, curY, 255, 255, 255);
            charNow++;
            if ((curX + CS_FONT_WIDTH * 2) > width) {
                curY += CS_FONT_HEIGHT;
                curX = CS_FB_INIT_CURX;
            }
            else {
                curX += CS_FONT_WIDTH;
            }
        }
    }
}

void CS_FrameBuffer::Print(csbool csb){
    if(csb == csFalse){
        Print("False");
    }
    else{
        Print("True");
    }
}

void CS_FrameBuffer::Print(string str)
{
    Print(str.c_str());
}

struct BitmapFileHeader{
	/*定义为'BM'，标识bmp文件*/
    ui16 bfType;
    /*整个BMP文件的大小*/
    ui32 bfSize;
    ui16 bfReserved1;
    ui16 bfReserved2;
    /*偏移数，即 位图文件头+位图信息头+调色板 的大小*/
    ui32 bfOffBits;
};

struct BitmapInfoHeader{
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

struct Pixel{
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

void CS_FrameBuffer::LoadFromBMP(string fileName){
    CS_File file;
    file.Open(fileName, csReadBinary);
    file.Read();
    file.Close();

    BitmapFileHeader *fileHeader = (BitmapFileHeader*)(file.buffer);
    BitmapInfoHeader *infoHeader = (BitmapInfoHeader*)(fileHeader + sizeof(BitmapFileHeader));
    Pixel            *pixel      = (Pixel*)(infoHeader + sizeof(BitmapInfoHeader));

    BitmapHeader *header = (BitmapHeader*)file.buffer;

    this->PrintLn(sizeof(BitmapHeader));
    this->PrintLn(sizeof(BitmapInfoHeader) + sizeof(BitmapFileHeader));
    this->PrintLn((i32)header->biPlanes);
}
