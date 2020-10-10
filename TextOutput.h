#ifndef __FONT_H__
#define __FONT_H__
#include "Font.h"
#endif

#ifndef __CROSSBUFFER_H__
#define __CROSSBUFFER_H__
#include "CrossBuffer.h"
#endif

;

void DrawChar(FrameBuffer fb, int x, int y, int color, char ch)
{
	int* bitmapPointer;
	for (int deltaY = 0; deltaY < 16; deltaY++) {
		bitmapPointer = (int*)(Font + ((int)ch * 16 * 8) + (8 * deltaY));
		if (bitmapPointer[0] == 255) { SetPixel(fb, (x + 0), (y + deltaY), color); }
		if (bitmapPointer[1] == 255) { SetPixel(fb, (x + 1), (y + deltaY), color); }
		if (bitmapPointer[2] == 255) { SetPixel(fb, (x + 2), (y + deltaY), color); }
		if (bitmapPointer[3] == 255) { SetPixel(fb, (x + 3), (y + deltaY), color); }
		if (bitmapPointer[4] == 255) { SetPixel(fb, (x + 4), (y + deltaY), color); }
		if (bitmapPointer[5] == 255) { SetPixel(fb, (x + 5), (y + deltaY), color); }
		if (bitmapPointer[6] == 255) { SetPixel(fb, (x + 6), (y + deltaY), color); }
		if (bitmapPointer[7] == 255) { SetPixel(fb, (x + 7), (y + deltaY), color); }
	}
}

void DrawString(FrameBuffer fb, int x, int y, int color, char* stringPointer)
{
	int originX = x;
	for (; *stringPointer != 0x00; stringPointer++) {
		if (*stringPointer == '\n') {
			y += 16;
			x = originX;
			continue;
		}
		DrawChar(fb, x, y, color, *stringPointer); //画这个字符
		x += 8; //下一个字符X轴位置加8
		
	}
	return;
}

void DrawShadowString(FrameBuffer fb, int x, int y, char* stringPointer) {
	DrawString(fb, x,     y,     RGB888(0,   0,   0  ), stringPointer);
	DrawString(fb, x + 1, y + 1, RGB888(255, 255, 255), stringPointer);
}
