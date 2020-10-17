#pragma once

#ifndef __STDIO_H__
#define __STDIO_H__
#include <stdio.h>
#endif

#ifndef __MATH_H__
#define __MATH_H__
#include <math.h>
#endif

#ifndef __LINEAR_ALGEBRA_H__
#define __LINEAR_ALGEBRA_H__
#include "LinearAlgebra.h"
#endif

#ifndef __MEST_STRUCTURE_H__
#define __MEST_STRUCTURE_H__
#include "MeshStructure.h"
#endif

#ifndef __BUILT_IN_MODEL_H__
#define __BUILT_IN_MODEL_H__
#include "BuiltInModel.h"
#endif

#define CAMERA_BUFFER_LENGTH 2048

struct Camera {

	/*
	** Things That Need To Set Manually
	*/

	/* Position */
	Vector4D Position;          // Position
	Vector4D GazeDirection;     // Gaze Direction
	Vector4D UpDirection;       // Up Direction

	/* Screen Configuration */
	int   ScreenWidth;          // Screen Width
	int   ScreenHeight;         // Screen Height
	float FoV;                  // Field Of Angle  (Y-Axis)

	/* Frustum Configuration */
	float n;                    // Frustum Near
	float f;                    // Frustum Far


	/*
	** Things That Will Be Calculated Automatically
	*/

	/* Screen Configuration */
	float AspectRatio;          // Aspect Ratio    (Width / Height)
	
	/* Frustum Configuration */
	float t;                    // Frustum Top
	float b;                    // Frustum Bottom
	float l;                    // Frustum Left
	float r;                    // Frustum Right
	float FrustumWidth;         // Frustum Width
	float FrustumHeight;        // Frustum Height
	
	/* Transform Matrices */
	Matrix4D MView;             // View Transform Matrix
	Matrix4D MOrtho;            // Orthographic Projection Transform Matrix
	Matrix4D MPersp;            // Perspective Projection Transform Matrix
	Matrix4D MViewport;         // Viewport Transform Matrix
};

Camera CreateCamera(
	float x,     float y,     float z,
	float n,     float f,     float FoV,
	int ScreenWidth,  int ScreenHeight
)
{
	Camera NewCamera;

	/* Position */
	NewCamera.Position      = CreateVector4D(x, y,  z, 1);
	NewCamera.GazeDirection = CreateVector4D(0, 0, -1, 1);
	NewCamera.UpDirection   = CreateVector4D(0, 1,  0, 1);

	/* Screen Configuration */
	NewCamera.ScreenWidth = ScreenWidth;
	NewCamera.ScreenHeight = ScreenHeight;
	NewCamera.FoV = FoV;
	NewCamera.AspectRatio = 1.0f * NewCamera.ScreenWidth / NewCamera.ScreenHeight;
	
	/* Frustum Configuration */
	NewCamera.n = n;
	NewCamera.f = f;

	NewCamera.t =       tand(NewCamera.FoV / 2) * abs(n);
	NewCamera.b =  -1 * tand(NewCamera.FoV / 2) * abs(n);
	
	NewCamera.FrustumHeight = NewCamera.t * 2;
	NewCamera.FrustumWidth  = NewCamera.FrustumHeight * NewCamera.AspectRatio;

	NewCamera.r =       NewCamera.FrustumWidth / 2;
	NewCamera.l =  -1 * NewCamera.FrustumWidth / 2;

	return NewCamera;
}

