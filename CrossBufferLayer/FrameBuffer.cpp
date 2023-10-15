#include "FrameBuffer.h"
#include "FontSupport.h"

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

	curX = CS_FB_INIT_CURX;
	curY = CS_FB_INIT_CURY;
}

void CS_FrameBuffer::ClearSelfBuffer(ui8 r, ui8 g, ui8 b)
{
    CS_Memset(redBuffer, r, width * height);
    CS_Memset(greenBuffer, g, width * height);
    CS_Memset(blueBuffer, b, width * height);

	curX = CS_FB_INIT_CURX;
	curY = CS_FB_INIT_CURY;
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

i32 CS_FrameBuffer::GetWidth()
{
	return width;
}

i32 CS_FrameBuffer::GetHeight()
{
	return height;
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
            xNow += CS_FONT_WIDTH;
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

void CS_FrameBuffer::LoadFromBMP(string fileName){
    CS_File file;
    file.Open(fileName, csReadBinary);
    file.Read();
    file.Close();

    BitmapHeader *header = (BitmapHeader*)(file.GetBufferPointer());
    Pixel        *pixel  = (Pixel*)(file.GetBufferPointer() + sizeof(BitmapHeader));

    curX = CS_FB_INIT_CURX;
    curY = CS_FB_INIT_CURY;

    width = header->biWidth;
    height = header->biHeight;

    AllocateBuffer(width, height);
    ClearSelfBuffer();

    for (i32 y = header->biHeight - 1; y >= 0; y--) {
        ui8* rpEnd = redBuffer + y * width + width;
        for (
            ui8 *rp = redBuffer + y * width,
                *gp = greenBuffer + y * width,
                *bp = blueBuffer + y * width;
            rp < rpEnd;
            rp++ && gp++ && bp++ && pixel++
        ) {
            *rp = pixel->r;
            *gp = pixel->g;
            *bp = pixel->b;
        }
    }
}
