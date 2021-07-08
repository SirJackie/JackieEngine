#ifndef __JKEG_MathSupport__
#define __JKEG_MathSupport__

#include "../CrossBufferLayer/BasicDataTypeDeclarations.h"


/*
** Vector4D
*/

class FVector4D {
public:
	float x;
	float y;
	float z;
	float w;

	FVector4D(float x_, float y_, float z_, float w_);
	FVector4D();
	string     str()                        const;
	float      length()                     const;
	FVector4D  normalized()                 const;
	void       Normalize();
	void       DevideByW();
	FVector4D  operator+(const FVector4D& b) const;
	FVector4D  operator-(const FVector4D& b) const;
	float      operator*(const FVector4D& b) const;  // Dot   Product
	FVector4D  operator%(const FVector4D& b) const;  // Cross Product
};


/*
** Matrix4D
*/

class FMatrix4D {
public:
	float m11, m12, m13, m14;
	float m21, m22, m23, m24;
	float m31, m32, m33, m34;
	float m41, m42, m43, m44;

	FMatrix4D(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44
	);
	FMatrix4D();

	string str() const;
	friend FVector4D operator*(FVector4D& v, FMatrix4D& m);
	friend FMatrix4D operator*(FMatrix4D& a, FMatrix4D& b);
};
#endif
