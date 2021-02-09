#ifndef __JKEG_LinearAlgebra
#define __JKEG_LinearAlgebra

#include <stdio.h>
#include <math.h>


/*
** Define Buffer Default Length
*/

#define VECTOR4D_BUFFER_LENGTH 256
#define MATRIX4D_BUFFER_LENGTH 1024


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
** Define Some Calculating Functions
*/

int clamp(int min, int input, int max) {
	if (input > min) {
		if (input < max) {
			return input;
		}
		else {
			return max;
		}
	}
	else {
		return min;
	}
}

double dclamp(double min, double input, double max) {
	if (input > min) {
		if (input < max) {
			return input;
		}
		else {
			return max;
		}
	}
	else {
		return min;
	}
}

int min3(int a, int b, int c) {
	int min = a;
	if (b < min) {
		min = b;
	}
	if (c < min) {
		min = c;
	}
	return min;
}

int max3(int a, int b, int c) {
	int max = a;
	if (b > max) {
		max = b;
	}
	if (c > max) {
		max = c;
	}
	return max;
}


/*
** Vector4D
*/

struct Vector4D {
	double x;
	double y;
	double z;
	double w;
};

Vector4D CreateVector4D(double x, double y, double z, double w) {
	Vector4D NewVector;
	NewVector.x = x;
	NewVector.y = y;
	NewVector.z = z;
	NewVector.w = w;
	return NewVector;
}

char* OutputVector4D(Vector4D* vec) {
	char* buffer = (char*)malloc(VECTOR4D_BUFFER_LENGTH * sizeof(char));

	if (buffer != 0) {
		sprintf_s(
			buffer, VECTOR4D_BUFFER_LENGTH,
			"Vector4D[%lf, %lf, %lf, %lf]",
			vec->x, vec->y, vec->z, vec->w
		);
	}

	return buffer;
}

double LengthOfVector4D(Vector4D* vec) {
	// Use the Pythagorean Theorem to calculate the length
	return sqrt(
		vec->x * vec->x + vec->y * vec->y + vec->z * vec->z
	);
}

Vector4D NormalizedVector4D(Vector4D* vec) {
	double length = LengthOfVector4D(vec);
	return CreateVector4D(
		vec->x / length,
		vec->y / length,
		vec->z / length,
		vec->w  // W-Axis is Meaningless, So Do Nothing
	);
}

void Vector4DDevidedByW(Vector4D* vec) {
	vec->x /= vec->w;
	vec->y /= vec->w;
	vec->z /= vec->w;
	vec->w /= vec->w;
}

Vector4D Vector4DAddVector4D(Vector4D* a, Vector4D* b) {
	Vector4D result;
	result.x = a->x + b->x;
	result.y = a->y + b->y;
	result.z = a->z + b->z;
	result.w = a->w + b->w;
	return result;
}

Vector4D Vector4DMinusVector4D(Vector4D* a, Vector4D* b) {
	Vector4D result;
	result.x = a->x - b->x;
	result.y = a->y - b->y;
	result.z = a->z - b->z;
	result.w = a->w - b->w;
	return result;
}

#define CreateVector4DFromPointToPoint(from, to) Vector4DMinusVector4D(to, from)

double Vector4DDotVector4D(Vector4D* a, Vector4D* b) {
	return a->x * b->x + a->y * b->y + a->z * b->z;
}

Vector4D Vector4DCrossVector4D(Vector4D* a, Vector4D* b) {
	Vector4D result;
	result.x = a->y * b->z - b->y * a->z;
	result.y = a->z * b->x - a->x * b->z;
	result.z = a->x * b->y - a->y * b->x;
	// Cross Product of a Vector is only defined on 3D Space
	// So W-Axis is Meaningless
	result.w = a->w;
	return result;
}




/*
** Matrix4D
*/

struct Matrix4D {
	double m11, m12, m13, m14;
	double m21, m22, m23, m24;
	double m31, m32, m33, m34;
	double m41, m42, m43, m44;
};

