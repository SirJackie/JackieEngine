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

	ss << "Vector4D[";
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
