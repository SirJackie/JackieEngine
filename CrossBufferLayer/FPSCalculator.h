#ifndef __CSBF_FPSCalculator
#define __CSBF_FPSCalculator

#include "IOSupport.h"
#include <stdio.h>
#define FPS_BUFFER_LENGTH 128

/*
** FPS Calculating
*/
float FPS = 0;
int   FPSDeltaTimeCount;
int   FPSFrameCount;
char  FPSBuffer[FPS_BUFFER_LENGTH];

void CalcFPS(FrameBuffer fb, int deltaTime) {
	/*
	** FPS Processing
	*/

	/* Calculate FPS */
	FPSDeltaTimeCount += deltaTime;
	FPSFrameCount += 1;

	if (FPSDeltaTimeCount > 1000) {
		FPS = (float)FPSFrameCount / ((float)FPSDeltaTimeCount / 1000);
		FPSDeltaTimeCount -= 1000;
		FPSFrameCount = 0;
	}

	/* Show FPS On Screen */
	sprintf_s(
		FPSBuffer,
		FPS_BUFFER_LENGTH,
		"FPS: %f; DeltaTime: %d; Width: %d; Height: %d; Pitch: %d; pBits: %p",
		FPS,
		deltaTime,
		fb.Width,
		fb.Height,
		fb.Pitch,
		fb.pBits
	);
	DrawShadowString(fb, 10, 10, FPSBuffer);
}


#endif
