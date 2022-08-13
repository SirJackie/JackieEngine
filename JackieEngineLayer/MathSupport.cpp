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
** Vec2
*/
//
//// Methods
//string Vec2::ToString() const{
//	stringstream ss;
//
//	ss << "Vec2 [";
//	ss << this->x;
//	ss << ", ";
//	ss << this->y;
//	ss << ", ";
//	ss << this->z;
//	ss << "]\n";
//
//	return ss.str();
//}
//
//// Vector-Scalar Calculation
//const Vec2 operator+(const Vec2& a, const f32 b){
//	return Vec2(
//		a.x + b, a.y + b, a.z
//	);
//}
//const Vec2 operator+(const f32 b, const Vec2& a){
//	return Vec2(
//		a.x + b, a.y + b, a.z
//	);
//}
//const Vec2 operator-(const Vec2& a, const f32 b){
//	return Vec2(
//		a.x - b, a.y - b, a.z
//	);
//}
//const Vec2 operator-(const f32 b, const Vec2& a){
//	return Vec2(
//		a.x - b, a.y - b, a.z
//	);
//}
//const Vec2 operator*(const Vec2& a, const f32 b){
//	return Vec2(
//		a.x * b, a.y * b, a.z
//	);
//}
//const Vec2 operator*(const f32 b, const Vec2& a){
//	return Vec2(
//		a.x * b, a.y * b, a.z
//	);
//}
//const Vec2 operator/(const Vec2& a, const f32 b){
//	return Vec2(
//		a.x / b, a.y / b, a.z
//	);
//}
//const Vec2 operator/(const f32 b, const Vec2& a){
//	return Vec2(
//		b / a.x, b / a.y, a.z
//	);
//}
//
//Vec2& Vec2::operator+=(const f32& b){
//	x += b;
//	y += b;
//	return *this;
//}
//
//Vec2& Vec2::operator-=(const f32& b){
//	x -= b;
//	y -= b;
//	return *this;
//}
//
//Vec2& Vec2::operator*=(const f32& b){
//	x *= b;
//	y *= b;
//	return *this;
//}
//
//Vec2& Vec2::operator/=(const f32& b){
//	x /= b;
//	y /= b;
//	return *this;
//}
//
//// Vector-Vector Calculation
//const Vec2 operator+(const Vec2& a, const Vec2& b){
//	return Vec2(
//		a.x + b.x, a.y + b.y, a.z
//	);
//}
//const Vec2 operator-(const Vec2& a, const Vec2& b){
//	return Vec2{
//		a.x - b.x, a.y - b.y, a.z
//	};
//}
//
//Vec2& Vec2::operator+=(const Vec2& b){
//	x += b.x;
//	y += b.y;
//	return *this;
//}
//
//Vec2& Vec2::operator-=(const Vec2& b){
//	x -= b.x;
//	y -= b.y;
//	return *this;
//}
//
//// Interpolation
//const Vec2 Vec2::InterpolateTo(const Vec2& to, f32 alpha) const {
//	const Vec2& from = *this;
//	Vec2 delta  = to - from;
//	return from + delta * alpha;
//}

