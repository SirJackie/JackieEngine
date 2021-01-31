#ifndef __JKEG_ModelSupport
#define __JKEG_ModelSupport

#include <stdio.h>
#include <math.h>
#include "LinearAlgebra.h"


Matrix4D CreateRotationMatrix(float rotx, float roty, float rotz) {
	Matrix4D MrotationX = CreateMatrix4D(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cosd(rotx), -1.0f * sind(rotx), 0.0f,
		0.0f, sind(rotx), cosd(rotx), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	Matrix4D MrotationY = CreateMatrix4D(
		cosd(roty), 0.0f, sind(roty), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-1.0f * sind(roty), 0.0f, cosd(roty), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	Matrix4D MrotationZ = CreateMatrix4D(
		cosd(rotz), -1.0f * sind(rotz), 0.0f, 0.0f,
		sind(rotz), cosd(rotz), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	Matrix4D Mrotation = Matrix4DTimesMatrix4D(
		&MrotationX,
		&MrotationY
	);

	Mrotation = Matrix4DTimesMatrix4D(
		&(Mrotation),
		&MrotationZ
	);

	return Mrotation;
}

#endif
