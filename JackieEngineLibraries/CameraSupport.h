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
	float n;
	float f;
	float t;
	float b;
	float l;
	float r;
	float fovY;
	int ScreenWidth;
	int ScreenHeight;
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
