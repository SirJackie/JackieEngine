#ifndef __JKEG_CameraSupport__
#define __JKEG_CameraSupport__

#include <cmath>
#include "MathSupport.h"
#include "ObjectSupport.h"


/*
** FCamera4D
*/

class FCamera4D {
private:

	// Position
	FVector4D position;
	FVector4D rotation;

	// Frustum
	float n;
	float f;
	float t;
	float b;
	float l;
	float r;
	float fovY;
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
		float x, float y, float z, float rotx, float roty, float rotz,
		float n, float f, float fovY, int ScreenWidth, int ScreenHeight
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
