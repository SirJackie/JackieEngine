#include "CameraSupport.h"
#include <cmath>
using std::abs;

Camera4D::Camera4D(
	float x_, float y_, float z_, float rotx_, float roty_, float rotz_,
	float n_, float f_, float fovY_, int ScreenWidth_, int ScreenHeight_
)
{

	this->position = Vector4D(x_, y_, z_, 1);
	this->rotation = Vector4D(rotx_, roty_, rotz_, 1);

	this->n = n_;
	this->f = f_;
	this->fovY = fovY_;
	this->ScreenWidth = ScreenWidth_;
	this->ScreenHeight = ScreenHeight_;

	this->t = abs(this->n) * tand(this->fovY / 2.0f);
	this->b = -1.0f * this->t;

	this->r = this->ScreenWidth * this->t / this->ScreenHeight;
	this->l = -1.0f * this->r;

	CalcAllTheMatricies();
}

void Camera4D::CalcTranslation() {
	TranslationMatrix = Matrix4D(
		1.0f, 0.0f, 0.0f, -1.0f * (this->position.x),
		0.0f, 1.0f, 0.0f, -1.0f * (this->position.y),
		0.0f, 0.0f, 1.0f, -1.0f * (this->position.z),
		0.0f, 0.0f, 0.0f,  1.0f
	);
}

void Camera4D::CalcRotation() {
	Matrix4D MrotationX = Matrix4D(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cosd(this->rotation.x), -1.0f * sind(this->rotation.x), 0.0f,
		0.0f, sind(this->rotation.x), cosd(this->rotation.x), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	Matrix4D MrotationY = Matrix4D(
		cosd(this->rotation.y), 0.0f, sind(this->rotation.y), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-1.0f * sind(this->rotation.y), 0.0f, cosd(this->rotation.y), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	Matrix4D MrotationZ = Matrix4D(
		cosd(this->rotation.z), -1.0f * sind(this->rotation.z), 0.0f, 0.0f,
		sind(this->rotation.z), cosd(this->rotation.z), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	RotationMatrix = MrotationZ * MrotationY;
	RotationMatrix = RotationMatrix * MrotationX;
}

void Camera4D::CalcOrthographicProjection() {
	Matrix4D Morthoa = Matrix4D(
		1.0f, 0.0f, 0.0f, -1.0f * (this->r + this->l) / 2.0f,
		0.0f, 1.0f, 0.0f, -1.0f * (this->t + this->b) / 2.0f,
		0.0f, 0.0f, 1.0f, -1.0f * (this->n + this->f) / 2.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	Matrix4D Morthob = Matrix4D(
		2.0f / (this->r - this->l), 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f / (this->t - this->b), 0.0f, 0.0f,
		0.0f, 0.0f, 2.0f / (this->n - this->f), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	OrthographicProjectionMatrix = Morthoa * Morthob;
}

void Camera4D::CalcPerspectiveProjection() {
	CalcOrthographicProjection();

	Matrix4D Mpersp2ortho = Matrix4D(
		this->n, 0.0, 0.0, 0.0,
		0.0, this->n, 0.0, 0.0,
		0.0, 0.0, this->f + this->n, -1 * this->f * this->n,
		0.0, 0.0, 1.0, 0.0
	);

	PerspectiveProjectionMatrix = Mpersp2ortho * OrthographicProjectionMatrix;
}

void Camera4D::CalcViewport() {
	Matrix4D MviewportPre = Matrix4D(
		this->ScreenWidth / 2.0f, 0.0f, 0.0f, this->ScreenWidth / 2.0f,
		0.0f, this->ScreenHeight / 2.0f, 0.0f, this->ScreenHeight / 2.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	Matrix4D MYReverse = Matrix4D(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f, (float)this->ScreenHeight,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	ViewportMatrix = MviewportPre * MYReverse;
}

void Camera4D::CalcTranslationAndRotation() {
	CalcTranslation();
	CalcRotation();
	TranslationAndRotationMatrix = TranslationMatrix * RotationMatrix;
}

void Camera4D::CalcProjectionAndViewport() {
	CalcPerspectiveProjection();
	CalcViewport();
	ProjectionAndViewportMatrix = PerspectiveProjectionMatrix * ViewportMatrix;
}

void Camera4D::RefreshTranslationAndRotation() {
	CalcTranslationAndRotation();
	//CalcProjectionAndViewport();
	TotalTransformMatrix = TranslationAndRotationMatrix * ProjectionAndViewportMatrix;
}
void Camera4D::CalcAllTheMatricies() {
	CalcTranslationAndRotation();
	CalcProjectionAndViewport();
	TotalTransformMatrix = TranslationAndRotationMatrix * ProjectionAndViewportMatrix;
}

string Camera4D::str() {
	return "\nCamera. TotalTransformMatrix: " + TotalTransformMatrix.str() + "\n";
}

void Camera4D::ProjectObject(Object4D& obj) {
	for (int i = 0; i < obj.vecs.size(); i++) {
		obj.vecs[i] = obj.vecs[i] * TotalTransformMatrix;
		obj.vecs[i].DevideByW();
	}
}
