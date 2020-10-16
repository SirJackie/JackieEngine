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

#ifndef __FPS_H__
#define __FPS_H__
#include "FPS.h"
#endif


void OnCreate() {
	;
}

Vector4D Vector = CreateVector4D(2.0f, 3.0f, 4.0f, 1.0f);
Matrix4D Matrix = CreateMatrix4D(
	101.0f, 102.0f, 103.0f, 104.0f,
	201.0f, 202.0f, 203.0f, 204.0f,
	301.0f, 302.0f, 303.0f, 304.0f,
	401.0f, 402.0f, 403.0f, 404.0f
);
Mesh4D Mesh = CreateMesh4D(
	CreateVector4D(101.0f, 102.0f, 103.0f, 104.0f),
	CreateVector4D(201.0f, 202.0f, 203.0f, 204.0f),
	CreateVector4D(301.0f, 302.0f, 303.0f, 304.0f)
);
MeshList4D MeshList = CreateMeshList4D(MESHLIST4D_MAX_LENGTH);

void Setup(FrameBuffer fb, int width, int height, int deltaTime, Keyboard keyboard, Mouse mouse) {
	AddMesh4DArrayToMeshList4D(&MeshList, CubeMesh);
}


void Update(FrameBuffer fb, int width, int height, int deltaTime, Keyboard keyboard, Mouse mouse) {
	CalcFPS(fb, deltaTime);

	char* buffer;

	/*buffer = OutputVector4D(&Vector);
	DrawShadowString(fb, 10, 42, buffer);
	free(buffer);

	buffer = OutputMatrix4D(&Matrix);
	DrawShadowString(fb, 10, 74, buffer);
	free(buffer);

	buffer = OutputMesh4D(&Mesh);
	DrawShadowString(fb, 10, 154, buffer);
	free(buffer);*/

	/*buffer = OutputMeshList4D(&MeshList, 0, MeshList.next);
	DrawShadowString(fb, 10, 42, buffer);
	free(buffer);*/

	Vector4D vec = CreateVector4D(3, 4, 0, 1);
	NormalizeVector4D(&vec);

	buffer = OutputVector4D(&vec);
	DrawShadowString(fb, 10, 42, buffer);
	free(buffer);
}


void OnDestroy() {
	DestroyMeshList4D(&MeshList);
}
