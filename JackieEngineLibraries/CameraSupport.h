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

	Matrix4D Mortho;
	Matrix4D Mpersp;
	Matrix4D Mviewport;
	Matrix4D Mtransform;
};

Camera4D CreateCamera4D(float n, float f, float fovY, int ScreenWidth, int ScreenHeight) {
	Camera4D cam;

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


