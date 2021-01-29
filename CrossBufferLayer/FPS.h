#ifndef __CSBF_FPS
#define __CSBF_FPS


#include "CrossBuffer.h"
#define FPS_BUFFER_LENGTH 128

/*
** FPS Calculating
*/
float FPS = 0;
int   FPSDeltaTimeCount;
int   FPSFrameCount;
char  FPSBuffer[FPS_BUFFER_LENGTH];

void CalcFPS(FrameBuffer fb, int width, int height, int deltaTime) {
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
		"FPS: %f; DeltaTime: %d; Width: %d; Height: %d",
		FPS,
		deltaTime,
		width,
		height
	);
	DrawShadowString(fb, width, height, 10, 10, FPSBuffer);
}


#endif
