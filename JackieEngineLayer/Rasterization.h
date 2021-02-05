#ifndef __JKEG_Rasterization
#define __JKEG_Rasterization

#include <stdio.h>
#include <math.h>
#include "LinearAlgebra.h"
#include "CameraSupport.h"
#include "ModelSupport.h"
#include "../CrossBufferLayer/CrossBuffer.h"


/*
** Drawing Functions for Vector4D
*/

void DrawVector4D(FrameBuffer fb, Vector4D* vec, int radius) {
	int CentralX = (int)vec->x;
	int CentralY = (int)vec->y;
	int StartX = clamp(0, CentralX - radius, fb.Width);
	int EndX = clamp(0, CentralX + radius, fb.Width);
	int StartY = clamp(0, CentralY - radius, fb.Height);
	int EndY = clamp(0, CentralY + radius, fb.Height);

	for (int y = StartY; y < EndY; y++) {
		for (int x = StartX; x < EndX; x++) {
			SetPixel(fb, x, y, CreateColor(255, 255, 255, 255));
		}
	}
}


/*
** Scan-Line Rasterization
**/

#define TriangleSide int
#define LONGSIDE_RIGHT 0
#define LONGSIDE_LEFT  1

#define VectorOrder int

typedef int* ZBuffer;

typedef Color(*ColorFunction) (double, double, double);

/*
** Flat Bottom Triangle Drawing Functions
*/

void FBDrawColorPixel(
	FrameBuffer fb, ZBuffer zb,
	int x, int y, double z,
	ColorFunction cfun, TriangleSide tris, VectorOrder vodr,
	double w, double a, double b
)
{
	if (zb[y * fb.Width + x] > z) return;  // Z-Buffer Test

	double r = a;                          // The Similarity between this pixel and A
	double s = b - a * b;                  // The Similarity between this pixel and B
	double t = a * b - a - b + 1;          // The Similarity between this pixel and C

	double glr, gls, glt;

	if (tris == LONGSIDE_RIGHT) {
		glr = r + t * w;
		gls = s;
		glt = t - t * w;
	}
	else {   // LONGSIDE_LEFT
		glr = r + s * w;
		gls = t;
		glt = s - s * w;
	}

	switch (vodr) {
	case 123:  //rst
		SetPixel(fb, x, y, cfun(glr, gls, glt));
		break;
	case 132:  //rts
		SetPixel(fb, x, y, cfun(glr, glt, gls));
		break;
	case 213:  //srt
		SetPixel(fb, x, y, cfun(gls, glr, glt));
		break;
	case 231:  //str
		SetPixel(fb, x, y, cfun(gls, glt, glr));
		break;
	case 312:  //trs
		SetPixel(fb, x, y, cfun(glt, glr, gls));
		break;
	case 321:  //tsr
		SetPixel(fb, x, y, cfun(glt, gls, glr));
		break;
	}
}

void FBDrawHLine(
	FrameBuffer fb, ZBuffer zb,
	int y, int i, int j, double iz, double jz,
	ColorFunction cfun, TriangleSide tris, VectorOrder vodr,
	double w, double a
)
{
	int llen = j - i;
	double lIPStep = -1.0f / llen;
	double kzStep = (jz - iz) / llen;

	double b = 1;
	double kz = iz;

	for (int k = i; k < j; k++) {
		FBDrawColorPixel(
			fb, zb,
			k, y, kz,
			cfun, tris, vodr,
			w, a, b
		);
		b += lIPStep;
		kz += kzStep;
	}
}

void DrawFlatBottomTriangle(
	FrameBuffer fb, ZBuffer zb,
	Vector4D* A, Vector4D* B, Vector4D* C,
	ColorFunction cfun, TriangleSide tris, VectorOrder vodr,
	double w
)
{
	double l1DeltaX = B->x - A->x;
	double l1DeltaY = B->y - A->y;

	double l1m = l1DeltaX / l1DeltaY;          // The Negative Slope of line 1
	double l1IPStep = -1.0f / l1DeltaY;        // The Step for interpolation in line 1

	double l2DeltaX = C->x - A->x;
	double l2m = l2DeltaX / l1DeltaY;          // The Negative Slope of line 2

	double izStep = (B->z - A->z) / l1DeltaY;  // The Step for Z-Buffer in line 1
	double jzStep = (C->z - A->z) / l1DeltaY;  // The Step for Z-Buffer in line 2

	double i = A->x;
	double j = A->x;
	double iz = A->z;
	double jz = A->z;
	double a = 1.0f;

	/* Draw Flat Bottom Triangle */
	for (int yHat = A->y; yHat <= B->y; yHat++) {
		FBDrawHLine(
			fb, zb, yHat, (int)i, (int)j, iz, jz,
			cfun, tris, vodr, w, a
		);
		i += l1m;
		j += l2m;
		iz += izStep;
		jz += jzStep;
		a += l1IPStep;
	}
}


///*
//** Draw Whole Triangle
//*/
//
//void DrawTriangle(FrameBuffer fb, Vector4D* A, Vector4D* B, Vector4D* C, ColorFunction cfun) {
//	Vector4D* swap;
//	if ((A->y) > (B->y)) {
//		swap = A;
//		A = B;
//		B = swap;
//	}
//	if ((A->y) > (C->y)) {
//		swap = A;
//		A = C;
//		C = swap;
//	}
//	if ((B->y) > (C->y)) {
//		swap = B;
//		B = C;
//		C = swap;
//	}
//
//	double lsm = (C->x - A->x) / (C->y - A->y);
//	Vector4D D = CreateVector4D(A->x + lsm * (B->y - A->y), B->y, 1, 1);
//	double lsIPStep = -1 / (C->y - A->y);
//	double w = 1 + lsIPStep * (B->y - A->y);
//	TriangleSide tris;
//
//	if (((B->x) < (A->x)) && ((B->x) < (C->x))) {
//		tris = LONGSIDE_RIGHT;
//		DrawFlatBottomTriangle(fb, A->x, A->y, B->x, D.x, B->y, tris, cfun, w);
//		DrawFlatToppedTriangle(fb, B->x, D.x, B->y, C->x, C->y, tris, cfun, w);
//	}
//	else {
//		tris = LONGSIDE_LEFT;
//		DrawFlatBottomTriangle(fb, A->x, A->y, D.x, B->x, B->y, tris, cfun, w);
//		DrawFlatToppedTriangle(fb, D.x, B->x, B->y, C->x, C->y, tris, cfun, w);
//	}
//}

#endif
