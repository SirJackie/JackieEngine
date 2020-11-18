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
** Global Variables
*/

Camera4D  cam;
Vector4D  vecs[8];
Matrix4D  Mrotation;
char*     buffer;
char      realbuffer[1000];
float     keyboardSensitivity  = 0.005f;
BOOL      rotateOrNot          = TRUE;
float     rotateDegree         = 0.0f;
int       rotateKeyDelay       = 0;


/*
** OnCreate()
*/

void OnCreate() {
	;
}


/*
** Setup()
*/

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


/*
** Update()
*/

void Update(FrameBuffer fb, int width, int height, int deltaTime, Keyboard keyboard, Mouse mouse) {
	

	/*
	** Calculating FPS
	*/

	CalcFPS(fb, width, height, deltaTime);


	/*
	** Position Responder
	*/

	if (keyboard['W'] == TRUE) {
		cam.position.z -= 1.0f * keyboardSensitivity * deltaTime;
	}
	if (keyboard['S'] == TRUE) {
		cam.position.z += 1.0f * keyboardSensitivity * deltaTime;
	}

	if (keyboard['A'] == TRUE) {
		cam.position.x -= 0.5f * keyboardSensitivity * deltaTime;
	}
	if (keyboard['D'] == TRUE) {
		cam.position.x += 0.5f * keyboardSensitivity * deltaTime;
	}

	if (keyboard['E'] == TRUE) {
		cam.position.y -= 0.5f * keyboardSensitivity * deltaTime;
	}
	if (keyboard['Q'] == TRUE) {
		cam.position.y += 0.5f * keyboardSensitivity * deltaTime;
	}


	/*
	** Rotation Responder
	*/

	if (keyboard['I'] == TRUE) {
		cam.rotation.x -= 5.0f * keyboardSensitivity * deltaTime;
	}
	if (keyboard['K'] == TRUE) {
		cam.rotation.x += 5.0f * keyboardSensitivity * deltaTime;
	}

	if (keyboard['J'] == TRUE) {
		cam.rotation.y -= 5.0f * keyboardSensitivity * deltaTime;
	}
	if (keyboard['L'] == TRUE) {
		cam.rotation.y += 5.0f * keyboardSensitivity * deltaTime;
	}

	if (keyboard['U'] == TRUE) {
		cam.rotation.z -= 5.0f * keyboardSensitivity * deltaTime;
	}
	if (keyboard['O'] == TRUE) {
		cam.rotation.z += 5.0f * keyboardSensitivity * deltaTime;
	}


	/*
	** R Key Responder
	*/

	if (keyboard['R'] == TRUE && rotateKeyDelay == 0) {
		rotateOrNot = !(rotateOrNot);
		rotateKeyDelay = 10;
	}

	if (rotateKeyDelay > 0) {
		rotateKeyDelay -= 1;
	}


	/*
	** Refresh Camera Matrices
	*/

	RefreshCamera4DMatrices(&cam);


	/*
	** Rotate the Vectors
	*/

	Mrotation = CreateRotationMatrix(rotateDegree, -30.0f, rotateDegree);

	if (rotateOrNot == TRUE) {
		rotateDegree += 0.03f * deltaTime;
	}
	if (rotateDegree >= 360.0f) {
		rotateDegree =  0.0f;
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
			&(vecs[i]), &(cam.Mtransform)
		);
	}

	for (int i = 0; i < 8; i++) {
		Vector4DDevidedByW(&(vecs[i]));
	}


	/*
	** Output Things
	*/

	// Camera Frustum
	sprintf_s(
		realbuffer, 1000,
		"n:%f\nf:%f\nt:%f\nb:%f\nl:%f\nr:%f\n",
		cam.n, cam.f, cam.t, cam.b, cam.l, cam.r
	);
	DrawShadowString(fb, width, height, 10, 42, realbuffer);

	// Camera Position
	buffer = OutputVector4D(&(cam.position));
	DrawShadowString(fb, width, height, 10, 314, buffer);
	free(buffer);

	// Camera Rotation
	buffer = OutputVector4D(&(cam.rotation));
	DrawShadowString(fb, width, height, 10, 346, buffer);
	free(buffer);

	// Mtransform
	buffer = OutputMatrix4D(&(cam.Mtransform));
	DrawShadowString(fb, width, height, 10, 378, buffer);
	free(buffer);

	// Vector List
	for (int i = 0; i < 8; i++) {
		buffer = OutputVector4D(&(vecs[i]));
		DrawShadowString(fb, width, height, 10, 154 + i * 16, buffer);
		free(buffer);
	}


	/*
	** Get And Clear Z-Buffer
	*/

	float* ZBuffer = (float*)malloc(sizeof(float) * width * height);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			ZBuffer[y * width + x] = cam.f;
		}
	}


	/*
	** Do Rasterization
	*/

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


	/*
	** Delete Z-Buffer
	*/

	free(ZBuffer);
}


void OnDestroy() {
	;
}
