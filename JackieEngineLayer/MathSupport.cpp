#include "MathSupport.h"
#include <string>
#include <sstream>
using std::string;
using std::stringstream;

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
	float m11_, float m12_, float m13_, float m14_,
	float m21_, float m22_, float m23_, float m24_,
	float m31_, float m32_, float m33_, float m34_,
	float m41_, float m42_, float m43_, float m44_
){
	this->m11 = m11_;
	this->m12 = m12_;
	this->m13 = m13_;
	this->m14 = m14_;

	this->m21 = m21_;
	this->m22 = m22_;
	this->m23 = m23_;
	this->m24 = m24_;

	this->m31 = m31_;
	this->m32 = m32_;
	this->m33 = m33_;
	this->m34 = m34_;

	this->m41 = m41_;
	this->m42 = m42_;
	this->m43 = m43_;
	this->m44 = m44_;
}

Matrix4D::Matrix4D() {
	this->m11 = NAN;
	this->m12 = NAN;
	this->m13 = NAN;
	this->m14 = NAN;

	this->m21 = NAN;
	this->m22 = NAN;
	this->m23 = NAN;
	this->m24 = NAN;

	this->m31 = NAN;
	this->m32 = NAN;
	this->m33 = NAN;
	this->m34 = NAN;

	this->m41 = NAN;
	this->m42 = NAN;
	this->m43 = NAN;
	this->m44 = NAN;
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

Vector4D operator*(Vector4D& v, Matrix4D& m) {
	Vector4D result;

	result.x = m.m11 * v.x + m.m12 * v.y + m.m13 * v.z + m.m14 * v.w;
	result.y = m.m21 * v.x + m.m22 * v.y + m.m23 * v.z + m.m24 * v.w;
	result.z = m.m31 * v.x + m.m32 * v.y + m.m33 * v.z + m.m34 * v.w;
	result.w = m.m41 * v.x + m.m42 * v.y + m.m43 * v.z + m.m44 * v.w;

	return result;
}

Matrix4D operator*(Matrix4D& a, Matrix4D& b) {
	Matrix4D result;

	result.m11 = b.m11 * a.m11 + b.m12 * a.m21 + b.m13 * a.m31 + b.m14 * a.m41;
	result.m21 = b.m21 * a.m11 + b.m22 * a.m21 + b.m23 * a.m31 + b.m24 * a.m41;
	result.m31 = b.m31 * a.m11 + b.m32 * a.m21 + b.m33 * a.m31 + b.m34 * a.m41;
	result.m41 = b.m41 * a.m11 + b.m42 * a.m21 + b.m43 * a.m31 + b.m44 * a.m41;

	result.m12 = b.m11 * a.m12 + b.m12 * a.m22 + b.m13 * a.m32 + b.m14 * a.m42;
	result.m22 = b.m21 * a.m12 + b.m22 * a.m22 + b.m23 * a.m32 + b.m24 * a.m42;
	result.m32 = b.m31 * a.m12 + b.m32 * a.m22 + b.m33 * a.m32 + b.m34 * a.m42;
	result.m42 = b.m41 * a.m12 + b.m42 * a.m22 + b.m43 * a.m32 + b.m44 * a.m42;

	result.m13 = b.m11 * a.m13 + b.m12 * a.m23 + b.m13 * a.m33 + b.m14 * a.m43;
	result.m23 = b.m21 * a.m13 + b.m22 * a.m23 + b.m23 * a.m33 + b.m24 * a.m43;
	result.m33 = b.m31 * a.m13 + b.m32 * a.m23 + b.m33 * a.m33 + b.m34 * a.m43;
	result.m43 = b.m41 * a.m13 + b.m42 * a.m23 + b.m43 * a.m33 + b.m44 * a.m43;

	result.m14 = b.m11 * a.m14 + b.m12 * a.m24 + b.m13 * a.m34 + b.m14 * a.m44;
	result.m24 = b.m21 * a.m14 + b.m22 * a.m24 + b.m23 * a.m34 + b.m24 * a.m44;
	result.m34 = b.m31 * a.m14 + b.m32 * a.m24 + b.m33 * a.m34 + b.m34 * a.m44;
	result.m44 = b.m41 * a.m14 + b.m42 * a.m24 + b.m43 * a.m34 + b.m44 * a.m44;

	return result;
}
