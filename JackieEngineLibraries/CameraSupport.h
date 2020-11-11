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
