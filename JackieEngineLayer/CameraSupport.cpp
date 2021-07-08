#include "CameraSupport.h"
#include <cmath>
using std::abs;

FCamera4D::FCamera4D(
	float x_, float y_, float z_, float rotx_, float roty_, float rotz_,
	float n_, float f_, float fovY_, int ScreenWidth_, int ScreenHeight_
)
{

	this->position = FVector4D(x_, y_, z_, 1);
	this->rotation = FVector4D(rotx_, roty_, rotz_, 1);

	this->n = n_;
	this->f = f_;
	this->fovY = fovY_;
	this->ScreenWidth = ScreenWidth_;
	this->ScreenHeight = ScreenHeight_;

	this->t = abs(this->n) * CS_tan(this->fovY / 2.0f);
	this->b = -1.0f * this->t;

	this->r = this->ScreenWidth * this->t / this->ScreenHeight;
	this->l = -1.0f * this->r;

	CalcAllTheMatricies();
}

void FCamera4D::CalcTranslation() {
	TranslationMatrix = FMatrix4D(
		1.0f, 0.0f, 0.0f, -1.0f * (this->position.x),
		0.0f, 1.0f, 0.0f, -1.0f * (this->position.y),
		0.0f, 0.0f, 1.0f, -1.0f * (this->position.z),
		0.0f, 0.0f, 0.0f,  1.0f
	);
}

void FCamera4D::CalcRotation() {
	FMatrix4D MrotationX = FMatrix4D(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, CS_cos(this->rotation.x), -1.0f * CS_sin(this->rotation.x), 0.0f,
		0.0f, CS_sin(this->rotation.x), CS_cos(this->rotation.x), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	FMatrix4D MrotationY = FMatrix4D(
		CS_cos(this->rotation.y), 0.0f, CS_sin(this->rotation.y), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-1.0f * CS_sin(this->rotation.y), 0.0f, CS_cos(this->rotation.y), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	FMatrix4D MrotationZ = FMatrix4D(
		CS_cos(this->rotation.z), -1.0f * CS_sin(this->rotation.z), 0.0f, 0.0f,
		CS_sin(this->rotation.z), CS_cos(this->rotation.z), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	RotationMatrix = MrotationZ * MrotationY;
	RotationMatrix = RotationMatrix * MrotationX;
}

void FCamera4D::CalcOrthographicProjection() {
	FMatrix4D Morthoa = FMatrix4D(
		1.0f, 0.0f, 0.0f, -1.0f * (this->r + this->l) / 2.0f,
		0.0f, 1.0f, 0.0f, -1.0f * (this->t + this->b) / 2.0f,
		0.0f, 0.0f, 1.0f, -1.0f * (this->n + this->f) / 2.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	FMatrix4D Morthob = FMatrix4D(
		2.0f / (this->r - this->l), 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / (this->t - this->b), 0.0f, 0.0f,
		0.0f, 0.0f, 2.0f / (this->n - this->f), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	OrthographicProjectionMatrix = Morthoa * Morthob;
}

void FCamera4D::CalcPerspectiveProjection() {
	CalcOrthographicProjection();

	FMatrix4D Mpersp2ortho = FMatrix4D(
		this->n, 0.0, 0.0, 0.0,
		0.0, this->n, 0.0, 0.0,
		0.0, 0.0, this->f + this->n, -1 * this->f * this->n,
		0.0, 0.0, 1.0, 0.0
	);

	PerspectiveProjectionMatrix = Mpersp2ortho * OrthographicProjectionMatrix;
}

void FCamera4D::CalcViewport() {
	FMatrix4D MviewportPre = FMatrix4D(
		this->ScreenWidth / 2.0f, 0.0f, 0.0f, this->ScreenWidth / 2.0f,
		0.0f, this->ScreenHeight / 2.0f, 0.0f, this->ScreenHeight / 2.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	FMatrix4D MYReverse = FMatrix4D(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f, (float)this->ScreenHeight,
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
