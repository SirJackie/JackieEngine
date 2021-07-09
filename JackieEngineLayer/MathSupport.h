#ifndef __JKEG_MathSupport__
#define __JKEG_MathSupport__

#include "../CrossBufferLayer/BasicDataTypeDeclarations.h"


/*
** FVector4D
*/

class FVector4D {
public:
	f32 x;
	f32 y;
	f32 z;
	f32 w;

	FVector4D(f32 x_, f32 y_, f32 z_, f32 w_);
	FVector4D();
	string     ToString()                   const;
	f32        length()                     const;
	FVector4D  normalized()                 const;
	void       Normalize();
	void       DevideByW();

	// Vector-Scalar Calculation
	friend FVector4D operator+(const FVector4D& a, f32 b);
	friend FVector4D operator+(f32 b, const FVector4D& a);
	friend FVector4D operator-(const FVector4D& a, f32 b);
	friend FVector4D operator-(f32 b, const FVector4D& a);
	friend FVector4D operator*(const FVector4D& a, f32 b);
	friend FVector4D operator*(f32 b, const FVector4D& a);

	// Vector-Vector Calculation
	FVector4D  operator+(const FVector4D& b) const;
	FVector4D  operator-(const FVector4D& b) const;
	f32        operator*(const FVector4D& b) const;  // Dot   Product
	FVector4D  operator%(const FVector4D& b) const;  // Cross Product
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
	friend FVector4D operator*(FVector4D& v, FMatrix4D& m);
	friend FMatrix4D operator*(FMatrix4D& a, FMatrix4D& b);

	static FMatrix4D GenerateTranslationMatrix (f32 x, f32 y, f32 z);
	static FMatrix4D GenerateRotationMatrix    (f32 x, f32 y, f32 z);
};
#endif
