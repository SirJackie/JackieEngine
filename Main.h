#ifndef __STDIO_H__
#define __STDIO_H__
#include <stdio.h>
#endif

#ifndef __MATH_H__
#define __MATH_H__
#include <math.h>
#endif

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

#ifndef __FPS_H__
#define __FPS_H__
#include "FPS.h"
#endif


/*
** OnCreate()
*/

void OnCreate() {
	;
}


Matrix4D CreateRotationMatrix(float rotx, float roty, float rotz) {
	Matrix4D MrotationX = CreateMatrix4D(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cosd(rotx), -1.0f * sind(rotx), 0.0f,
		0.0f, sind(rotx), cosd(rotx), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	Matrix4D MrotationY = CreateMatrix4D(
		cosd(roty), 0.0f, sind(roty), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-1.0f * sind(roty), 0.0f, cosd(roty), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	Matrix4D MrotationZ = CreateMatrix4D(
		cosd(rotz), -1.0f * sind(rotz), 0.0f, 0.0f,
		sind(rotz), cosd(rotz), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	Matrix4D Mrotation = Matrix4DTimesMatrix4D(
		&MrotationX,
		&MrotationY
	);

	Mrotation = Matrix4DTimesMatrix4D(
		&(Mrotation),
		&MrotationZ
	);

	return Mrotation;
}

Camera4D cam;
Vector4D vecs[8];

void Setup(FrameBuffer fb, int width, int height, int deltaTime, Keyboard keyboard, Mouse mouse) {
	
	
	/*
	** Camera
	*/

	cam = CreateCamera4D(
		0.0f, 0.0f, 7.0f, 0.0f, 0.0f, 0.0f,
		-0.1f, -1000.0f, 60.0f, width, height
	);
	CalcCamera4DMatrices(&cam);


	/*
	** Vectors
	*/

	vecs[0] = CreateVector4D(-1.0f, -1.0f,  1.0f, 1.0f);
	vecs[1] = CreateVector4D( 1.0f, -1.0f,  1.0f, 1.0f);
	vecs[2] = CreateVector4D( 1.0f,  1.0f,  1.0f, 1.0f);
	vecs[3] = CreateVector4D(-1.0f,  1.0f,  1.0f, 1.0f);
	vecs[4] = CreateVector4D(-1.0f, -1.0f, -1.0f, 1.0f);
	vecs[5] = CreateVector4D( 1.0f, -1.0f, -1.0f, 1.0f);
	vecs[6] = CreateVector4D( 1.0f,  1.0f, -1.0f, 1.0f);
	vecs[7] = CreateVector4D(-1.0f,  1.0f, -1.0f, 1.0f);
}


char* buffer;
char realbuffer[1000];
float deltaX = 0.0f, deltaY = 0.0f, deltaZ = 0.0f;
float sensitivity = 0.005f;
BOOL rotOrNot = TRUE;
float rotdeg = 0.0f;
int KeyDelay = 0;

void Update(FrameBuffer fb, int width, int height, int deltaTime, Keyboard keyboard, Mouse mouse) {
	CalcFPS(fb, width, height, deltaTime);

	/*
	** Position Responder
	*/

	if (keyboard['W'] == TRUE) {
		cam.position.z -= sensitivity * deltaTime;
	}
	if (keyboard['S'] == TRUE) {
		cam.position.z += sensitivity * deltaTime;
	}

	if (keyboard['A'] == TRUE) {
		cam.position.x -= 0.5f * sensitivity * deltaTime;
	}
	if (keyboard['D'] == TRUE) {
		cam.position.x += 0.5f * sensitivity * deltaTime;
	}

	if (keyboard['E'] == TRUE) {
		cam.position.y -= 0.5f * sensitivity * deltaTime;
	}
	if (keyboard['Q'] == TRUE) {
		cam.position.y += 0.5f * sensitivity * deltaTime;
	}


	/*
	** Rotation Responder
	*/

	if (keyboard['I'] == TRUE) {
		cam.rotation.x -= 5.0f * sensitivity * deltaTime;
	}
	if (keyboard['K'] == TRUE) {
		cam.rotation.x += 5.0f * sensitivity * deltaTime;
	}

	if (keyboard['J'] == TRUE) {
		cam.rotation.y -= 5.0f * sensitivity * deltaTime;
	}
	if (keyboard['L'] == TRUE) {
		cam.rotation.y += 5.0f * sensitivity * deltaTime;
	}

	if (keyboard['U'] == TRUE) {
		cam.rotation.z -= 5.0f * sensitivity * deltaTime;
	}
	if (keyboard['O'] == TRUE) {
		cam.rotation.z += 5.0f * sensitivity * deltaTime;
	}

	if (keyboard['R'] == TRUE && KeyDelay == 0) {
		rotOrNot = !(rotOrNot);
		KeyDelay = 10;
	}

	if (KeyDelay > 0) {
		KeyDelay -= 1;
	}


	/*
	** Refresh Camera Matrices
	*/

	RefreshCamera4DMatrices(&cam);


	/*
	** Rotate the Vectors
	*/

	Matrix4D Mrotation = CreateRotationMatrix(rotdeg, -30.0f, rotdeg);
	//Matrix4D Mrotation = CreateRotationMatrix(0.0f, 0.0f, 0.0f);
	if (rotOrNot) {
		rotdeg += 0.03f * deltaTime;
	}
	if (rotdeg >= 360.0f) {
		rotdeg = 0.0f;
	}

	for (int i = 0; i < 8; i++) {
		vecs[i] = Vector4DTimesMatrix4D(
			&(vecs[i]), &(Mrotation)
		);
	}


	/*
	** Do Projection
	*/

	for (int i = 0; i < 8; i++) {
		vecs[i] = Vector4DTimesMatrix4D(
			&(vecs[i]), &(cam.Mtranslation)
		);
	}

	for (int i = 0; i < 8; i++) {
		vecs[i] = Vector4DTimesMatrix4D(
			&(vecs[i]), &(cam.Mrotation)
		);
	}

	for (int i = 0; i < 8; i++) {
		buffer = OutputVector4D(&(vecs[i]));
		DrawShadowString(fb, width, height, 10, 154 + i * 16, buffer);
		free(buffer);
	}

	for (int i = 0; i < 8; i++) {
		vecs[i] = Vector4DTimesMatrix4D(
			&(vecs[i]), &(cam.MprojAndviewport)
		);
	}

	for (int i = 0; i < 8; i++) {
		Vector4DDevidedByW(&(vecs[i]));
	}


	/*
	** Output Things
	*/

	sprintf_s(
		realbuffer, 1000,
		"n:%f\nf:%f\nt:%f\nb:%f\nl:%f\nr:%f\n",
		cam.n, cam.f, cam.t, cam.b, cam.l, cam.r
	);
	DrawShadowString(fb, width, height, 10, 42, realbuffer);

	buffer = OutputMatrix4D(&(cam.Mtransform));
	DrawShadowString(fb, width, height, 10, 314, buffer);
	free(buffer);

	buffer = OutputVector4D(&(cam.position));
	DrawShadowString(fb, width, height, 10, 394, buffer);
	free(buffer);

	buffer = OutputVector4D(&(cam.rotation));
	DrawShadowString(fb, width, height, 10, 410, buffer);
	free(buffer);

	for (int i = 0; i < 8; i++) {
		buffer = OutputVector4D(&(vecs[i]));
		DrawShadowString(fb, width, height, 10, 458 + i * 16, buffer);
		free(buffer);
	}

	//for (int i = 0; i < 8; i++) {
	//	float tmp = (-1.0f * vecs[i].z) - 0.9f;
	//	DrawVector4D(fb, width, height, &(vecs[i]), (int)((0.1f - tmp) * 100.0f));
	//}

	float* ZBuffer = (float*)malloc(sizeof(float) * width * height);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			ZBuffer[y * width + x] = cam.f;
		}
	}

	DrawFlatMesh4D(fb, width, height, &(vecs[0]), &(vecs[1]), &(vecs[3]), CreateColor(255, 0, 255, 255), ZBuffer);
	DrawFlatMesh4D(fb, width, height, &(vecs[2]), &(vecs[3]), &(vecs[1]), CreateColor(255, 255, 0, 255), ZBuffer);
	DrawFlatMesh4D(fb, width, height, &(vecs[5]), &(vecs[4]), &(vecs[6]), CreateColor(255, 255, 255, 255), ZBuffer);
	DrawFlatMesh4D(fb, width, height, &(vecs[7]), &(vecs[6]), &(vecs[4]), CreateColor(255, 255, 255, 255), ZBuffer);
	DrawFlatMesh4D(fb, width, height, &(vecs[4]), &(vecs[0]), &(vecs[7]), CreateColor(255, 255, 255, 255), ZBuffer);
	DrawFlatMesh4D(fb, width, height, &(vecs[3]), &(vecs[7]), &(vecs[0]), CreateColor(255, 255, 255, 255), ZBuffer);
	//DrawFlatMesh4D(fb, width, height, &(vecs[1]), &(vecs[5]), &(vecs[2]), CreateColor(255, 255, 255, 255), ZBuffer);
	//DrawFlatMesh4D(fb, width, height, &(vecs[6]), &(vecs[2]), &(vecs[5]), CreateColor(255, 255, 255, 255), ZBuffer);
	//DrawFlatMesh4D(fb, width, height, &(vecs[3]), &(vecs[2]), &(vecs[7]), CreateColor(255, 255, 255, 255), ZBuffer);
	//DrawFlatMesh4D(fb, width, height, &(vecs[6]), &(vecs[7]), &(vecs[2]), CreateColor(255, 255, 255, 255), ZBuffer);
	//DrawFlatMesh4D(fb, width, height, &(vecs[5]), &(vecs[0]), &(vecs[4]), CreateColor(255, 255, 255, 255), ZBuffer);
	//DrawFlatMesh4D(fb, width, height, &(vecs[5]), &(vecs[1]), &(vecs[0]), CreateColor(255, 255, 255, 255), ZBuffer);


	/*
	** Reset Vectors
	*/

	vecs[0] = CreateVector4D(-1.0f, -1.0f,  1.0f, 1.0f);
	vecs[1] = CreateVector4D( 1.0f, -1.0f,  1.0f, 1.0f);
	vecs[2] = CreateVector4D( 1.0f,  1.0f,  1.0f, 1.0f);
	vecs[3] = CreateVector4D(-1.0f,  1.0f,  1.0f, 1.0f);
	vecs[4] = CreateVector4D(-1.0f, -1.0f, -1.0f, 1.0f);
	vecs[5] = CreateVector4D( 1.0f, -1.0f, -1.0f, 1.0f);
	vecs[6] = CreateVector4D( 1.0f,  1.0f, -1.0f, 1.0f);
	vecs[7] = CreateVector4D(-1.0f,  1.0f, -1.0f, 1.0f);

	free(ZBuffer);
}


void OnDestroy() {
	;
}
