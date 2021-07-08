#include "MathSupport.h"

FVector4D::FVector4D(f32 x_, f32 y_, f32 z_, f32 w_) {
	x = x_;
	y = y_;
	z = z_;
	w = w_;
}

FVector4D::FVector4D() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

string FVector4D::str() const {
	stringstream ss;

	ss << "FVector4D [";
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

f32 FVector4D::length() const {
	// Use the Pythagorean Theorem to calculate the length
	return sqrtf(x*x + y*y + z*z);
}

FVector4D FVector4D::normalized() const {
	f32 length = this->length();
	return FVector4D(
		this->x / length,
		this->y / length,
		this->z / length,
		this->w  // W-Axis is Meaningless, So Do Nothing
	);
}

void FVector4D::Normalize() {
	f32 length = this->length();
	this->x /= length;
	this->y /= length;
	this->z /= length;
	// W-Axis is Meaningless, So Do Nothing
}

void FVector4D::DevideByW(){
	x /= w;
	y /= w;
	z /= w;
	w =  1;      // The same as w /= w;
}

FVector4D operator+(const FVector4D& a, f32 b)
{
	return FVector4D
	(
		a.x + b, a.y + b, a.z + b, a.w
	);
}

FVector4D operator+(f32 b, const FVector4D& a)
{
	return FVector4D
	(
		a.x + b, a.y + b, a.z + b, a.w
	);
}

FVector4D operator-(const FVector4D& a, f32 b)
{
	return FVector4D
	(
		a.x - b, a.y - b, a.z - b, a.w
	);
}

FVector4D operator-(f32 b, const FVector4D& a)
{
	return FVector4D
	(
		a.x - b, a.y - b, a.z - b, a.w
	);
}

FVector4D operator*(const FVector4D& a, f32 b)
{
	return FVector4D
	(
		a.x * b, a.y * b, a.z * b, a.w
	);
}

FVector4D operator*(f32 b, const FVector4D& a)
{
	return FVector4D
	(
		a.x * b, a.y * b, a.z * b, a.w
	);
}

FVector4D FVector4D::operator+(const FVector4D& b) const {
	const FVector4D& a = *this;

	return FVector4D(
		a.x + b.x,
		a.y + b.y,
		a.z + b.z,
		1
	);
}

FVector4D FVector4D::operator-(const FVector4D& b) const {
	const FVector4D& a = *this;

	return FVector4D(
		a.x - b.x,
		a.y - b.y,
		a.z - b.z,
		1
	);
}

f32 FVector4D::operator*(const FVector4D& b) const {
	const FVector4D& a = *this;

	return a.x * b.x + a.y * b.y + a.z * b.z;
}

FVector4D FVector4D::operator%(const FVector4D& b) const {
	const FVector4D& a = *this;
	FVector4D result;

	result.x = a.y * b.z - b.y * a.z;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	result.w = 1;  // W-Axis is Meaningless, So Do Nothing

	return result;
}


FMatrix4D::FMatrix4D(
	f32 m11_, f32 m12_, f32 m13_, f32 m14_,
	f32 m21_, f32 m22_, f32 m23_, f32 m24_,
	f32 m31_, f32 m32_, f32 m33_, f32 m34_,
	f32 m41_, f32 m42_, f32 m43_, f32 m44_
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

FMatrix4D::FMatrix4D() {
	this->m11 = 0;
	this->m12 = 0;
	this->m13 = 0;
	this->m14 = 0;

	this->m21 = 0;
	this->m22 = 0;
	this->m23 = 0;
	this->m24 = 0;

	this->m31 = 0;
	this->m32 = 0;
	this->m33 = 0;
	this->m34 = 0;

	this->m41 = 0;
	this->m42 = 0;
	this->m43 = 0;
	this->m44 = 0;
}

string FMatrix4D::str() const {
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

FVector4D operator*(FVector4D& v, FMatrix4D& m) {
	FVector4D result;

	result.x = m.m11 * v.x + m.m12 * v.y + m.m13 * v.z + m.m14 * v.w;
	result.y = m.m21 * v.x + m.m22 * v.y + m.m23 * v.z + m.m24 * v.w;
	result.z = m.m31 * v.x + m.m32 * v.y + m.m33 * v.z + m.m34 * v.w;
	result.w = m.m41 * v.x + m.m42 * v.y + m.m43 * v.z + m.m44 * v.w;

	return result;
}

FMatrix4D operator*(FMatrix4D& a, FMatrix4D& b) {
	FMatrix4D result;

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
