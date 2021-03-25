#include "MathSupport.h"
#include <string>
#include <sstream>
using std::string;
using std::stringstream;
using std::sqrtf;

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

float fmin3(float a, float b, float c) {
	float min = a;
	if (b < min) {
		min = b;
	}
	if (c < min) {
		min = c;
	}
	return min;
}

float fmax3(float a, float b, float c) {
	float max = a;
	if (b > max) {
		max = b;
	}
	if (c > max) {
		max = c;
	}
	return max;
}

Vector4D::Vector4D(float x_, float y_, float z_, float w_) {
	x = x_;
	y = y_;
	z = z_;
	w = w_;
}

Vector4D::Vector4D() {
	x = NAN;
	y = NAN;
	z = NAN;
	w = NAN;
}

string Vector4D::str() const {
	stringstream ss;

	ss << "Vector4D [";
	ss << this->x;
	ss << ", ";
	ss << this->y;
	ss << ", ";
	ss << this->z;
	ss << ", ";
	ss << this->w;
	ss << "]";

	return ss.str();
}

float Vector4D::length() const {
	// Use the Pythagorean Theorem to calculate the length
	return sqrtf(x*x + y*y + z*z);
}

Vector4D Vector4D::normalized() const {
	float length = this->length();
	return Vector4D(
		this->x / length,
		this->y / length,
		this->z / length,
		this->w  // W-Axis is Meaningless, So Do Nothing
	);
}

void Vector4D::Normalize() {
	float length = this->length();
	this->x /= length;
	this->y /= length;
	this->z /= length;
	// W-Axis is Meaningless, So Do Nothing
}

void Vector4D::DevideByW(){
	x /= w;
	y /= w;
	z /= w;
	w =  1;      // The same as w /= w;
}

Vector4D Vector4D::operator+(const Vector4D& b) const {
	const Vector4D& a = *this;

	return Vector4D(
		a.x + b.x,
		a.y + b.y,
		a.z + b.z,
		1
	);
}

Vector4D Vector4D::operator-(const Vector4D& b) const {
	const Vector4D& a = *this;

	return Vector4D(
		a.x - b.x,
		a.y - b.y,
		a.z - b.z,
		1
	);
}

float Vector4D::operator*(const Vector4D& b) const {
	const Vector4D& a = *this;

	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector4D Vector4D::operator%(const Vector4D& b) const {
	const Vector4D& a = *this;
	Vector4D result;

	result.x = a.y * b.z - b.y * a.z;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	result.w = 1;  // W-Axis is Meaningless, So Do Nothing

	return result;
}


Matrix4D::Matrix4D(
	float m11, float m12, float m13, float m14,
	float m21, float m22, float m23, float m24,
	float m31, float m32, float m33, float m34,
	float m41, float m42, float m43, float m44
){
	this->m11 = m11;
	this->m12 = m12;
	this->m13 = m13;
	this->m14 = m14;

	this->m21 = m21;
	this->m22 = m22;
	this->m23 = m23;
	this->m24 = m24;

	this->m31 = m31;
	this->m32 = m32;
	this->m33 = m33;
	this->m34 = m34;

	this->m41 = m41;
	this->m42 = m42;
	this->m43 = m43;
	this->m44 = m44;
}

string Matrix4D::str() const {
	stringstream ss;

	ss  << "\nMatrix4D [\n";
	ss  << this->m11 << ", " << this->m12 << ", "
		<< this->m13 << ", " << this->m14 << ", " << "\n";
	ss  << this->m21 << ", " << this->m22 << ", "
		<< this->m23 << ", " << this->m24 << ", " << "\n";
	ss  << this->m31 << ", " << this->m32 << ", "
		<< this->m33 << ", " << this->m34 << ", " << "\n";
	ss  << this->m41 << ", " << this->m42 << ", "
		<< this->m43 << ", " << this->m44 << ", " << "\n";
	ss  << "]\n";

	return ss.str();
}
