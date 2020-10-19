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

MeshList4D MeshList = CreateMeshList4D(MESHLIST4D_MAX_LENGTH);
Camera camera;


void Setup(FrameBuffer fb, int width, int height, int deltaTime, Keyboard keyboard, Mouse mouse) {
	InitBuiltInModels();
	AddModelToMeshList4D(&MeshList, &CubeModel, 0.0f, 0.0f, -10.0f);
	camera = CreateCamera(0.0f, 0.0f, 0.0f, 0.05f, 1000.0f, 60.0f, width, height);
}


void Update(FrameBuffer fb, int width, int height, int deltaTime, Keyboard keyboard, Mouse mouse) {
	CalcFPS(fb, deltaTime);

	CalcCameraMOrtho(&camera);
	CalcCameraMPersp(&camera);
	CalcCameraMViewport(&camera);

	MeshList4D TmpMeshList = CloneMeshList4D(&MeshList);

	OrthographicProjectionTransform(&TmpMeshList, &camera);
	//PerspectiveProjectionTransform(&TmpMeshList, &camera);
	//ViewportTransform(&TmpMeshList, &camera);

	char* buffer;
	buffer = OutputMeshList4D(&TmpMeshList, 0, TmpMeshList.next);
	DrawShadowString(fb, 10, 42, buffer);
	free(buffer);

	//RenderMeshList4D(fb, width, height, &MeshList);
	for (int i = 0; i < TmpMeshList.next; i++) {
		//if (TmpMeshList.list[i].a.x > 0.0f && TmpMeshList.list[i].a.x < width) {
		//	if (TmpMeshList.list[i].a.y > 0.0f && TmpMeshList.list[i].a.y < height) {
				DrawPoint(fb, width, height, TmpMeshList.list[i].a.x, TmpMeshList.list[i].a.y, 5, RGB888(255, 255, 255));
		//	}
		//}

		//if (TmpMeshList.list[i].b.x > 0.0f && TmpMeshList.list[i].b.x < width) {
		//	if (TmpMeshList.list[i].b.y > 0.0f && TmpMeshList.list[i].b.y < height) {
				DrawPoint(fb, width, height, TmpMeshList.list[i].b.x, TmpMeshList.list[i].b.y, 5, RGB888(255, 255, 255));
		//	}
		//}

		//if (TmpMeshList.list[i].c.x > 0.0f && TmpMeshList.list[i].c.x < width) {
		//	if (TmpMeshList.list[i].c.y > 0.0f && TmpMeshList.list[i].c.y < height) {
				DrawPoint(fb, width, height, TmpMeshList.list[i].c.x, TmpMeshList.list[i].c.y, 5, RGB888(255, 255, 255));
		//	}
		//}
	}

	DestroyMeshList4D(&TmpMeshList);
}


void OnDestroy() {
	DestroyMeshList4D(&MeshList);
}
