#ifndef __JKEG_CameraSupport__
#define __JKEG_CameraSupport__

#include <cmath>
#include "MathSupport.h"


/*
** Camera4D Definition
*/

class Camera4D {
public:

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
	Matrix4D ProjectionAndViewportMatrix;
	Matrix4D TotalTransformMatrix;

	// Methods
	Camera4D(
		float x, float y, float z, float rotx, float roty, float rotz,
		float n, float f, float fovY, int ScreenWidth, int ScreenHeight
	);
	void CalcTranslation();
	void CalcRotation();
	void CalcOrthographicProjection();
	void CalcPerspectiveProjection();
};

//void CalcCamera4DMviewport(Camera4D* cam) {
//	Matrix4D MviewportPre = CreateMatrix4D(
//		cam->ScreenWidth / 2.0, 0.0, 0.0, cam->ScreenWidth / 2.0,
//		0.0, cam->ScreenHeight / 2.0, 0.0, cam->ScreenHeight / 2.0,
//		0.0, 0.0, 1.0, 0.0,
//		0.0, 0.0, 0.0, 1.0
//	);
//
//	Matrix4D MYReverse = CreateMatrix4D(
//		1.0, 0.0, 0.0, 0.0,
//		0.0, -1.0, 0.0, cam->ScreenHeight,
//		0.0, 0.0, 1.0, 0.0,
//		0.0, 0.0, 0.0, 1.0
//	);
//
//	cam->Mviewport = Matrix4DTimesMatrix4D(&MviewportPre, &MYReverse);
//}
//
//
///*
//** Functions that Merge Matrices Together In Order To Speed Up
//*/
//
//void CalcCamera4DMprojAndviewport(Camera4D* cam) {
//	CalcCamera4DMpersp(cam);
//	CalcCamera4DMviewport(cam);
//	cam->MprojAndviewport = Matrix4DTimesMatrix4D(
//		&(cam->Mpersp),
//		&(cam->Mviewport)
//	);
//}
//
//void CalcCamera4DMatrices(Camera4D* cam) {
//	CalcCamera4DMtranslation(cam);
//	CalcCamera4DMrotation(cam);
//	CalcCamera4DMprojAndviewport(cam);
//	cam->Mtransform = Matrix4DTimesMatrix4D(
//		&(cam->Mtranslation),
//		&(cam->Mrotation)
//	);
//	cam->Mtransform = Matrix4DTimesMatrix4D(
//		&(cam->Mtransform),
//		&(cam->MprojAndviewport)
//	);
//}
//
//void RefreshCamera4DMatrices(Camera4D* cam) {
//	CalcCamera4DMtranslation(cam);
//	CalcCamera4DMrotation(cam);
//	// cam->MprojAndviewport is not changed
//	cam->Mtransform = Matrix4DTimesMatrix4D(
//		&(cam->Mtranslation),
//		&(cam->Mrotation)
//	);
//	cam->Mtransform = Matrix4DTimesMatrix4D(
//		&(cam->Mtransform),
//		&(cam->MprojAndviewport)
//	);
//}

#endif
