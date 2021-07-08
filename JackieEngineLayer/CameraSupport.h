#ifndef __JKEG_CameraSupport__
#define __JKEG_CameraSupport__

#include <cmath>
#include "MathSupport.h"
#include "ObjectSupport.h"


/*
** FFrustum
*/

//class FFrustum {
//public:
//	
//};


/*
** FCamera4D
*/

class FCamera4D {
private:

	// Position
	FVector4D position;
	FVector4D rotation;

	// Frustum
	f32 n;
	f32 f;
	f32 t;
	f32 b;
	f32 l;
	f32 r;
	f32 fovY;
	int ScreenWidth;
	int ScreenHeight;

	// Matricies
	FMatrix4D TranslationMatrix;
	FMatrix4D RotationMatrix;
	FMatrix4D OrthographicProjectionMatrix;
	FMatrix4D PerspectiveProjectionMatrix;
	FMatrix4D ViewportMatrix;
	FMatrix4D TranslationAndRotationMatrix;
	FMatrix4D ProjectionAndViewportMatrix;
	FMatrix4D TotalTransformMatrix;

public:
	// Methods
	FCamera4D(
		f32 x, f32 y, f32 z, f32 rotx, f32 roty, f32 rotz,
		f32 n, f32 f, f32 fovY, int ScreenWidth, int ScreenHeight
	);
	void CalcTranslation();
	void CalcRotation();
	void CalcOrthographicProjection();
	void CalcPerspectiveProjection();
	void CalcViewport();

	void CalcTranslationAndRotation();
	void CalcProjectionAndViewport();
	void RefreshTranslationAndRotation();
	void CalcAllTheMatricies();

	string str();
	void ProjectObject(Object4D& obj);
};
#endif