char* OutputCamera(Camera* camera) {
	char* buffer = (char*)malloc(CAMERA_BUFFER_LENGTH * sizeof(char));

	char* PositionBuffer      = OutputVector4D(&(camera->Position));
	char* GazeDirectionBuffer = OutputVector4D(&(camera->GazeDirection));
	char* UpDirectionBuffer   = OutputVector4D(&(camera->UpDirection));
	char* MViewBuffer         = OutputMatrix4D(&(camera->MView));
	char* MOrthoBuffer        = OutputMatrix4D(&(camera->MOrtho));
	char* MPerspBuffer        = OutputMatrix4D(&(camera->MPersp));
	char* MViewportBuffer     = OutputMatrix4D(&(camera->MViewport));

	sprintf_s(
		buffer, CAMERA_BUFFER_LENGTH,
		"Camera{\nPosition:        %s\nGazeDirection:   %s\nUpDirection:     %s\nScreenWidth:     %d\nScreenHeight:    %d\nFoV:             %f\nAspectRatio:     %f\nn:               %f\nf:               %f\nt:               %f\nb:               %f\nl:               %f\nr:               %f\nFrustumWidth:    %f\nFrustumHeight:   %f\nMView:\n%s\nMOrtho:\n%s\nMPersp:\n%s\nMViewport:\n%s\n}",
		PositionBuffer, GazeDirectionBuffer, UpDirectionBuffer, camera->ScreenWidth, camera->ScreenHeight, camera->FoV, camera->AspectRatio, camera->n, camera->f, camera->t, camera->b, camera->l, camera->r, camera->FrustumWidth, camera->FrustumHeight, MViewBuffer, MOrthoBuffer, MPerspBuffer, MViewportBuffer
	);

	free(PositionBuffer);
	free(GazeDirectionBuffer);
	free(UpDirectionBuffer);
	free(MViewBuffer);
	free(MOrthoBuffer);
	free(MPerspBuffer);
	free(MViewportBuffer);

	return buffer;
}

void CalcCameraMOrtho(Camera* camera) {

	/* Translation Matrix */
	Matrix4D TOrtho = CreateMatrix4D(
		1.0f, 0.0f, 0.0f, -(camera->r + camera->l) / 2.0f,
		0.0f, 1.0f, 0.0f, -(camera->t + camera->b) / 2.0f,
		0.0f, 0.0f, 1.0f, -(camera->n + camera->f) / 2.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	/* Scale Matrix */
	Matrix4D SOrtho = CreateMatrix4D(
		2.0f / (camera->r - camera->l),  0.0f,                            0.0f,                            0.0f,
		0.0f,                            2.0f / (camera->t - camera->b),  0.0f,                            0.0f,
		0.0f,                            0.0f,                            2.0f / (camera->n - camera->f),  0.0f,
		0.0f,                            0.0f,                            0.0f,                            1.0f
	);

	/* MOrtho = SOrtho * TOrtho */
	camera->MOrtho = Matrix4D_X_Matrix4D(&SOrtho, &TOrtho);
}

void CalcCameraMPersp(Camera* camera) {
	CalcCameraMOrtho(camera);
	Matrix4D MPerspToOrtho = CreateMatrix4D(
		camera->n,  0.0f,       0.0f,                    0.0f,
		0.0f,       camera->n,  0.0f,                    0.0f,
		0.0f,       0.0f,       camera->f + camera->n,  -1.0f * camera->f * camera->n,
		0.0f,       0.0f,       1.0f,                    0.0f
	);
	camera->MPersp = Matrix4D_X_Matrix4D(&(camera->MOrtho), &MPerspToOrtho);
}


//void CalcCameraMView(Camera* camera) {
//	// MView = RView * TView
//	Matrix4D TView = CreateMatrix4D(
//		1.0f, 0.0f, 0.0f, -1.0f * camera->e.x,
//		0.0f, 1.0f, 0.0f, -1.0f * camera->e.y,
//		0.0f, 0.0f, 1.0f, -1.0f * camera->e.z,
//		0.0f, 0.0f, 0.0f,  1.0f
//	);
//
//	// Normalized Gaze Direction
//	Vector4D gn = camera->g;
//	NormalizeVector4D(&gn);
//
//	// Normalized Up Direction
//	Vector4D tn = camera->t;
//	NormalizeVector4D(&tn);
//
//	Matrix4D RView = CreateMatrix4D(
//		Vector4D_Cross_Vector4D(&gn, &tn).x,  Vector4D_Cross_Vector4D(&gn, &tn).y,  Vector4D_Cross_Vector4D(&gn, &tn).z,  0.0f,
//		camera->t.x,                          camera->t.y,                          camera->t.z,                          0.0f,
//		-1 * camera->g.x,                     -1 * camera->g.y,                     -1 * camera->g.z,                     0.0f,
//		0.0f,                                 0.0f,                                 0.0f,                                 1.0f
//	);
//	
//	camera->MView = Matrix4D_X_Matrix4D(&RView, &TView);
//}
