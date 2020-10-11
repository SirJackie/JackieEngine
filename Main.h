/*
** This is a Demo of CrossBuffer
** You can change everything if you like
*/

#ifndef __CROSSBUFFER_H__
#define __CROSSBUFFER_H__
#include "CrossBuffer.h"
#endif

#ifndef __TEXTOUTPUT_H__
#define __TEXTOUTPUT_H__
#include "TextOutput.h"
#endif

#ifndef __INPUT_H__
#define __INPUT_H__
#include "Input.h"
#endif

#ifndef __JACKIE_ENGINE_H__
#define __JACKIE_ENGINE_H__
#include "JackieEngineLibraries/JackieEngine.h"
#endif

#ifndef __STDIO_H__
#define __STDIO_H__
#include <stdio.h>
#endif


/*
** FPS Calculating
*/
float FPS = 0;
int   deltaTimeCount;
int   frameCount;
char  buffer[1000];

void CalcFPS(FrameBuffer fb, int deltaTime, char* buffer, int bufferLength) {
	/*
	** FPS Processing
	*/

	/* Calculate FPS */
	deltaTimeCount += deltaTime;
	frameCount += 1;

	if (deltaTimeCount > 1000) {
		FPS = (float)frameCount / ((float)deltaTimeCount / 1000);
		deltaTimeCount -= 1000;
		frameCount = 0;
	}

	/* Show FPS On Screen */
	sprintf_s(
		buffer,
		bufferLength,
		"FPS: %f; DeltaTime: %d",
		FPS,
		deltaTime
	);
	DrawShadowString(fb, 10, 10, buffer);
}


/*
** On Create Callback Function
*/
void OnCreate() {
	;
}

Vector4D vec;

/*
** Setup Callback Function
*/
void Setup(FrameBuffer fb, int width, int height, int deltaTime, Keyboard keyboard, Mouse mouse) {
	vec = CreateVector4D(2, 3, 4, 1);
}


/*
** Update Callback Function
*/
void Update(FrameBuffer fb, int width, int height, int deltaTime, Keyboard keyboard, Mouse mouse) {
	CalcFPS(fb, deltaTime, buffer, 1000);

	OutputVector4D(buffer, 1000, &vec);
	DrawShadowString(fb, 10, 26, buffer);
}

void OnDestroy() {
	;
}
