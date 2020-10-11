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
	Vector4D NewVector;
	NewVector.x = x;
	NewVector.y = y;
	NewVector.z = z;
	NewVector.w = w;
	return NewVector;
}

Matrix4D CreateMatrix4D(
	float m11, float m12, float m13, float m14,
	float m21, float m22, float m23, float m24,
	float m31, float m32, float m33, float m34,
	float m41, float m42, float m43, float m44
)
{
	Matrix4D NewMatrix;

	NewMatrix.m11 = m11;
	NewMatrix.m12 = m12;
	NewMatrix.m13 = m13;
	NewMatrix.m14 = m14;

	NewMatrix.m21 = m21;
	NewMatrix.m22 = m22;
	NewMatrix.m23 = m23;
	NewMatrix.m24 = m24;

	NewMatrix.m31 = m31;
	NewMatrix.m32 = m32;
	NewMatrix.m33 = m33;
	NewMatrix.m34 = m34;

	NewMatrix.m41 = m41;
	NewMatrix.m42 = m42;
	NewMatrix.m43 = m43;
	NewMatrix.m44 = m44;

	return NewMatrix;
}

void OutputVector4D(char* buffer, int bufferLength, Vector4D* vec) {
	sprintf_s(
		buffer, bufferLength, "Vector4D[%f,\n         %f,\n         %f,\n         %f]",
		vec->x, vec->y, vec->z, vec->w
	);
}

void OutputMatrix4D(char* buffer, int bufferLength, Matrix4D* matrix) {
	sprintf_s(
		buffer, bufferLength, "Matrix4D[%f, %f, %f, %f,\n         %f, %f, %f, %f,\n         %f, %f, %f, %f,\n         %f, %f, %f, %f]",
		matrix->m11, matrix->m12, matrix->m13, matrix->m14,
		matrix->m21, matrix->m22, matrix->m23, matrix->m24,
		matrix->m31, matrix->m32, matrix->m33, matrix->m34,
		matrix->m41, matrix->m42, matrix->m43, matrix->m44
	);
}

Vector4D Matrix4D_X_Vector4D(Matrix4D* m, Vector4D* v) {
	Vector4D result;
	result.x = m->m11 * v->x + m->m12 * v->y + m->m13 * v->z + m->m14 * v->w;
	result.y = m->m21 * v->x + m->m22 * v->y + m->m23 * v->z + m->m24 * v->w;
	result.z = m->m31 * v->x + m->m32 * v->y + m->m33 * v->z + m->m34 * v->w;
	result.w = m->m41 * v->x + m->m42 * v->y + m->m43 * v->z + m->m44 * v->w;
	return result;
}
