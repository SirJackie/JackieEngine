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

FCamera::FCamera()
{
	position = FVector4D();
	rotation = FVector4D();
	frustum  = FFrustum();

	TranslationMatrix = FMatrix4D();
	RotationMatrix    = FMatrix4D();
	ProjectionMatrix  = FMatrix4D();
	TotalMatrix       = FMatrix4D();
}

FCamera::FCamera
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

void FCamera::CalcTranslation() {
	TranslationMatrix = FMatrix4D::GenerateTranslationMatrix
	(
		position.x, position.y, position.z
	);
}

void FCamera::CalcRotation() {
	RotationMatrix = FMatrix4D::GenerateRotationMatrix
	(
		rotation.x, rotation.y, rotation.z
	);
}

void FCamera::CalcProjection() {
	ProjectionMatrix = FMatrix4D
	(
		frustum.hh * frustum.fot, 0, frustum.hw, 0,
		0, -frustum.hh * frustum.fot, frustum.hh, 0,
		0, 0, (frustum.n + frustum.f) / (frustum.n - frustum.f), (-2.0f * frustum.f * frustum.n) / (frustum.n - frustum.f),
		0, 0, 1, 0
	);
}

void FCamera::CalcTotal() {
	CalcTranslation();
	CalcRotation();
	CalcProjection();
	TotalMatrix = TranslationMatrix * RotationMatrix * ProjectionMatrix;
}

string FCamera::ToString() {
	return "FCamera:\n" + TotalMatrix.ToString();
}

void FCamera::ProjectObject(FObject& obj) {
	obj.tmpVl = obj.vl;
	for (ui32 i = 0; i < obj.tmpVl.size(); i++) {
		obj.tmpVl[i] = obj.tmpVl[i] * TotalMatrix;
		obj.tmpVl[i].DevideByW();
	}
}

void FCamera::Walk(const FVector4D& direction_){
	FVector4D direction = direction_;
	FMatrix4D rotmat = FMatrix4D::GenerateRotationMatrix(
		0.0f, -rotation.y, 0.0f
	);
	direction = direction * rotmat;
	position = position + direction;
	CalcTotal();
}

void FCamera::Rotate(f32 x_, f32 y_, f32 z_){
	rotation.x += x_;
	rotation.y += y_;
	rotation.z += z_;
	CalcTotal();
}
