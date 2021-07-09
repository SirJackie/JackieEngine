#ifndef __JKEG_CameraSupport__
#define __JKEG_CameraSupport__

#include "../CrossBufferLayer/BasicDataTypeDeclarations.h"
#include "MathSupport.h"
#include "ObjectSupport.h"


/*
** FFrustum
*/

class FFrustum {
public:
	f32 n;
	f32 f;
	f32 t;
	f32 b;
	f32 l;
	f32 r;
	f32 fovY;
	f32 fot;    // FoV-Tangent Reation
	f32 hw;     // Half of Screen Width
	f32 hh;     // Half of Screen Height
	i32 screenWidth;
	i32 screenHeight;

	FFrustum();
	FFrustum
	(
		f32 n_, f32 f_, f32 fovY_, i32 screenWidth_, i32 screenHeight_
	);
	void CalculateFrustum();
};


/*
** FCamera4D
*/

class FCamera {
private:

	// Position
	FVector4D position;
	FVector4D rotation;

	// Frustum
	FFrustum  frustum;

	// Matricies
	FMatrix4D TranslationMatrix;
	FMatrix4D RotationMatrix;
	FMatrix4D ProjectionMatrix;
	FMatrix4D TotalMatrix;

public:
	// Methods
	FCamera();
	FCamera(
		f32 x_, f32 y_, f32 z_, f32 rotx_, f32 roty_, f32 rotz_,
		f32 n_, f32 f_, f32 fovY_, i32 screenWidth_, i32 screenHeight_
	);
	void CalcTranslation();
	void CalcRotation();
	void CalcProjection();
	void CalcTotal();

	string str();
	void ProjectObject(FObject& obj);
};
#endif
