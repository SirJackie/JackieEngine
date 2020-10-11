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

Vector4D vector;
Matrix4D matrix;

/*
** Setup Callback Function
*/
void Setup(FrameBuffer fb, int width, int height, int deltaTime, Keyboard keyboard, Mouse mouse) {
	vector = CreateVector4D(2, 3, 4, 1);
	matrix = CreateMatrix4D(
		 1.0f,   2.0f,   3.0f,   4.0f,
		 5.0f,   6.0f,   7.0f,   8.0f,
		 9.0f,  10.0f,  11.0f,  12.0f,
		13.0f,  14.0f,  15.0f,  16.0f
	);
}


/*
** Update Callback Function
*/
void Update(FrameBuffer fb, int width, int height, int deltaTime, Keyboard keyboard, Mouse mouse) {
	CalcFPS(fb, deltaTime, buffer, 1000);

	OutputVector4D(buffer, 1000, &vector);
	DrawShadowString(fb, 10, 42, buffer);

	OutputMatrix4D(buffer, 1000, &matrix);
	DrawShadowString(fb, 10, 122, buffer);

	Vector4D result;
	result = Matrix4D_X_Vector4D(&matrix, &vector);
	OutputVector4D(buffer, 1000, &result);
	DrawShadowString(fb, 10, 202, buffer);
}

void OnDestroy() {
	;
}
