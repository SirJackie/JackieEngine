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

int min3(int a, int b, int c) {
	int min = a;
	if (b < min) {
		min = b;
	}
	if (c < min) {
		min = c;
	}
	return min;
}

int max3(int a, int b, int c) {
	int max = a;
	if (b > max) {
		max = b;
	}
	if (c > max) {
		max = c;
	}
	return max;
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

void CreateVector4DFromPointToPoint(Vector4D* from, Vector4D* to, Vector4D* result) {
	result->x = from->x - to->x;
	result->y = from->y - to->y;
}

void DrawFlatMesh4D(FrameBuffer fb, int width, int height,
	Vector4D* v0, Vector4D* v1, Vector4D* v2
)
{
	Color color = CreateColor(255, 255, 255, 255);

	int StartX = min3(v0->x, v1->x, v2->x);
	int StartY = min3(v0->y, v1->y, v2->y);
	int EndX   = max3(v0->x, v1->x, v2->x);
	int EndY   = max3(v0->y, v1->y, v2->y);
	StartX     = clamp(0, StartX, width);
	StartY     = clamp(0, StartY, height);
	EndX       = clamp(0, EndX, width);
	EndY       = clamp(0, EndY, height);

	float v0x = v0->x;
	float v0y = v0->y;
	float v1x = v1->x;
	float v1y = v1->y;
	float v2x = v2->x;
	float v2y = v2->y;

	float v1v2x, v1v2y;
	float v0v1x, v0v1y;
	float v2v0x, v2v0y;

	float v1px, v1py;
	float v0px, v0py;
	float v2px, v2py;

	float zresult1;
	float zresult2;
	float zresult3;

	//CreateVector4DFromPointToPoint(v1, v2, &v1v2);
	v1v2x = v1x - v2x;
	v1v2y = v1y - v2y;
	//CreateVector4DFromPointToPoint(v0, v1, &v0v1);
	v0v1x = v0x - v1x;
	v0v1y = v0y - v1y;
	//CreateVector4DFromPointToPoint(v2, v0, &v2v0);
	v2v0x = v2x - v0x;
	v2v0y = v2y - v0y;

	for (int y = StartY; y < EndY; y++) {
		for (int x = StartX; x < EndX; x++) {

			//CreateVector4DFromPointToPoint(v1, &p, &v1p);
			v1px = v1->x - x;
			v1py = v1->y - y;
			//CreateVector4DFromPointToPoint(v0, &p, &v0p);
			v0px = v0->x - x;
			v0py = v0->y - y;
			//CreateVector4DFromPointToPoint(v2, &p, &v2p);
			v2px = v2->x - x;
			v2py = v2->y - y;

			//result1 = Vector4DCrossVector4D(&v1v2, &v1p);
			zresult1 = v1v2x * v1py - v1v2y * v1px;
			//result2 = Vector4DCrossVector4D(&v0v1, &v0p);
			zresult2 = v0v1x * v0py - v0v1y * v0px;
			//result3 = Vector4DCrossVector4D(&v2v0, &v2p);
			zresult3 = v2v0x * v2py - v2v0y * v2px;

			if (zresult1 > 0 && zresult2 > 0 && zresult3 > 0) {
				SetPixel(fb, x, y, color);
			}
			else if (zresult1 < 0 && zresult2 < 0 && zresult3 < 0) {
				SetPixel(fb, x, y, color);
			}
		}
	}
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
float rotdeg = 0.0f;

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


	/*
	** Refresh Camera Matrices
	*/

	RefreshCamera4DMatrices(&cam);


	/*
	** Rotate the Vectors
	*/

	Matrix4D Mrotation = CreateRotationMatrix(rotdeg, -30.0f, rotdeg);
	//Matrix4D Mrotation = CreateRotationMatrix(0.0f, 0.0f, 0.0f);
	rotdeg += 0.03f * deltaTime;
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
			&(vecs[i]), &(cam.Mtransform)
		);
	}

	for (int i = 0; i < 8; i++) {
		Vector4DDevidedByW(&(vecs[i]));
	}


	/*
	** Do Y-Axis Reverse
	*/

	for (int i = 0; i < 8; i++) {
		vecs[i].y = height - vecs[i].y;
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

	for (int i = 0; i < 8; i++) {
		buffer = OutputVector4D(&(vecs[i]));
		DrawShadowString(fb, width, height, 10, 154 + i * 16, buffer);
		free(buffer);
	}

	for (int i = 0; i < 8; i++) {
		float tmp = (-1.0f * vecs[i].z) - 0.9f;
		DrawVector4D(fb, width, height, &(vecs[i]), (int)((0.1f - tmp) * 100.0f));
	}

	DrawFlatMesh4D(fb, width, height, &(vecs[0]), &(vecs[1]), &(vecs[3]));
	DrawFlatMesh4D(fb, width, height, &(vecs[2]), &(vecs[3]), &(vecs[1]));
	DrawFlatMesh4D(fb, width, height, &(vecs[7]), &(vecs[4]), &(vecs[5]));
	DrawFlatMesh4D(fb, width, height, &(vecs[6]), &(vecs[5]), &(vecs[4]));
	DrawFlatMesh4D(fb, width, height, &(vecs[4]), &(vecs[0]), &(vecs[6]));
	DrawFlatMesh4D(fb, width, height, &(vecs[3]), &(vecs[6]), &(vecs[0]));
	DrawFlatMesh4D(fb, width, height, &(vecs[1]), &(vecs[7]), &(vecs[2]));
	DrawFlatMesh4D(fb, width, height, &(vecs[5]), &(vecs[2]), &(vecs[7]));
	DrawFlatMesh4D(fb, width, height, &(vecs[3]), &(vecs[2]), &(vecs[6]));
	DrawFlatMesh4D(fb, width, height, &(vecs[5]), &(vecs[6]), &(vecs[2]));
	DrawFlatMesh4D(fb, width, height, &(vecs[7]), &(vecs[0]), &(vecs[4]));
	DrawFlatMesh4D(fb, width, height, &(vecs[7]), &(vecs[1]), &(vecs[0]));


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
}


void OnDestroy() {
	;
}