Matrix4D CreateMatrix4D(
	double m11, double m12, double m13, double m14,
	double m21, double m22, double m23, double m24,
	double m31, double m32, double m33, double m34,
	double m41, double m42, double m43, double m44
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

char* OutputMatrix4D(Matrix4D* matrix) {
	char* buffer = (char*)malloc(MATRIX4D_BUFFER_LENGTH * sizeof(char));

	if (buffer != 0) {
		sprintf_s(
			buffer, MATRIX4D_BUFFER_LENGTH,
			"Matrix4D[%lf, %lf, %lf, %lf,\n         %lf, %lf, %lf, %lf,\n         %lf, %lf, %lf, %lf,\n         %lf, %lf, %lf, %lf]",
			matrix->m11, matrix->m12, matrix->m13, matrix->m14,
			matrix->m21, matrix->m22, matrix->m23, matrix->m24,
			matrix->m31, matrix->m32, matrix->m33, matrix->m34,
			matrix->m41, matrix->m42, matrix->m43, matrix->m44
		);
	}

	return buffer;
}

Vector4D Vector4DTimesMatrix4D(Vector4D* v, Matrix4D* m) {
	Vector4D result;
	result.x = m->m11 * v->x + m->m12 * v->y + m->m13 * v->z + m->m14 * v->w;
	result.y = m->m21 * v->x + m->m22 * v->y + m->m23 * v->z + m->m24 * v->w;
	result.z = m->m31 * v->x + m->m32 * v->y + m->m33 * v->z + m->m34 * v->w;
	result.w = m->m41 * v->x + m->m42 * v->y + m->m43 * v->z + m->m44 * v->w;
	return result;
}

Matrix4D Matrix4DTimesMatrix4D(Matrix4D* a, Matrix4D* b) {
	Matrix4D result;

	result.m11 = b->m11 * a->m11 + b->m12 * a->m21 + b->m13 * a->m31 + b->m14 * a->m41;
	result.m21 = b->m21 * a->m11 + b->m22 * a->m21 + b->m23 * a->m31 + b->m24 * a->m41;
	result.m31 = b->m31 * a->m11 + b->m32 * a->m21 + b->m33 * a->m31 + b->m34 * a->m41;
	result.m41 = b->m41 * a->m11 + b->m42 * a->m21 + b->m43 * a->m31 + b->m44 * a->m41;

	result.m12 = b->m11 * a->m12 + b->m12 * a->m22 + b->m13 * a->m32 + b->m14 * a->m42;
	result.m22 = b->m21 * a->m12 + b->m22 * a->m22 + b->m23 * a->m32 + b->m24 * a->m42;
	result.m32 = b->m31 * a->m12 + b->m32 * a->m22 + b->m33 * a->m32 + b->m34 * a->m42;
	result.m42 = b->m41 * a->m12 + b->m42 * a->m22 + b->m43 * a->m32 + b->m44 * a->m42;

	result.m13 = b->m11 * a->m13 + b->m12 * a->m23 + b->m13 * a->m33 + b->m14 * a->m43;
	result.m23 = b->m21 * a->m13 + b->m22 * a->m23 + b->m23 * a->m33 + b->m24 * a->m43;
	result.m33 = b->m31 * a->m13 + b->m32 * a->m23 + b->m33 * a->m33 + b->m34 * a->m43;
	result.m43 = b->m41 * a->m13 + b->m42 * a->m23 + b->m43 * a->m33 + b->m44 * a->m43;

	result.m14 = b->m11 * a->m14 + b->m12 * a->m24 + b->m13 * a->m34 + b->m14 * a->m44;
	result.m24 = b->m21 * a->m14 + b->m22 * a->m24 + b->m23 * a->m34 + b->m24 * a->m44;
	result.m34 = b->m31 * a->m14 + b->m32 * a->m24 + b->m33 * a->m34 + b->m34 * a->m44;
	result.m44 = b->m41 * a->m14 + b->m42 * a->m24 + b->m43 * a->m34 + b->m44 * a->m44;

	return result;
}

#endif
