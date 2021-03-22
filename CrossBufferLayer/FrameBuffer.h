#ifndef __CSBF_FrameBuffer__
#define __CSBF_FrameBuffer__

#include "FontSupport.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

/*
** Define Cross Platform Types
*/

#define ui32                                 unsigned int    // Should be 32-bit 4-byte no sign
#define i32                                  signed   int    // Should be 32-bit 4-byte have sign

#define ui16                                 unsigned short  // Should be 16-bit 2-byte no sign
#define i16                                  signed   short  // Should be 16-bit 2-byte have sign

#define ui8                                  unsigned char   // Should be 16-bit 2-byte no sign
#define i8                                   signed   char   // Should be 16-bit 2-byte have sign

#define f64                                  double          // Should be 64-bit 8-byte float
#define f32                                  float           // Should be 32-bit 4-byte float


/*
** Define Mathematics Functions
*/

#ifndef __MathSupport_Clamp__
#define __MathSupport_Clamp__
int   clamp (int   min, int   input, int   max);
float fclamp(float min, float input, float max);
#endif


/*
** Define Color and Functions for Color
** -------------------------------------------------------------------
** You have to notice that in order to increase the speed of program,
** The type 'Color' is not defined by Class and Object
** We just use #define to process color before running
*/

#define Color                                ui32
#define CreateColor(r, g, b)                 ((Color) (( (0xff) << 24)  |  (((r)&0xff) << 16)  |  (((g)&0xff) << 8)  |  ((b) & 0xff) ))

#define GetColorR(color)                     ( ( (color) >> 16) & 0xff)
#define GetColorG(color)                     ( ( (color) >> 8 ) & 0xff)
#define GetColorB(color)                     ( ( (color)      ) & 0xff)

#define SetColorR(color, r)                  ( (color) = ( (color)  & 0xFF00FFFF) | ( ((r) & 0xff) << 16) )
#define SetColorG(color, g)                  ( (color) = ( (color)  & 0xFFFF00FF) | ( ((g) & 0xff) <<  8) )
#define SetColorB(color, b)                  ( (color) = ( (color)  & 0xFFFFFF00) | ( ((b) & 0xff)      ) )

#define GetPixel(fb, x, y)                   (((Color*)(fb).pBits)[(x) + (fb.Pitch) * (y)])
#define SetPixel(fb, x, y, color)            (((Color*)(fb).pBits)[(x) + (fb.Pitch) * (y)] = color)
#define GetPixelLB(fb, height, x, y)         (((Color*)(fb).pBits)[(x) + (fb.Pitch) * (height-(y))])
#define SetPixelLB(fb, height, x, y, color)  (((Color*)(fb).pBits)[(x) + (fb.Pitch) * (height-(y))] = color)


/*
** Define FrameBuffer
** -------------------------------------------------------------------
** FrameBuffer is the object for controling the screen
** You can draw whatever you want on FrameBuffer,
** Then the HardwareSimuLayer will automatically help you
** to draw it on the screen.
*/

#define INIT_CUR_X   10
#define INIT_CUR_Y   10
#define TEXT_WIDTH   8
#define TEXT_HEIGHT  16

class FrameBuffer
{
public:
    // Basic Informations
    int   Width;
    int   Height;
    int   Pitch;
    void* pBits;
    bool  externalBits;

    // Text Cursor
    int   CurX;
    int   CurY;
    int   InitCurX;
    int   InitCurY;

    // Bitmap Loading Require
    bool wannaLoadBitmap;
    string bitmapAddress;

    // Special Methods
    FrameBuffer();
    FrameBuffer(int Width_, int Height_, int Pitch_, Color* pBits_);
    FrameBuffer(int Width_, int Height_);
    FrameBuffer(const FrameBuffer& fb);
    FrameBuffer& operator=(const FrameBuffer& fb);
    ~FrameBuffer();
   

    // Methods
	void DrawChar          (int x, int y, Color color, char ch);
    void DrawString        (Color color, const char* stringPointer);
    void DrawBuffer        (const FrameBuffer& fb, int PositionX, int PositionY);
    void Draw              (const char* stringPointer);
    void Draw              (const FrameBuffer& fb);
    void AllocateBuffer    (int width, int height);
    void DisAllocateBuffer ();
    void InitCursor        ();
    void ClearBuffer       ();
    void LoadBMP           (string bitmapAddress_, vector<FrameBuffer*>& fbLoadingQueue);
};

#endif
