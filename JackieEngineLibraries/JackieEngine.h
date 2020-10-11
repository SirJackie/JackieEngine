#pragma once

#ifndef __STDIO_H__
#define __STDIO_H__
#include <stdio.h>
#endif

#ifndef __MATH_H__
#define __MATH_H__
#include <math.h>
#endif


/*
** Define Trigonometric Functions that use Degrees instead of Radians
*/
#define cosd(x)  cos(x*0.017453293)
#define sind(x)  sin(x*0.017453293)
#define tand(x)  tan(x*0.017453293)
#define acosd(x) acos(x*0.017453293)
#define asind(x) asin(x*0.017453293)
#define atand(x) atan(x*0.017453293)


/*
** Define a Cube
*/
float CubeMesh[12 * 3 * 3] = {
  1.0f, 1.0f, 1.0f,  4.0f, 1.0f, 1.0f,  1.0f, 4.0f, 1.0f,  //near
  1.0f, 4.0f, 1.0f,  4.0f, 4.0f, 1.0f,  4.0f, 1.0f, 1.0f,  //near
  1.0f, 1.0f, 4.0f,  4.0f, 1.0f, 4.0f,  1.0f, 4.0f, 4.0f,  //far
  1.0f, 4.0f, 4.0f,  4.0f, 4.0f, 4.0f,  4.0f, 1.0f, 4.0f,  //far
  1.0f, 4.0f, 4.0f,  1.0f, 1.0f, 4.0f,  1.0f, 1.0f, 1.0f,  //left
  1.0f, 4.0f, 4.0f,  1.0f, 4.0f, 1.0f,  1.0f, 1.0f, 1.0f,  //left
  4.0f, 4.0f, 4.0f,  4.0f, 1.0f, 4.0f,  4.0f, 1.0f, 1.0f,  //right
  4.0f, 4.0f, 4.0f,  4.0f, 4.0f, 1.0f,  4.0f, 1.0f, 1.0f,  //right
  1.0f, 4.0f, 1.0f,  1.0f, 4.0f, 4.0f,  4.0f, 4.0f, 4.0f,  //up
  1.0f, 4.0f, 1.0f,  4.0f, 4.0f, 1.0f,  4.0f, 4.0f, 4.0f,  //up
  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 4.0f,  4.0f, 1.0f, 4.0f,  //down
  1.0f, 1.0f, 1.0f,  4.0f, 1.0f, 1.0f,  4.0f, 1.0f, 4.0f   //down
};


/*
** Mathematical Definition
*/

struct Vector4D {
	float x;
	float y;
	float z;
	float w;
};

struct Matrix4D {
	float m11, m12, m13, m14;
	float m21, m22, m23, m24;
	float m31, m32, m33, m34;
	float m41, m42, m43, m44;
};

Vector4D CreateVector4D(float x, float y, float z, float w) {
	Vector4D NewVec;
	NewVec.x = x;
	NewVec.y = y;
	NewVec.z = z;
	NewVec.w = w;
	return NewVec;
}

void OutputVector4D(char* buffer, int bufferLength, Vector4D* vec) {
	sprintf_s(
		buffer, bufferLength, "Vector4D[%f,\n         %f,\n         %f,\n         %f]",
		vec->x, vec->y, vec->z, vec->w
	);
}

