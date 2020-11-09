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


Camera4D cam;
Matrix4D Morthoa, Morthob, Mortho, Mpersp2ortho, Mpersp;

void Setup(FrameBuffer fb, int width, int height, int deltaTime, Keyboard keyboard, Mouse mouse) {
	
	
	/*
	** Camera
	*/

	cam.n = -0.1f;
	cam.f = -1000.0f;
	cam.fovY = 60.0f;
	cam.ScreenWidth = width;
	cam.ScreenHeight = height;

	cam.t = abs(cam.n) * tand(cam.fovY / 2.0f);
	cam.b = -1.0f * cam.t;

	cam.r = cam.ScreenWidth * cam.t / cam.ScreenHeight;
	cam.l = -1.0 * cam.r;


	/*
	** Mortho
	*/

	Morthoa = CreateMatrix4D(
		1.0f, 0.0f, 0.0f, -1 * (cam.r + cam.l) / 2.0f,
		0.0f, 1.0f, 0.0f, -1 * (cam.t + cam.b) / 2.0f,
		0.0f, 0.0f, 1.0f, -1 * (cam.n + cam.f) / 2.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	Morthob = CreateMatrix4D(
		2.0f / (cam.r - cam.l), 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / (cam.t - cam.b), 0.0f, 0.0f,
		0.0f, 0.0f, 2.0f / (cam.n - cam.f), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	Mortho = Matrix4DTimesMatrix4D(
		&Morthoa,
		&Morthob
	);

	Mpersp2ortho = CreateMatrix4D(
		cam.n, 0.0f, 0.0f, 0.0f,
		0.0f, cam.n, 0.0f, 0.0f,
		0.0f, 0.0f, cam.f + cam.n, -1 * cam.f * cam.n,
		0.0f, 0.0f, 1.0f, 0.0f
	);

	Mpersp = Matrix4DTimesMatrix4D(
		&Mpersp2ortho,
		&Mortho
	);
}


char* buffer;
char realbuffer[1000];

void Update(FrameBuffer fb, int width, int height, int deltaTime, Keyboard keyboard, Mouse mouse) {
	ClacFPS(fb, width, height, deltaTime);

	sprintf_s(
		realbuffer, 1000,
		"n:%f\nf:%f\nt:%f\nb:%f\nl:%f\nr:%f\n",
		cam.n, cam.f, cam.t, cam.b, cam.l, cam.r
	);
	DrawShadowString(fb, width, height, 10, 42, realbuffer);

	buffer = OutputMatrix4D(&Morthoa);
	DrawShadowString(fb, width, height, 10, 154, buffer);
	free(buffer);

	buffer = OutputMatrix4D(&Morthob);
	DrawShadowString(fb, width, height, 10, 234, buffer);
	free(buffer);

	buffer = OutputMatrix4D(&Mortho);
	DrawShadowString(fb, width, height, 10, 314, buffer);
	free(buffer);

	buffer = OutputMatrix4D(&Mpersp2ortho);
	DrawShadowString(fb, width, height, 10, 394, buffer);
	free(buffer);

	buffer = OutputMatrix4D(&Mpersp);
	DrawShadowString(fb, width, height, 10, 474, buffer);
	free(buffer);
}


void OnDestroy() {
	;
}
