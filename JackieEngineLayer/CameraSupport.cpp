#include "CameraSupport.h"

FFrustum::FFrustum()
{
	n = 0.0f; f = 0.0f; t = 0.0f; b = 0.0f; l = 0.0f; r = 0.0f;
	fovY = 0.0f; fot = 0.0f; hw = 0.0f; hh = 0.0f;
	screenWidth = 0; screenHeight = 0;
}

FFrustum::FFrustum
(
	f32 n_, f32 f_, f32 fovY_, i32 screenWidth_, i32 screenHeight_
)
{
	n = n_; f = f_; fovY = fovY_;
	screenWidth = screenWidth_; screenHeight = screenHeight_;

	CalculateFrustum();
}

void FFrustum::CalculateFrustum()
{
	t = abs(n) * CS_tan(fovY / 2.0f);
	b = -1.0f * t;

	r = screenWidth * t / screenHeight;
	l = -1.0f * r;

	fot = -1.0f / CS_tan(fovY / 2);
	hw = (f32)screenWidth  / 2.0f;
	hh = (f32)screenHeight / 2.0f;
}

FCamera4D::FCamera4D
(
	f32 x_, f32 y_, f32 z_, f32 rotx_, f32 roty_, f32 rotz_,
	f32 n_, f32 f_, f32 fovY_, i32 screenWidth_, i32 screenHeight_
)
{

	position = FVector4D(x_, y_, z_, 1);
	rotation = FVector4D(rotx_, roty_, rotz_, 1);
	frustum = FFrustum(n_, f_, fovY_, screenWidth_, screenHeight_);

	frustum.CalculateFrustum();
	CalcTotal();
}

void FCamera4D::CalcTranslation() {
	TranslationMatrix = FMatrix4D::GenerateTranslationMatrix
	(
		position.x, position.y, position.z
	);
}

void FCamera4D::CalcRotation() {
	RotationMatrix = FMatrix4D::GenerateRotationMatrix
	(
		rotation.x, rotation.y, rotation.z
	);
}

void FCamera4D::CalcProjection() {
	ProjectionMatrix = FMatrix4D
	(
		frustum.hh * frustum.fot, 0, frustum.hw, 0,
		0, -frustum.hh * frustum.fot, frustum.hh, 0,
		0, 0, (frustum.n + frustum.f) / (frustum.n - frustum.f), (-2.0f * frustum.f * frustum.n) / (frustum.n - frustum.f),
		0, 0, 1, 0
	);
}

void FCamera4D::CalcTotal() {
	CalcTranslation();
	CalcRotation();
	CalcProjection();
	TotalMatrix = TranslationMatrix * RotationMatrix;
	TotalMatrix = TotalMatrix *  ProjectionMatrix;
}

string FCamera4D::str() {
	return "\nCamera. TotalTransformMatrix: " + TotalMatrix.str() + "\n";
}

void FCamera4D::ProjectObject(Object4D& obj) {
	for (ui32 i = 0; i < obj.vecs.size(); i++) {
		obj.vecs[i] = obj.vecs[i] * TotalMatrix;
		obj.vecs[i].DevideByW();
	}
}
