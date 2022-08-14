#ifndef __JKEG_MathSupport__
#define __JKEG_MathSupport__

#include <cmath>
using std::sqrt;
using std::cosf;
using std::sinf;

#include <cstring>;
using std::memcpy;
using std::memset;


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
	Vec2  operator+  (const Vec2& rhs);
	Vec2& operator+= (const Vec2& rhs);
	Vec2  operator-  (const Vec2& rhs);
	Vec2& operator-= (const Vec2& rhs);

	// Negative Operator
	Vec2  operator-  ();

public:
	float x;
	float y;
};


class Vec3 : public Vec2 {
public:

	// Default Constructor
	Vec3() { x = 0.0f; y = 0.0f; z = 0.0f; }

	// Custom Constructor
	Vec3(float x_, float y_, float z_) { x = x_; y = y_; z = z_; }

	// Copy Constructor
	Vec3(const Vec3& rhs) {
		*this = rhs;
	}

	// Copy Assignment
	Vec3& operator=(const Vec3& rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}

	// LenSq
	float LenSq() {
		return x * x + y * y + z * z;
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
		this->z /= len;
	}

	// GetNormalized
	Vec3 GetNormalized() {
		float len = Len();
		return Vec3(x / len, y / len, z / len);
	}

	// Vector-Scalar Operators
	Vec3  operator*  (const float rhs);
	Vec3& operator*= (const float rhs);
	Vec3  operator/  (const float rhs);
	Vec3& operator/= (const float rhs);

	// Vector-Vector Operators
	Vec3  operator+  (const Vec3& rhs);
	Vec3& operator+= (const Vec3& rhs);
	Vec3  operator-  (const Vec3& rhs);
	Vec3& operator-= (const Vec3& rhs);

	// Vector-Vector Dot Product
	float operator*  (const Vec3& rhs);

	// Negative Operator
	Vec3  operator-  ();

public:
	float z;
};


/*
** Matrices
*/

class Mat2 {
public:

	// Default Constructor
	Mat2() {
		memset(elements, 0, sizeof(elements));
	}

	// Custom Constructor
	Mat2(float m00, float m01, float m10, float m11) {
		elements[0][0] = m00;
		elements[0][1] = m01;
		elements[1][0] = m10;
		elements[1][1] = m11;
	}

	// Copy Constructor
	Mat2(const Mat2& rhs) {
		*this = rhs;
	}

	// Copy Assignment
	Mat2& operator=(const Mat2& rhs) {
		memcpy(elements, rhs.elements, sizeof(elements));
		return *this;
	}

	// Matrix-Scalar Operators
	Mat2  operator*  (float rhs);
	Mat2& operator*= (float rhs);

	// Matrix-Matrix Operators
	Mat2  operator*  (const Mat2& rhs);
	Mat2& operator*= (const Mat2& rhs);

	// Special Matrix Getters
	static Mat2 Identity();
	static Mat2 Scaling(float factor);
	static Mat2 Rotation(float theta);

public:
	float elements[2][2];
};


class Mat3 {
public:

	// Default Constructor
	Mat3() {
		memset(elements, 0, sizeof(elements));
	}

	// Custom Constructor
	Mat3(
		float m00, float m01, float m02,
		float m10, float m11, float m12,
		float m20, float m21, float m22
	) {
		elements[0][0] = m00;
		elements[0][1] = m01;
		elements[0][2] = m02;

		elements[1][0] = m10;
		elements[1][1] = m11;
		elements[1][2] = m12;

		elements[2][0] = m20;
		elements[2][1] = m21;
		elements[2][2] = m22;
	}

	// Copy Constructor
	Mat3(const Mat3& rhs) {
		*this = rhs;
	}

	// Copy Assignment
	Mat3& operator=(const Mat3& rhs) {
		memcpy(elements, rhs.elements, sizeof(elements));
		return *this;
	}

	// Matrix-Scalar Operators
	Mat3  operator*  (float rhs);
	Mat3& operator*= (float rhs);

	//// Matrix-Matrix Operators
	//Mat2  operator*  (const Mat2& rhs);
	//Mat2& operator*= (const Mat2& rhs);

	//// Special Matrix Getters
	//static Mat2 Identity();
	//static Mat2 Scaling(float factor);
	//static Mat2 Rotation(float theta);

public:
	float elements[3][3];
};


/*
** Vector-Matrix Operators
*/

Vec2  operator*  (const Vec2& lhs, const Mat2& rhs);
Vec2& operator*= (Vec2& lhs, const Mat2& rhs);


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
