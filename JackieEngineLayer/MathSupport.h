#ifndef __JKEG_MathSupport__
#define __JKEG_MathSupport__

#include <cmath>
#include <string>
#include <sstream>
using std::string;
using std::stringstream;




/*
** Define Trigonometric Functions that use Degrees instead of Radians
*/

#define  PI         3.14159265f
#define  _DEG2RAD_  PI / 180.0f
#define  _RAD2DEG_  180.0f / PI

using std::sinf;
using std::cosf;
using std::tanf;

using std::asinf;
using std::acosf;
using std::atanf;

#define cosd(x) cosf(x*_DEG2RAD_)
#define sind(x) sinf(x*_DEG2RAD_)
#define tand(x) tanf(x*_DEG2RAD_)

#define acosd(x) (acosf(x)*_RAD2DEG_)
#define asind(x) (asinf(x)*_RAD2DEG_)
#define atand(x) (atanf(x)*_RAD2DEG_)




/*
** Define Some Calculating Functions
*/

#ifndef __MathSupport_Clamp__
#define __MathSupport_Clamp__
int   clamp (int   min, int   input, int   max);
float fclamp(float min, float input, float max);
#endif

#ifndef __MathSupport_MinMax3__
#define __MathSupport_MinMax3__
int   min3 (int   a, int   b, int   c);
int   max3 (int   a, int   b, int   c);
float fmin3(float a, float b, float c);
float fmax3(float a, float b, float c);
#endif


/*
** Vector4D
*/

class Vector4D {
public:
	float x;
	float y;
	float z;
	float w;

	Vector4D(float x_, float y_, float z_, float w_);
	Vector4D();
	string    str()                        const;
	float     length()                     const;
	Vector4D  normalized()                 const;
	void      Normalize();
	void      DevideByW();
	Vector4D  operator+(const Vector4D& b) const;
	Vector4D  operator-(const Vector4D& b) const;
	float     operator*(const Vector4D& b) const;  // Dot   Product
	Vector4D  operator%(const Vector4D& b) const;  // Cross Product
};


/*
** Matrix4D
*/

class Matrix4D {
public:
	float m11, m12, m13, m14;
	float m21, m22, m23, m24;
	float m31, m32, m33, m34;
	float m41, m42, m43, m44;

	Matrix4D(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44
	);

	string str() const;
};


////Vector4D Vector4DTimesMatrix4D(Vector4D* v, Matrix4D* m) {
////	Vector4D result;
////	result.x = m->m11 * v->x + m->m12 * v->y + m->m13 * v->z + m->m14 * v->w;
////	result.y = m->m21 * v->x + m->m22 * v->y + m->m23 * v->z + m->m24 * v->w;
////	result.z = m->m31 * v->x + m->m32 * v->y + m->m33 * v->z + m->m34 * v->w;
////	result.w = m->m41 * v->x + m->m42 * v->y + m->m43 * v->z + m->m44 * v->w;
////	return result;
////}
////
////Matrix4D Matrix4DTimesMatrix4D(Matrix4D* a, Matrix4D* b) {
////	Matrix4D result;
////
////	result.m11 = b->m11 * a->m11 + b->m12 * a->m21 + b->m13 * a->m31 + b->m14 * a->m41;
////	result.m21 = b->m21 * a->m11 + b->m22 * a->m21 + b->m23 * a->m31 + b->m24 * a->m41;
////	result.m31 = b->m31 * a->m11 + b->m32 * a->m21 + b->m33 * a->m31 + b->m34 * a->m41;
////	result.m41 = b->m41 * a->m11 + b->m42 * a->m21 + b->m43 * a->m31 + b->m44 * a->m41;
////
////	result.m12 = b->m11 * a->m12 + b->m12 * a->m22 + b->m13 * a->m32 + b->m14 * a->m42;
////	result.m22 = b->m21 * a->m12 + b->m22 * a->m22 + b->m23 * a->m32 + b->m24 * a->m42;
////	result.m32 = b->m31 * a->m12 + b->m32 * a->m22 + b->m33 * a->m32 + b->m34 * a->m42;
////	result.m42 = b->m41 * a->m12 + b->m42 * a->m22 + b->m43 * a->m32 + b->m44 * a->m42;
////
////	result.m13 = b->m11 * a->m13 + b->m12 * a->m23 + b->m13 * a->m33 + b->m14 * a->m43;
////	result.m23 = b->m21 * a->m13 + b->m22 * a->m23 + b->m23 * a->m33 + b->m24 * a->m43;
////	result.m33 = b->m31 * a->m13 + b->m32 * a->m23 + b->m33 * a->m33 + b->m34 * a->m43;
////	result.m43 = b->m41 * a->m13 + b->m42 * a->m23 + b->m43 * a->m33 + b->m44 * a->m43;
////
////	result.m14 = b->m11 * a->m14 + b->m12 * a->m24 + b->m13 * a->m34 + b->m14 * a->m44;
////	result.m24 = b->m21 * a->m14 + b->m22 * a->m24 + b->m23 * a->m34 + b->m24 * a->m44;
////	result.m34 = b->m31 * a->m14 + b->m32 * a->m24 + b->m33 * a->m34 + b->m34 * a->m44;
////	result.m44 = b->m41 * a->m14 + b->m42 * a->m24 + b->m43 * a->m34 + b->m44 * a->m44;
////
////	return result;
////}
////
#endif
