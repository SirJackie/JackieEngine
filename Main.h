#pragma once

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

#ifndef __FPS_H__
#define __FPS_H__
#include "FPS.h"
#endif


void OnCreate() {
	;
}


void Setup(FrameBuffer fb, int width, int height, int deltaTime, Keyboard keyboard, Mouse mouse) {
	;
}

Vector4D vec;
Matrix4D mat;
char* buffer;
char realbuffer[1000];

void Update(FrameBuffer fb, int width, int height, int deltaTime, Keyboard keyboard, Mouse mouse) {
	
	/*
	** Vector4D And Matrix4D Basic Test
	**/

	vec = CreateVector4D(1.1f, 1.2f, 1.3f, 1.0f);
	buffer = OutputVector4D(&vec);
	DrawShadowString(fb, width, height, 10, 10, buffer);
	free(buffer);

	mat = CreateMatrix4D(
		1.1f, 1.2f, 1.3f, 1.4f,
		2.1f, 2.2f, 2.3f, 2.4f,
		3.1f, 3.2f, 3.3f, 3.4f,
		4.1f, 4.2f, 4.3f, 4.4f
	);
	buffer = OutputMatrix4D(&mat);
	DrawShadowString(fb, width, height, 10, 42, buffer);
	free(buffer);

	Vector4D vtmp = Vector4DTimesMatrix4D(&vec, &mat);
	Matrix4D mtmp = Matrix4DTimesMatrix4D(&mat, &mat);
	buffer = OutputVector4D(&vtmp);
	DrawShadowString(fb, width, height, 10, 122, buffer);
	free(buffer);
	buffer = OutputMatrix4D(&mtmp);
	DrawShadowString(fb, width, height, 10, 154, buffer);
	free(buffer);


	/*
	** Vector4D Length And Normalize Test
	*/

	Vector4D v1, v2, v3;

	v1 = CreateVector4D(1.0f, 1.0f, 1.0f, 1.0f);
	sprintf_s(realbuffer, 1000, "LengthOfVector4D(v1) = %f", LengthOfVector4D(&v1));
	DrawShadowString(fb, width, height, 10, 234, realbuffer);

	v1 = NormalizedVector4D(&v1);
	sprintf_s(realbuffer, 1000, "LengthOfVector4D(v1) = %f", LengthOfVector4D(&v1));
	DrawShadowString(fb, width, height, 10, 266, realbuffer);

	buffer = OutputVector4D(&v1);
	DrawShadowString(fb, width, height, 10, 298, buffer);
	free(buffer);


	/*
	** Vector4D-Vector4D Calculation
	*/

	v1 = CreateVector4D(1.0f, 2.0f, 3.0f, 1.0f);
	v2 = CreateVector4D(3.0f, 2.0f, 1.0f, 1.0f);

	v3 = Vector4DAddVector4D(&v1, &v2);
	buffer = OutputVector4D(&v3);
	DrawShadowString(fb, width, height, 10, 346, buffer);
	free(buffer);

	v3 = Vector4DMinusVector4D(&v1, &v2);
	buffer = OutputVector4D(&v3);
	DrawShadowString(fb, width, height, 10, 378, buffer);
	free(buffer);

	v1 = CreateVector4D(1.0f, 0.0f, 0.0f, 1.0f);
	v2 = CreateVector4D(0.0f, 1.0f, 0.0f, 1.0f);

	float dotresult = Vector4DDotVector4D(&v1, &v2);
	sprintf_s(
		realbuffer, 1000,
		"DotResult: %f", dotresult
	);
	DrawShadowString(fb, width, height, 10, 410, realbuffer);

	v3 = Vector4DCrossVector4D(&v1, &v2);
	buffer = OutputVector4D(&v3);
	DrawShadowString(fb, width, height, 10, 442, buffer);
	free(buffer);
}


void OnDestroy() {
	;
}
