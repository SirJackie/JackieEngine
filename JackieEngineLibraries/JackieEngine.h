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

struct Camera {
	Vector4D e;    // Position
	Vector4D g;    // Gaze Direction
	Vector4D t;    // Up Direction
	
	float n;       // Frustum Near
	float f;       // Frustum Far

	float FoV;     // Field Of Angle (Y-Axis)
	float top;     // Frustum Top
	float bottom;  // Frustum Bottom
	float left;    // Frustum Left
	float right;   // Frustum Right

	int ScreenWidth;
	int ScreenHeight;
	float AspectRatio;

	Matrix4D MView;      // View Transform Matrix
	Matrix4D MOrtho;     // Orthographic Projection Transform Matrix
	Matrix4D MPersp;     // Perspective Projection Transform Matrix
	Matrix4D MViewport;  // Viewport Transform Matrix
};

Camera CreateCamera(
	float x, float y, float z,
	float xRot, float yRot, float zRot,
	float n, float f, float FoV, int ScreenWidth, int ScreenHeight
)
{
	Camera NewCamera;
	NewCamera.e = CreateVector4D(x, y, z, 1);
	NewCamera.g = CreateVector4D(xRot, yRot, zRot, 1);
	
	NewCamera.n = n;
	NewCamera.f = f;
	NewCamera.FoV = FoV;
	NewCamera.ScreenWidth = ScreenWidth;
	NewCamera.ScreenHeight = ScreenHeight;

	float HalfFoV = NewCamera.FoV / 2;
	NewCamera.top = tand(HalfFoV) * abs(n);
	NewCamera.bottom = -1 * NewCamera.top;
	
	float height = NewCamera.top * 2;
	NewCamera.AspectRatio = 1.0f * NewCamera.ScreenWidth / NewCamera.ScreenHeight;
	float width = height * NewCamera.AspectRatio;

	NewCamera.left = -1 * width / 2;
	NewCamera.right = width / 2;

	return NewCamera;
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
