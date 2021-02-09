#ifndef __JKEG_ModelSupport
#define __JKEG_ModelSupport

#include <stdio.h>
#include <math.h>
#include "LinearAlgebra.h"


Matrix4D CreateRotationMatrix(double rotx, double roty, double rotz) {
	Matrix4D MrotationX = CreateMatrix4D(
		1.0, 0.0, 0.0, 0.0,
		0.0, cosd(rotx), -1.0 * sind(rotx), 0.0,
		0.0, sind(rotx), cosd(rotx), 0.0,
		0.0, 0.0, 0.0, 1.0
	);

	Matrix4D MrotationY = CreateMatrix4D(
		cosd(roty), 0.0, sind(roty), 0.0,
		0.0, 1.0, 0.0, 0.0,
		-1.0 * sind(roty), 0.0, cosd(roty), 0.0,
		0.0, 0.0, 0.0, 1.0
	);

	Matrix4D MrotationZ = CreateMatrix4D(
		cosd(rotz), -1.0 * sind(rotz), 0.0, 0.0,
		sind(rotz), cosd(rotz), 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
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
