#ifndef __JKEG_MathSupport__
#define __JKEG_MathSupport__

#include <cmath>
using std::sqrt;
using std::cosf;
using std::sinf;

#include <cstring>;
using std::memcpy;
using std::memset;

#include <algorithm>
using std::swap;


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

	// Matrix-Matrix Operators
	Mat3  operator*  (const Mat3& rhs);
	Mat3& operator*= (const Mat3& rhs);

	// Special Matrix Getters
	static Mat3 Identity();
	static Mat3 Scaling(float factor);
	static Mat3 RotationZ(float theta);
	static Mat3 RotationY(float theta);
	static Mat3 RotationX(float theta);

public:
	float elements[3][3];
};


/*
** Vector-Matrix Operators
*/

Vec2  operator*  (const Vec2& lhs, const Mat2& rhs);
Vec2& operator*= (Vec2& lhs, const Mat2& rhs);

Vec3  operator*  (const Vec3& lhs, const Mat3& rhs);
Vec3& operator*= (Vec3& lhs, const Mat3& rhs);


/*
** Vertex
*/

class Vertex {
public:

	// Default Constructor
	Vertex() {
		pos = Vec3();
		tex = Vec2();
	}

	// Custom Constructor
	Vertex(const Vec3& pos_, const Vec2& tex_) {
		pos = pos_;
		tex = tex_;
	}

	// Copy Constructor
	Vertex(const Vertex& rhs) {
		pos = rhs.pos;
		tex = rhs.tex;
	}

	// Copy Assignment
	Vertex& operator=(const Vertex& rhs) {
		pos = rhs.pos;
		tex = rhs.tex;
		return *this;
	}

	// Vertex-Vertex Operators
	Vertex operator+(const Vertex& rhs) {
		return Vertex(
			pos + rhs.pos,
			tex + rhs.tex
		);
	}

	Vertex operator-(const Vertex& rhs) {
		return Vertex(
			pos - rhs.pos,
			tex - rhs.tex
		);
	}

	Vertex operator*(float rhs) {
		return Vertex(
			pos * rhs,
			tex * rhs
		);
	}

public:
	Vec3 pos;
	Vec2 tex;
};


/*
** Interpolator
*/

template<typename T>
inline T interpolate(T& src, T& dst, float alpha)
{
	return src + (dst - src) * alpha;
}

#endif
