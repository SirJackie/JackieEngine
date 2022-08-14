#include "MathSupport.h"


/*
** Vec2
*/

Vec2 Vec2::operator*(const float rhs)
{
	return Vec2(*this) *= rhs;
}

Vec2 & Vec2::operator*=(const float rhs)
{
	x *= rhs;
	y *= rhs;
	return *this;
}

Vec2 Vec2::operator/(const float rhs)
{
	return Vec2(*this) /= rhs;
}

Vec2 & Vec2::operator/=(const float rhs)
{
	x /= rhs;
	y /= rhs;
	return *this;
}

Vec2 Vec2::operator+(const Vec2 & rhs)
{
	return Vec2(*this) += rhs;
}

Vec2 & Vec2::operator+=(const Vec2 & rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vec2 Vec2::operator-(const Vec2 & rhs)
{
	return Vec2(*this) -= rhs;
}

Vec2 & Vec2::operator-=(const Vec2 & rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vec2 Vec2::operator-()
{
	return Vec2(-x, -y);
}


/*
** Vec3
*/

Vec3 Vec3::operator*(const float rhs)
{
	return Vec3(*this) *= rhs;
}

Vec3 & Vec3::operator*=(const float rhs)
{
	x *= rhs;
	y *= rhs;
	z *= rhs;
	return *this;
}

Vec3 Vec3::operator/(const float rhs)
{
	return Vec3(*this) /= rhs;
}

Vec3 & Vec3::operator/=(const float rhs)
{
	x /= rhs;
	y /= rhs;
	z /= rhs;
	return *this;
}

Vec3 Vec3::operator+(const Vec3 & rhs)
{
	return Vec3(*this) += rhs;
}

Vec3 & Vec3::operator+=(const Vec3 & rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vec3 Vec3::operator-(const Vec3 & rhs)
{
	return Vec3(*this) -= rhs;
}

Vec3 & Vec3::operator-=(const Vec3 & rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

float Vec3::operator*(const Vec3 & rhs)
{
	return x * rhs.x + y * rhs.y + z * rhs.z;
}

Vec3 Vec3::operator-()
{
	return Vec3(-x, -y, -z);
}


/*
** Mat2
*/

Mat2 Mat2::operator*(float rhs)
{
	return Mat2(*this) *= rhs;
}

Mat2 & Mat2::operator*=(float rhs)
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			elements[i][j] *= rhs;
		}
	}
	return *this;
}

Mat2 Mat2::operator*(const Mat2 & rhs)
{
	Mat2 result;

	for (int y = 0; y < 2; y++) {
		for (int x = 0; x < 2; x++) {
			float sum = 0.0f;
			for (int i = 0; i < 2; i++) {
				sum += elements[y][i] * rhs.elements[i][x];
			}
			result.elements[y][x] = sum;
		}
	}

	return result;
}

Mat2 & Mat2::operator*=(const Mat2 & rhs)
{
	return (*this) = (*this) * rhs;
}

Mat2 Mat2::Identity()
{
	return Mat2(
		1.0f, 0.0f,
		0.0f, 1.0f
	);
}

Mat2 Mat2::Scaling(float factor)
{
	return Mat2(
		factor, 0.0f,
		0.0f, factor
	);
}

Mat2 Mat2::Rotation(float theta)
{
	float cosTheta = cosf(theta);
	float sinTheta = sinf(theta);

	return Mat2(
		cosTheta, sinTheta,
		-sinTheta, cosTheta
	);
}


/*
** Mat3
*/

Mat3 Mat3::operator*(float rhs)
{
	return Mat3(*this) *= rhs;
}

Mat3 & Mat3::operator*=(float rhs)
{
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			elements[y][x] *= rhs;
		}
	}
	return *this;
}

Mat3 Mat3::operator*(const Mat3 & rhs)
{
	Mat3 result;

	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			float sum = 0.0f;
			for (int i = 0; i < 3; i++) {
				sum += elements[y][i] * rhs.elements[i][x];
			}
			result.elements[y][x] = sum;
		}
	}

	return result;
}

Mat3 & Mat3::operator*=(const Mat3 & rhs)
{
	return (*this) = (*this) * rhs;
}

Mat3 Mat3::Identity()
{
	return Mat3(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	);
}

Mat3 Mat3::Scaling(float factor)
{
	return Mat3(
		factor, 0.0f, 0.0f,
		0.0f, factor, 0.0f,
		0.0f, 0.0f, factor
	);
}

Mat3 Mat3::RotationZ(float theta)
{
	float cosTheta = cos(theta);
	float sinTheta = sin(theta);

	return Mat3(
		cosTheta, sinTheta, 0.0f,
		-sinTheta, cosTheta, 0.0f,
		0.0f, 0.0f, 1.0f
	);
}

Mat3 Mat3::RotationY(float theta)
{
	float cosTheta = cos(theta);
	float sinTheta = sin(theta);

	return Mat3(
		cosTheta, 0.0f, -sinTheta,
		0.0f, 1.0f, 0.0f,
		sinTheta, 0.0f, cosTheta
	);
}

Mat3 Mat3::RotationX(float theta)
{
	float cosTheta = cos(theta);
	float sinTheta = sin(theta);

	return Mat3(
		1.0f, 0.0f, 0.0f,
		0.0f, cosTheta, sinTheta,
		0.0f, -sinTheta, cosTheta
	);
}


/*
** Vector-Matrix Operators
*/

Vec2 operator*(const Vec2 & lhs, const Mat2 & rhs)
{
	return Vec2(
		lhs.x * rhs.elements[0][0] + lhs.y * rhs.elements[1][0],
		lhs.x * rhs.elements[0][1] + lhs.y * rhs.elements[1][1]
	);
}

Vec2 & operator*=(Vec2 & lhs, const Mat2 & rhs)
{
	return lhs = lhs * rhs;
}

Vec3 operator*(const Vec3 & lhs, const Mat3 & rhs)
{
	return Vec3(
		lhs.x * rhs.elements[0][0] + lhs.y * rhs.elements[1][0] + lhs.z * rhs.elements[2][0],
		lhs.x * rhs.elements[0][1] + lhs.y * rhs.elements[1][1] + lhs.z * rhs.elements[2][1],
		lhs.x * rhs.elements[0][2] + lhs.y * rhs.elements[1][2] + lhs.z * rhs.elements[2][2]
	);
}

Vec3 & operator*=(Vec3 & lhs, const Mat3 & rhs)
{
	return lhs = lhs * rhs;
}
