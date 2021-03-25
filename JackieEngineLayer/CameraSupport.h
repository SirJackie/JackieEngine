#ifndef __JKEG_CameraSupport__
#define __JKEG_CameraSupport__

#include <cmath>
#include "MathSupport.h"


/*
** Camera4D Definition
*/

class Camera4D {
private:

	// Position
	Vector4D position;
	Vector4D rotation;

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
	Matrix4D TranslationMatrix;
	Matrix4D RotationMatrix;
	Matrix4D OrthographicProjectionMatrix;
	Matrix4D PerspectiveProjectionMatrix;
	Matrix4D ViewportMatrix;
	Matrix4D TranslationAndRotationMatrix;
	Matrix4D ProjectionAndViewportMatrix;
	Matrix4D TotalTransformMatrix;

public:
	// Methods
	Camera4D(
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
};
#endif
