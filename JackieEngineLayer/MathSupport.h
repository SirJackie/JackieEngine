#ifndef __JKEG_MathSupport__
#define __JKEG_MathSupport__

#include "../CrossBufferLayer/BasicDataTypeDeclarations.h"


/*
** FVector4D
*/

class FVector3D{
public:
	f32 x;
	f32 y;
	f32 z;

	FVector3D() : x(0.0f), y(0.0f), z(0.0f) {}
	FVector3D(f32 x_, f32 y_, f32 z_) : x(x_), y(y_), z(z_) {}

	// Methods
	string     ToString()                   const;

	// Vector-Scalar Calculation
	friend const FVector3D operator+(const FVector3D& a, const f32 b);
	friend const FVector3D operator+(const f32 b, const FVector3D& a);
	friend const FVector3D operator-(const FVector3D& a, const f32 b);
	friend const FVector3D operator-(const f32 b, const FVector3D& a);
	friend const FVector3D operator*(const FVector3D& a, const f32 b);
	friend const FVector3D operator*(const f32 b, const FVector3D& a);
	friend const FVector3D operator/(const FVector3D& a, const f32 b);
	friend const FVector3D operator/(const f32 b, const FVector3D& a);
	virtual FVector3D& operator+=(const f32& b);
	virtual FVector3D& operator-=(const f32& b);
	virtual FVector3D& operator*=(const f32& b);
	virtual FVector3D& operator/=(const f32& b);

	// Vector-Vector Calculation
	friend const FVector3D operator+(const FVector3D& a, const FVector3D& b);
	friend const FVector3D operator-(const FVector3D& a, const FVector3D& b);
	virtual FVector3D& operator+=(const FVector3D& b);
	virtual FVector3D& operator-=(const FVector3D& b);

	// Interpolation
	virtual const FVector3D InterpolateTo(const FVector3D& b, f32 alpha) const;
};

class FVector4D : public FVector3D {
public:
	f32 w;

	FVector4D() : FVector3D(), w(0.0f) {}
	FVector4D(f32 x_, f32 y_, f32 z_, f32 w_) : FVector3D(x_, y_, z_), w(w_) {}
	
	// Methods
	string     ToString()                   const;
	f32        Length()                     const;
	FVector4D  Normalized()                 const;
	void       Normalize();
	void       DevideByW();

	// Vector-Scalar Calculation
	friend const FVector4D operator+(const FVector4D& a, const f32 b);
	friend const FVector4D operator+(const f32 b, const FVector4D& a);
	friend const FVector4D operator-(const FVector4D& a, const f32 b);
	friend const FVector4D operator-(const f32 b, const FVector4D& a);
	friend const FVector4D operator*(const FVector4D& a, const f32 b);
	friend const FVector4D operator*(const f32 b, const FVector4D& a);
	friend const FVector4D operator/(const FVector4D& a, const f32 b);
	friend const FVector4D operator/(const f32 b, const FVector4D& a);
	virtual FVector4D& operator+=(const f32& b);
	virtual FVector4D& operator-=(const f32& b);
	virtual FVector4D& operator*=(const f32& b);
	virtual FVector4D& operator/=(const f32& b);

	// Vector-Vector Calculation
	friend const FVector4D operator+(const FVector4D& a, const FVector4D& b);
	friend const FVector4D operator-(const FVector4D& a, const FVector4D& b);
	friend const f32       operator*(const FVector4D& a, const FVector4D& b);  // Dot   Product
	friend const FVector4D operator%(const FVector4D& a, const FVector4D& b);  // Cross Product
	virtual FVector4D& operator+=(const FVector4D& b);
	virtual FVector4D& operator-=(const FVector4D& b);

	// Interpolation
	virtual const FVector4D InterpolateTo(const FVector4D& b, f32 alpha) const;
};

class FVectorTex{
public:
	FVector4D pos;
	FVector3D tex;

	FVectorTex();
	FVectorTex(const FVectorTex& fvt);
	FVectorTex(const FVector4D& pos_, const FVector3D& tex_);

	// Vector-Scalar Calculation
	friend const FVectorTex operator+(const FVectorTex& a, const f32 b);
	friend const FVectorTex operator+(const f32 b, const FVectorTex& a);
	friend const FVectorTex operator-(const FVectorTex& a, const f32 b);
	friend const FVectorTex operator-(const f32 b, const FVectorTex& a);
	friend const FVectorTex operator*(const FVectorTex& a, const f32 b);
	friend const FVectorTex operator*(const f32 b, const FVectorTex& a);
	friend const FVectorTex operator/(const FVectorTex& a, const f32 b);
	friend const FVectorTex operator/(const f32 b, const FVectorTex& a);
	FVectorTex& operator+=(const f32& b);
	FVectorTex& operator-=(const f32& b);
	FVectorTex& operator*=(const f32& b);
	FVectorTex& operator/=(const f32& b);

	// Vector-Vector Calculation
	friend const FVectorTex operator+(const FVectorTex& a, const FVectorTex& b);
	friend const FVectorTex operator-(const FVectorTex& a, const FVectorTex& b);
	FVectorTex& operator+=(const FVectorTex& b);
	FVectorTex& operator-=(const FVectorTex& b);

	// Interpolation
	const FVectorTex InterpolateTo(const FVectorTex& b, f32 alpha) const;

	string ToString() const;
};


/*
** FMatrix4D
*/

class FMatrix4D {
public:
	f32 m11, m12, m13, m14;
	f32 m21, m22, m23, m24;
	f32 m31, m32, m33, m34;
	f32 m41, m42, m43, m44;

	FMatrix4D(
		f32 m11, f32 m12, f32 m13, f32 m14,
		f32 m21, f32 m22, f32 m23, f32 m24,
		f32 m31, f32 m32, f32 m33, f32 m34,
		f32 m41, f32 m42, f32 m43, f32 m44
	);
	FMatrix4D();

	string ToString() const;
	friend const FVector4D operator*(const FVector4D& v, const FMatrix4D& m);
	friend const FMatrix4D operator*(const FMatrix4D& a, const FMatrix4D& b);

	static FMatrix4D GenerateTranslationMatrix (f32 x, f32 y, f32 z);
	static FMatrix4D GenerateRotationMatrix    (f32 x, f32 y, f32 z);
};
#endif
