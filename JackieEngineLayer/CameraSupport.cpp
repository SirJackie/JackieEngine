#include "CameraSupport.h"
#include <cmath>
using std::abs;

FCamera4D::FCamera4D
(
	f32 x_, f32 y_, f32 z_, f32 rotx_, f32 roty_, f32 rotz_,
	f32 n_, f32 f_, f32 fovY_, i32 screenWidth_, i32 screenHeight_
)
{

	position = FVector4D(x_, y_, z_, 1);
	rotation = FVector4D(rotx_, roty_, rotz_, 1);
	frustum  = FFrustum(n_, f_, fovY_, screenWidth_, screenHeight_);

	frustum.CalculateFrustum();

	CalcAllTheMatricies();
}

void FCamera4D::CalcTranslation() {
	TranslationMatrix = FMatrix4D(
		1.0f, 0.0f, 0.0f, -1.0f * (position.x),
		0.0f, 1.0f, 0.0f, -1.0f * (position.y),
		0.0f, 0.0f, 1.0f, -1.0f * (position.z),
		0.0f, 0.0f, 0.0f,  1.0f
	);
}

void FCamera4D::CalcRotation() {
	FMatrix4D MrotationX = FMatrix4D(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, CS_cos(rotation.x), -1.0f * CS_sin(rotation.x), 0.0f,
		0.0f, CS_sin(rotation.x), CS_cos(rotation.x), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	FMatrix4D MrotationY = FMatrix4D(
		CS_cos(rotation.y), 0.0f, CS_sin(rotation.y), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-1.0f * CS_sin(rotation.y), 0.0f, CS_cos(rotation.y), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	FMatrix4D MrotationZ = FMatrix4D(
		CS_cos(rotation.z), -1.0f * CS_sin(rotation.z), 0.0f, 0.0f,
		CS_sin(rotation.z), CS_cos(rotation.z), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	RotationMatrix = MrotationZ * MrotationY;
	RotationMatrix = RotationMatrix * MrotationX;
}

void FCamera4D::CalcOrthographicProjection() {
	FMatrix4D Morthoa = FMatrix4D(
		1.0f, 0.0f, 0.0f, -1.0f * (frustum.r + frustum.l) / 2.0f,
		0.0f, 1.0f, 0.0f, -1.0f * (frustum.t + frustum.b) / 2.0f,
		0.0f, 0.0f, 1.0f, -1.0f * (frustum.n + frustum.f) / 2.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	FMatrix4D Morthob = FMatrix4D(
		2.0f / (frustum.r - frustum.l), 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / (frustum.t - frustum.b), 0.0f, 0.0f,
		0.0f, 0.0f, 2.0f / (frustum.n - frustum.f), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	OrthographicProjectionMatrix = Morthoa * Morthob;
}

void FCamera4D::CalcPerspectiveProjection() {
	CalcOrthographicProjection();

	FMatrix4D Mpersp2ortho = FMatrix4D(
		frustum.n, 0.0, 0.0, 0.0,
		0.0, frustum.n, 0.0, 0.0,
		0.0, 0.0, frustum.f + frustum.n, -1 * frustum.f * frustum.n,
		0.0, 0.0, 1.0, 0.0
	);

	PerspectiveProjectionMatrix = Mpersp2ortho * OrthographicProjectionMatrix;
}

void FCamera4D::CalcViewport() {
	FMatrix4D MviewportPre = FMatrix4D(
		frustum.screenWidth / 2.0f, 0.0f, 0.0f, frustum.screenWidth / 2.0f,
		0.0f, frustum.screenHeight / 2.0f, 0.0f, frustum.screenHeight / 2.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	FMatrix4D MYReverse = FMatrix4D(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f, (f32)frustum.screenHeight,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	ViewportMatrix = MviewportPre * MYReverse;
}

void FCamera4D::CalcTranslationAndRotation() {
	CalcTranslation();
	CalcRotation();
	TranslationAndRotationMatrix = TranslationMatrix * RotationMatrix;
}

void FCamera4D::CalcProjectionAndViewport() {
	CalcPerspectiveProjection();
	CalcViewport();
	ProjectionAndViewportMatrix = PerspectiveProjectionMatrix * ViewportMatrix;
}

void FCamera4D::RefreshTranslationAndRotation() {
	CalcTranslationAndRotation();
	//CalcProjectionAndViewport();
	TotalTransformMatrix = TranslationAndRotationMatrix * ProjectionAndViewportMatrix;
}
void FCamera4D::CalcAllTheMatricies() {
	CalcTranslationAndRotation();
	CalcProjectionAndViewport();
	TotalTransformMatrix = TranslationAndRotationMatrix * ProjectionAndViewportMatrix;
}

string FCamera4D::str() {
	return "\nCamera. TotalTransformMatrix: " + TotalTransformMatrix.str() + "\n";
}

void FCamera4D::ProjectObject(Object4D& obj) {
	for (ui32 i = 0; i < obj.vecs.size(); i++) {
		obj.vecs[i] = obj.vecs[i] * TotalTransformMatrix;
		obj.vecs[i].DevideByW();
	}
}

FFrustum::FFrustum()
{
	n = 0.0f; f = 0.0f; t = 0.0f; b = 0.0f; l = 0.0f; r = 0.0f;
	fovY = 0.0f; screenWidth = 0; screenHeight = 0;
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
}
