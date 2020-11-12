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

struct Camera4D {


	/*
	** Position Setting
	*/

	Vector4D position;
	Vector4D rotation;


	/*
	** Frustum Setting
	*/

	float n;
	float f;
	float t;
	float b;
	float l;
	float r;
	float fovY;
	int ScreenWidth;
	int ScreenHeight;


	/*
	** Matrices
	*/

	Matrix4D Mtranslation;
	Matrix4D Mrotation;
	Matrix4D Mortho;
	Matrix4D Mpersp;
	Matrix4D Mviewport;
	Matrix4D MprojAndviewport;
	Matrix4D Mtransform;
};

Camera4D CreateCamera4D(
	float x, float y, float z, float rotx, float roty, float rotz,
	float n, float f, float fovY, int ScreenWidth, int ScreenHeight
)
{
	Camera4D cam;

	cam.position = CreateVector4D(x, y, z, 1);
	cam.rotation = CreateVector4D(rotx, roty, rotz, 1);

	cam.n = n;
	cam.f = f;
	cam.fovY = fovY;
	cam.ScreenWidth = ScreenWidth;
	cam.ScreenHeight = ScreenHeight;

	cam.t = abs(cam.n) * tand(cam.fovY / 2.0f);
	cam.b = -1.0f * cam.t;

	cam.r = cam.ScreenWidth * cam.t / cam.ScreenHeight;
	cam.l = -1.0 * cam.r;

	return cam;
}

void CalcCamera4DMtranslation(Camera4D* cam) {
	cam->Mtranslation = CreateMatrix4D(
		1.0f, 0.0f, 0.0f, -1.0f * (cam->position.x),
		0.0f, 1.0f, 0.0f, -1.0f * (cam->position.y),
		0.0f, 0.0f, 1.0f, -1.0f * (cam->position.z),
		0.0f, 0.0f, 0.0f,  1.0f
	);
}

void CalcCamera4DMrotation(Camera4D* cam) {
	Matrix4D MrotationX = CreateMatrix4D(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cosd(cam->rotation.x), -1.0f * sind(cam->rotation.x), 0.0f,
		0.0f, sind(cam->rotation.x), cosd(cam->rotation.x), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	Matrix4D MrotationY = CreateMatrix4D(
		cosd(cam->rotation.y), 0.0f, sind(cam->rotation.y), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-1.0f * sind(cam->rotation.y), 0.0f, cosd(cam->rotation.y), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	Matrix4D MrotationZ = CreateMatrix4D(
		cosd(cam->rotation.z), -1.0f * sind(cam->rotation.z), 0.0f, 0.0f,
		sind(cam->rotation.z), cosd(cam->rotation.z), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	cam->Mrotation = Matrix4DTimesMatrix4D(
		&MrotationX,
		&MrotationY
	);

	cam->Mrotation = Matrix4DTimesMatrix4D(
		&(cam->Mrotation),
		&MrotationZ
	);
}

void CalcCamera4DMortho(Camera4D* cam) {
	Matrix4D Morthoa = CreateMatrix4D(
		1.0f, 0.0f, 0.0f, -1 * (cam->r + cam->l) / 2.0f,
		0.0f, 1.0f, 0.0f, -1 * (cam->t + cam->b) / 2.0f,
		0.0f, 0.0f, 1.0f, -1 * (cam->n + cam->f) / 2.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	Matrix4D Morthob = CreateMatrix4D(
		2.0f / (cam->r - cam->l), 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / (cam->t - cam->b), 0.0f, 0.0f,
		0.0f, 0.0f, 2.0f / (cam->n - cam->f), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	cam->Mortho = Matrix4DTimesMatrix4D(
		&Morthoa,
		&Morthob
	);
}

void CalcCamera4DMpersp(Camera4D* cam) {
	CalcCamera4DMortho(cam);
	Matrix4D Mpersp2ortho = CreateMatrix4D(
		cam->n, 0.0f, 0.0f, 0.0f,
		0.0f, cam->n, 0.0f, 0.0f,
		0.0f, 0.0f, cam->f + cam->n, -1 * cam->f * cam->n,
		0.0f, 0.0f, 1.0f, 0.0f
	);

	cam->Mpersp = Matrix4DTimesMatrix4D(
		&Mpersp2ortho,
		&(cam->Mortho)
	);
}

void CalcCamera4DMviewport(Camera4D* cam) {
	cam->Mviewport = CreateMatrix4D(
		cam->ScreenWidth / 2.0f, 0.0f, 0.0f, cam->ScreenWidth / 2.0f,
		0.0f, cam->ScreenHeight / 2.0f, 0.0f, cam->ScreenHeight / 2.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

void CalcCamera4DMprojAndviewport(Camera4D* cam) {
	CalcCamera4DMpersp(cam);
	CalcCamera4DMviewport(cam);
	cam->MprojAndviewport = Matrix4DTimesMatrix4D(
		&(cam->Mpersp),
		&(cam->Mviewport)
	);
}

void RefreshCamera4DMatrices(Camera4D* cam) {
	CalcCamera4DMtranslation(cam);
	CalcCamera4DMrotation(cam);
	// cam->MprojAndviewport is not changed
	cam->Mtransform = Matrix4DTimesMatrix4D(
		&(cam->Mtranslation),
		&(cam->Mrotation)
	);
	cam->Mtransform = Matrix4DTimesMatrix4D(
		&(cam->Mtransform),
		&(cam->MprojAndviewport)
	);
}


void CalcCamera4DMatrices(Camera4D* cam) {
	CalcCamera4DMprojAndviewport(cam);
	RefreshCamera4DMatrices(cam);
}
