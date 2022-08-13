#ifndef __JKEG_MathSupport__
#define __JKEG_MathSupport__

#include "../CrossBufferLayer/BasicDataTypeDeclarations.h"

#include <cmath>
using std::sqrt;


/*
** Vectors
*/

class Vec2{
public:

	// Default Constructor
	Vec2() { x = 0.0f; y = 0.0f; }

	// Custom Constructor
	Vec2(float x_, float y_) { x = x_; y = y_; }

	// Copy Constructor
	Vec2(const Vec2& rhs) {
		*this = rhs;
	}

	// Copy Assignment
	Vec2& operator=(const Vec2& rhs) {
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	// LenSq
	float LenSq() {
		return x * x + y * y;
	}

	// Len
	float Len() {
		return sqrt(LenSq());
	}

	// Normalize
	void Normalize() {
		float len = Len();
		this->x /= len;
		this->y /= len;
	}

	// GetNormalized
	Vec2 GetNormalized() {
		float len = Len();
		return Vec2(x / len, y / len);
	}

	// Vector-Scalar Operators
	Vec2  operator*  (const float rhs);
	Vec2& operator*= (const float rhs);
	Vec2  operator/  (const float rhs);
	Vec2& operator/= (const float rhs);

	// Vector-Vector Operators
	//Vec2  operator+  (const Vec2& rhs);
	//Vec2& operator+= (const Vec2& rhs);
	//Vec2  operator-  (const Vec2& rhs);
	//Vec2& operator-= (const Vec2& rhs);



	//Vec2() : x(0.0f), y(0.0f), z(0.0f) {}
	//Vec2(f32 x_, f32 y_, f32 z_) : x(x_), y(y_), z(z_) {}

	//// Methods
	//string     ToString()                   const;

	//// Vector-Scalar Calculation
	//friend const Vec2 operator+(const Vec2& a, const f32 b);
	//friend const Vec2 operator+(const f32 b, const Vec2& a);
	//friend const Vec2 operator-(const Vec2& a, const f32 b);
	//friend const Vec2 operator-(const f32 b, const Vec2& a);
	//friend const Vec2 operator*(const Vec2& a, const f32 b);
	//friend const Vec2 operator*(const f32 b, const Vec2& a);
	//friend const Vec2 operator/(const Vec2& a, const f32 b);
	//friend const Vec2 operator/(const f32 b, const Vec2& a);
	//virtual Vec2& operator+=(const f32& b);
	//virtual Vec2& operator-=(const f32& b);
	//virtual Vec2& operator*=(const f32& b);
	//virtual Vec2& operator/=(const f32& b);

	//// Vector-Vector Calculation
	//friend const Vec2 operator+(const Vec2& a, const Vec2& b);
	//friend const Vec2 operator-(const Vec2& a, const Vec2& b);
	//virtual Vec2& operator+=(const Vec2& b);
	//virtual Vec2& operator-=(const Vec2& b);

	//// Interpolation
	//virtual const Vec2 InterpolateTo(const Vec2& b, f32 alpha) const;

public:
	float x;
	float y;
};

//
//class Vec3 : public Vec2 {
//public:
//	f32 w;
//
//	Vec3() : Vec2(), w(0.0f) {}
//	Vec3(f32 x_, f32 y_, f32 z_, f32 w_) : Vec2(x_, y_, z_), w(w_) {}
//	
//	// Methods
//	string     ToString()                   const;
//	f32        Length()                     const;
//	Vec3  Normalized()                 const;
//	void       Normalize();
//	void       DevideByW();
//
//	// Vector-Scalar Calculation
//	friend const Vec3 operator+(const Vec3& a, const f32 b);
//	friend const Vec3 operator+(const f32 b, const Vec3& a);
//	friend const Vec3 operator-(const Vec3& a, const f32 b);
//	friend const Vec3 operator-(const f32 b, const Vec3& a);
//	friend const Vec3 operator*(const Vec3& a, const f32 b);
//	friend const Vec3 operator*(const f32 b, const Vec3& a);
//	friend const Vec3 operator/(const Vec3& a, const f32 b);
//	friend const Vec3 operator/(const f32 b, const Vec3& a);
//	virtual Vec3& operator+=(const f32& b);
//	virtual Vec3& operator-=(const f32& b);
//	virtual Vec3& operator*=(const f32& b);
//	virtual Vec3& operator/=(const f32& b);
//
//	// Vector-Vector Calculation
//	friend const Vec3 operator+(const Vec3& a, const Vec3& b);
//	friend const Vec3 operator-(const Vec3& a, const Vec3& b);
//	friend const f32       operator*(const Vec3& a, const Vec3& b);  // Dot   Product
//	friend const Vec3 operator%(const Vec3& a, const Vec3& b);  // Cross Product
//	virtual Vec3& operator+=(const Vec3& b);
//	virtual Vec3& operator-=(const Vec3& b);
//
//	// Interpolation
//	virtual const Vec3 InterpolateTo(const Vec3& b, f32 alpha) const;
//};
//
//
///*
//** Mat3
//*/
//
//class Mat3 {
//public:
//	f32 m11, m12, m13, m14;
//	f32 m21, m22, m23, m24;
//	f32 m31, m32, m33, m34;
//	f32 m41, m42, m43, m44;
//
//	Mat3(
//		f32 m11, f32 m12, f32 m13, f32 m14,
//		f32 m21, f32 m22, f32 m23, f32 m24,
//		f32 m31, f32 m32, f32 m33, f32 m34,
//		f32 m41, f32 m42, f32 m43, f32 m44
//	);
//	Mat3();
//
//	string ToString() const;
//	friend const Vec3 operator*(const Vec3& v, const Mat3& m);
//	friend const Mat3 operator*(const Mat3& a, const Mat3& b);
//
//	static Mat3 GenerateTranslationMatrix (f32 x, f32 y, f32 z);
//	static Mat3 GenerateRotationMatrix    (f32 x, f32 y, f32 z);
//};
#endif