//
///*
//** Vec3
//*/
//
//// Methods
//string Vec3::ToString() const {
//	stringstream ss;
//
//	ss << "Vec3 [";
//	ss << this->x;
//	ss << ", ";
//	ss << this->y;
//	ss << ", ";
//	ss << this->z;
//	ss << ", ";
//	ss << this->w;
//	ss << "]\n";
//
//	return ss.str();
//}
//
//f32 Vec3::Length() const {
//	// Use the Pythagorean Theorem to calculate the length
//	return sqrtf(x*x + y*y + z*z);
//}
//
//Vec3 Vec3::Normalized() const {
//	f32 length = Length();
//	return Vec3(
//		this->x / length,
//		this->y / length,
//		this->z / length,
//		this->w  // W-Axis is Meaningless, So Do Nothing
//	);
//}
//
//void Vec3::Normalize() {
//	f32 length = Length();
//	this->x /= length;
//	this->y /= length;
//	this->z /= length;
//	// W-Axis is Meaningless, So Do Nothing
//}
//
//void Vec3::DevideByW(){
//	x /= w;
//	y /= w;
//	z /= w;
//	w =  1;      // The same as w /= w;
//}
//
//// Vector-Scalar Calculation
//const Vec3 operator+(const Vec3& a, const f32 b)
//{
//	return Vec3(
//		a.x + b, a.y + b, a.z + b, a.w
//	);
//}
//const Vec3 operator+(const f32 b, const Vec3& a)
//{
//	return Vec3
//	(
//		a.x + b, a.y + b, a.z + b, a.w
//	);
//}
//
//const Vec3 operator-(const Vec3& a, const f32 b)
//{
//	return Vec3(
//		a.x - b, a.y - b, a.z - b, a.w
//	);
//}
//
//const Vec3 operator-(const f32 b, const Vec3& a)
//{
//	return Vec3(
//		a.x - b, a.y - b, a.z - b, a.w
//	);
//}
//
//const Vec3 operator*(const Vec3& a, const f32 b)
//{
//	return Vec3(
//		a.x * b, a.y * b, a.z * b, a.w
//	);
//}
//
//const Vec3 operator*(const f32 b, const Vec3& a)
//{
//	return Vec3(
//		a.x * b, a.y * b, a.z * b, a.w
//	);
//}
//
//const Vec3 operator/(const Vec3& a, const f32 b)
//{
//	return Vec3(
//		a.x / b, a.y / b, a.z / b, a.w
//	);
//}
//
//const Vec3 operator/(const f32 b, const Vec3& a)
//{
//	return Vec3(
//		b / a.x, b / a.y, b / a.z, a.w
//	);
//}
//
//Vec3& Vec3::operator+=(const f32& b){
//	x += b;
//	y += b;
//	z += b;
//	return *this;
//}
//
//Vec3& Vec3::operator-=(const f32& b){
//	x -= b;
//	y -= b;
//	z -= b;
//	return *this;
//}
//
//Vec3& Vec3::operator*=(const f32& b){
//	x *= b;
//	y *= b;
//	z *= b;
//	return *this;
//}
//
//Vec3& Vec3::operator/=(const f32& b){
//	x /= b;
//	y /= b;
//	z /= b;
//	return *this;
//}
//
//// Vector-Vector Calculation
//const Vec3 operator+(const Vec3& a, const Vec3& b){
//	return Vec3(
//		a.x + b.x, a.y + b.y, a.z + b.z, a.w
//	);
//}
//
//const Vec3 operator-(const Vec3& a, const Vec3& b){
//	return Vec3(
//		a.x - b.x, a.y - b.y, a.z - b.z, a.w
//	);
//}
//
//const f32 operator*(const Vec3& a, const Vec3& b){
//	return a.x * b.x + a.y * b.y + a.z * b.z;
//}
//
//const Vec3 operator%(const Vec3& a, const Vec3& b){
//	return Vec3(
//		a.y * b.z - b.y * a.z,
//		a.z * b.x - a.x * b.z,
//		a.x * b.y - a.y * b.x,
//		a.z
//	);
//}
//
//Vec3& Vec3::operator+=(const Vec3& b){
//	x += b.x;
//	y += b.y;
//	z += b.z;
//	return *this;
//}
//
//Vec3& Vec3::operator-=(const Vec3& b){
//	x -= b.x;
//	y -= b.y;
//	z -= b.z;
//	return *this;
//}
//
//// Interpolation
//const Vec3 Vec3::InterpolateTo(const Vec3& to, f32 alpha) const {
//	const Vec3& from = *this;
//	Vec3 delta  = to - from;
//	return from + delta * alpha;
//}
//
//
///*
//** Mat3
//*/
//
//Mat3::Mat3(
//	f32 m11_, f32 m12_, f32 m13_, f32 m14_,
//	f32 m21_, f32 m22_, f32 m23_, f32 m24_,
//	f32 m31_, f32 m32_, f32 m33_, f32 m34_,
//	f32 m41_, f32 m42_, f32 m43_, f32 m44_
//){
//	this->m11 = m11_;
//	this->m12 = m12_;
//	this->m13 = m13_;
//	this->m14 = m14_;
//
//	this->m21 = m21_;
//	this->m22 = m22_;
//	this->m23 = m23_;
//	this->m24 = m24_;
//
//	this->m31 = m31_;
//	this->m32 = m32_;
//	this->m33 = m33_;
//	this->m34 = m34_;
//
//	this->m41 = m41_;
//	this->m42 = m42_;
//	this->m43 = m43_;
//	this->m44 = m44_;
//}
//
//Mat3::Mat3() {
//	this->m11 = 0;
//	this->m12 = 0;
//	this->m13 = 0;
//	this->m14 = 0;
//
//	this->m21 = 0;
//	this->m22 = 0;
//	this->m23 = 0;
//	this->m24 = 0;
//
//	this->m31 = 0;
//	this->m32 = 0;
//	this->m33 = 0;
//	this->m34 = 0;
//
//	this->m41 = 0;
//	this->m42 = 0;
//	this->m43 = 0;
//	this->m44 = 0;
//}
//
//string Mat3::ToString() const {
//	stringstream ss;
//
//	ss  << "Mat3 [\n";
//	ss  << this->m11 << ", " << this->m12 << ", "
//		<< this->m13 << ", " << this->m14 << ", " << "\n";
//	ss  << this->m21 << ", " << this->m22 << ", "
//		<< this->m23 << ", " << this->m24 << ", " << "\n";
//	ss  << this->m31 << ", " << this->m32 << ", "
//		<< this->m33 << ", " << this->m34 << ", " << "\n";
//	ss  << this->m41 << ", " << this->m42 << ", "
//		<< this->m43 << ", " << this->m44 << ", " << "\n";
//	ss  << "]\n";
//
//	return ss.str();
//}
//
//Mat3 Mat3::GenerateTranslationMatrix(f32 x, f32 y, f32 z)
//{
//	return Mat3
//	(
//		1.0f, 0.0f, 0.0f, -1.0f * x,
//		0.0f, 1.0f, 0.0f, -1.0f * y,
//		0.0f, 0.0f, 1.0f, -1.0f * z,
//		0.0f, 0.0f, 0.0f,  1.0f
//	);
//}
//
//Mat3 Mat3::GenerateRotationMatrix(f32 x, f32 y, f32 z)
//{
//	Mat3 MrotationX = Mat3(
//		1.0f, 0.0f, 0.0f, 0.0f,
//		0.0f, CS_cos(x), -1.0f * CS_sin(x), 0.0f,
//		0.0f, CS_sin(x), CS_cos(x), 0.0f,
//		0.0f, 0.0f, 0.0f, 1.0f
//	);
//
//	Mat3 MrotationY = Mat3(
//		CS_cos(y), 0.0f, CS_sin(y), 0.0f,
//		0.0f, 1.0f, 0.0f, 0.0f,
//		-1.0f * CS_sin(y), 0.0f, CS_cos(y), 0.0f,
//		0.0f, 0.0f, 0.0f, 1.0f
//	);
//
//	Mat3 MrotationZ = Mat3(
//		CS_cos(z), -1.0f * CS_sin(z), 0.0f, 0.0f,
//		CS_sin(z), CS_cos(z), 0.0f, 0.0f,
//		0.0f, 0.0f, 1.0f, 0.0f,
//		0.0f, 0.0f, 0.0f, 1.0f
//	);
//
//	return MrotationZ * MrotationY * MrotationX;
//}
//
//const Vec3 operator*(const Vec3& v, const Mat3& m) {
//	Vec3 result;
//
//	result.x = m.m11 * v.x + m.m12 * v.y + m.m13 * v.z + m.m14 * v.w;
//	result.y = m.m21 * v.x + m.m22 * v.y + m.m23 * v.z + m.m24 * v.w;
//	result.z = m.m31 * v.x + m.m32 * v.y + m.m33 * v.z + m.m34 * v.w;
//	result.w = m.m41 * v.x + m.m42 * v.y + m.m43 * v.z + m.m44 * v.w;
//
//	return result;
//}
//
//const Mat3 operator*(const Mat3& a, const Mat3& b) {
//	Mat3 result;
//
//	result.m11 = b.m11 * a.m11 + b.m12 * a.m21 + b.m13 * a.m31 + b.m14 * a.m41;
//	result.m21 = b.m21 * a.m11 + b.m22 * a.m21 + b.m23 * a.m31 + b.m24 * a.m41;
//	result.m31 = b.m31 * a.m11 + b.m32 * a.m21 + b.m33 * a.m31 + b.m34 * a.m41;
//	result.m41 = b.m41 * a.m11 + b.m42 * a.m21 + b.m43 * a.m31 + b.m44 * a.m41;
//
//	result.m12 = b.m11 * a.m12 + b.m12 * a.m22 + b.m13 * a.m32 + b.m14 * a.m42;
//	result.m22 = b.m21 * a.m12 + b.m22 * a.m22 + b.m23 * a.m32 + b.m24 * a.m42;
//	result.m32 = b.m31 * a.m12 + b.m32 * a.m22 + b.m33 * a.m32 + b.m34 * a.m42;
//	result.m42 = b.m41 * a.m12 + b.m42 * a.m22 + b.m43 * a.m32 + b.m44 * a.m42;
//
//	result.m13 = b.m11 * a.m13 + b.m12 * a.m23 + b.m13 * a.m33 + b.m14 * a.m43;
//	result.m23 = b.m21 * a.m13 + b.m22 * a.m23 + b.m23 * a.m33 + b.m24 * a.m43;
//	result.m33 = b.m31 * a.m13 + b.m32 * a.m23 + b.m33 * a.m33 + b.m34 * a.m43;
//	result.m43 = b.m41 * a.m13 + b.m42 * a.m23 + b.m43 * a.m33 + b.m44 * a.m43;
//
//	result.m14 = b.m11 * a.m14 + b.m12 * a.m24 + b.m13 * a.m34 + b.m14 * a.m44;
//	result.m24 = b.m21 * a.m14 + b.m22 * a.m24 + b.m23 * a.m34 + b.m24 * a.m44;
//	result.m34 = b.m31 * a.m14 + b.m32 * a.m24 + b.m33 * a.m34 + b.m34 * a.m44;
//	result.m44 = b.m41 * a.m14 + b.m42 * a.m24 + b.m43 * a.m34 + b.m44 * a.m44;
//
//	return result;
//}

