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

int clamp(int min, int input, int max) {
	if (input > min) {
		if (input < max) {
			return input;
		}
		else {
			return max;
		}
	}
	else {
		return min;
	}
}

void DrawVector4D(FrameBuffer fb, int width, int height, Vector4D* vec, int radius) {
	int CentralX = (int)vec->x;
	int CentralY = (int)vec->y;
	int StartX = clamp(0, CentralX - radius, width);
	int EndX   = clamp(0, CentralX + radius, width);
	int StartY = clamp(0, CentralY - radius, height);
	int EndY   = clamp(0, CentralY + radius, height);

	for (int y = StartY; y < EndY; y++) {
		for (int x = StartX; x < EndX; x++) {
			SetPixel(fb, x, y, CreateColor(255, 255, 255, 255));
		}
	}
}

Camera4D cam;
Matrix4D Morthoa, Morthob, Mortho, Mpersp2ortho, Mpersp, Mviewport, Mtransform;
Vector4D vecs[8];

void Setup(FrameBuffer fb, int width, int height, int deltaTime, Keyboard keyboard, Mouse mouse) {
	
	
	/*
	** Camera
	*/

	cam = CreateCamera4D(-0.1f, -1000.0f, 60.0f, width, height);


	/*
	** Mortho
	*/

	CalcCamera4DMatrices(&cam);
	Mtransform = cam.Mtransform;

	


	/*
	** Vectors
	*/

	vecs[0] = CreateVector4D(-1.0f, -1.0f, -3.0f, 1.0f);
	vecs[1] = CreateVector4D( 1.0f, -1.0f, -3.0f, 1.0f);
	vecs[2] = CreateVector4D( 1.0f,  1.0f, -3.0f, 1.0f);
	vecs[3] = CreateVector4D(-1.0f,  1.0f, -3.0f, 1.0f);
	vecs[4] = CreateVector4D(-1.0f, -1.0f, -5.0f, 1.0f);
	vecs[5] = CreateVector4D( 1.0f, -1.0f, -5.0f, 1.0f);
	vecs[6] = CreateVector4D( 1.0f,  1.0f, -5.0f, 1.0f);
	vecs[7] = CreateVector4D(-1.0f,  1.0f, -5.0f, 1.0f);
}


char* buffer;
char realbuffer[1000];
float deltaX = 0.0f, deltaY = 0.0f, deltaZ = 0.0f;
float sensitivity = 0.1f;

void Update(FrameBuffer fb, int width, int height, int deltaTime, Keyboard keyboard, Mouse mouse) {
	ClacFPS(fb, width, height, deltaTime);

	if (keyboard['W'] == TRUE) {
		deltaZ -= sensitivity;
	}
	if (keyboard['S'] == TRUE) {
		deltaZ += sensitivity;
	}

	if (keyboard['A'] == TRUE) {
		deltaX -= 0.5f * sensitivity;
	}
	if (keyboard['D'] == TRUE) {
		deltaX += 0.5f * sensitivity;
	}

	if (keyboard['E'] == TRUE) {
		deltaY -= 0.5f * sensitivity;
	}
	if (keyboard['Q'] == TRUE) {
		deltaY += 0.5f * sensitivity;
	}

	for (int i = 0; i < 8; i++) {
		vecs[i].x = vecs[i].x -= deltaX;
		vecs[i].y = vecs[i].y -= deltaY;
		vecs[i].z = vecs[i].z -= deltaZ;
	}

	for (int i = 0; i < 8; i++) {
		vecs[i] = Vector4DTimesMatrix4D(
			&(vecs[i]), &Mtransform
		);
	}

	for (int i = 0; i < 8; i++) {
		Vector4DDevidedByW(&(vecs[i]));
	}

	// Do Y-Axis Reverse
	for (int i = 0; i < 8; i++) {
		vecs[i].y = height - vecs[i].y;
	}

	sprintf_s(
		realbuffer, 1000,
		"n:%f\nf:%f\nt:%f\nb:%f\nl:%f\nr:%f\n",
		cam.n, cam.f, cam.t, cam.b, cam.l, cam.r
	);
	DrawShadowString(fb, width, height, 10, 42, realbuffer);

	buffer = OutputMatrix4D(&Mviewport);
	DrawShadowString(fb, width, height, 10, 154, buffer);
	free(buffer);

	buffer = OutputMatrix4D(&Mtransform);
	DrawShadowString(fb, width, height, 10, 234, buffer);
	free(buffer);

	for (int i = 0; i < 8; i++) {
		buffer = OutputVector4D(&(vecs[i]));
		DrawShadowString(fb, width, height, 10, 330 + i * 16, buffer);
		free(buffer);
	}

	for (int i = 0; i < 8; i++) {
		float tmp = (-1.0f * vecs[i].z) - 0.9f;
		DrawVector4D(fb, width, height, &(vecs[i]), (int)((0.1f - tmp) * 100.0f));
	}

	//buffer = OutputMatrix4D(&Mortho);
	//DrawShadowString(fb, width, height, 10, 314, buffer);
	//free(buffer);

	//buffer = OutputMatrix4D(&Mpersp2ortho);
	//DrawShadowString(fb, width, height, 10, 394, buffer);
	//free(buffer);

	//buffer = OutputMatrix4D(&Mpersp);
	//DrawShadowString(fb, width, height, 10, 474, buffer);
	//free(buffer);


	/*
	** Reset Vectors
	*/

	vecs[0] = CreateVector4D(-1.0f, -1.0f, -3.0f, 1.0f);
	vecs[1] = CreateVector4D( 1.0f, -1.0f, -3.0f, 1.0f);
	vecs[2] = CreateVector4D( 1.0f,  1.0f, -3.0f, 1.0f);
	vecs[3] = CreateVector4D(-1.0f,  1.0f, -3.0f, 1.0f);
	vecs[4] = CreateVector4D(-1.0f, -1.0f, -5.0f, 1.0f);
	vecs[5] = CreateVector4D( 1.0f, -1.0f, -5.0f, 1.0f);
	vecs[6] = CreateVector4D( 1.0f,  1.0f, -5.0f, 1.0f);
	vecs[7] = CreateVector4D(-1.0f,  1.0f, -5.0f, 1.0f);
}


void OnDestroy() {
	;
}
