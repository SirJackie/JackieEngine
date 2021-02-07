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

typedef double* ZBuffer;

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
	if (x > fb.Width - 1) return;
	if (x < 0) return;
	if (y > fb.Height - 1) return;
	if (y < 0) return;

	if (z > zb[y * fb.Width + x]) {
		zb[y * fb.Width + x] = z;              // Over Write Z-Buffer

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

		//SetPixel(fb, x, y, CreateColor(
		//	(int)(2560 * z),
		//	(int)(2560 * z),
		//	(int)(2560 * z)
		//));
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


/*
** Flat Topped Triangle Drawing Functions
*/

void FTDrawColorPixel(
	FrameBuffer fb, ZBuffer zb,
	int x, int y, double z,
	ColorFunction cfun, TriangleSide tris, VectorOrder vodr,
	double w, double a, double b
)
{
	if (x > fb.Width - 1) return;
	if (x < 0) return;
	if (y > fb.Height - 1) return;
	if (y < 0) return;

	if (z > zb[y * fb.Width + x]) {
		zb[y * fb.Width + x] = z;

		double r = a * b;                      // The Similarity between this pixel and A
		double s = a - a * b;                  // The Similarity between this pixel and B
		double t = 1 - a;                      // The Similarity between this pixel and C

		double glr, gls, glt;

		if (tris == LONGSIDE_RIGHT) {
			glr = s * w;
			gls = r;
			glt = s - s * w + t;
		}
		else {   // LONGSIDE_LEFT
			glr = r * w;
			gls = s;
			glt = r - r * w + t;
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

		//SetPixel(fb, x, y, CreateColor(
		//	(int)(2560 * z),
		//	(int)(2560 * z),
		//	(int)(2560 * z)
		//));
	}
}

void FTDrawHLine(
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
		FTDrawColorPixel(
			fb, zb,
			k, y, kz,
			cfun, tris, vodr,
			w, a, b
		);
		b += lIPStep;
		kz += kzStep;
	}
}

void DrawFlatToppedTriangle(
	FrameBuffer fb, ZBuffer zb,
	Vector4D* A, Vector4D* B, Vector4D* C,
	ColorFunction cfun, TriangleSide tris, VectorOrder vodr,
	double w
)
{
	double l1DeltaX = C->x - A->x;
	double l1DeltaY = C->y - A->y;

	double l1m = l1DeltaX / l1DeltaY;          // The Negative Slope of line 1
	double l1IPStep = -1.0f / l1DeltaY;        // The Step for interpolation in line 1

	double l2DeltaX = C->x - B->x;
	double l2m = l2DeltaX / l1DeltaY;          // The Negative Slope of line 2

	double izStep = (C->z - A->z) / l1DeltaY;  // The Step for Z-Buffer in line 1
	double jzStep = (C->z - B->z) / l1DeltaY;  // The Step for Z-Buffer in line 2

	double i = A->x;
	double j = B->x;
	double iz = A->z;
	double jz = B->z;
	double a = 1.0f;

	/* Draw Flat Bottom Triangle */
	for (int yHat = A->y; yHat <= C->y; yHat++) {
		FTDrawHLine(
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



/*
** Draw Whole Triangle
*/

void DrawTriangle(FrameBuffer fb, ZBuffer zb,
	Vector4D* A, Vector4D* B, Vector4D* C, ColorFunction cfun
)
{
	TriangleSide tris;
	VectorOrder  vodr;
	int vodrArr[3] = { 1, 2, 3 };

	Vector4D* swap;
	int swapi;
	if ((A->y) > (B->y)) {
		swap = A;
		A = B;
		B = swap;

		swapi = vodrArr[0];
		vodrArr[0] = vodrArr[1];
		vodrArr[1] = swapi;
	}
	if ((A->y) > (C->y)) {
		swap = A;
		A = C;
		C = swap;

		swapi = vodrArr[0];
		vodrArr[0] = vodrArr[2];
		vodrArr[2] = swapi;
	}
	if ((B->y) > (C->y)) {
		swap = B;
		B = C;
		C = swap;

		swapi = vodrArr[1];
		vodrArr[1] = vodrArr[2];
		vodrArr[2] = swapi;
	}

	vodr = vodrArr[0] * 100 + vodrArr[1] * 10 + vodrArr[2];

	double lsm = (C->x - A->x) / (C->y - A->y);
	double lsIPStep = -1 / (C->y - A->y);
	double w = 1 + lsIPStep * (B->y - A->y);
	Vector4D D = CreateVector4D(
		A->x + lsm * (B->y - A->y),
		B->y,
		w * A->z + (1 - w) * C->z,
		1
	);  // Calculate the value of D

	if (B->x < A->x && B->x < C->x) {
		tris = LONGSIDE_RIGHT;
	}
	else if (B->x > A->x && B->x > C->x) {
		tris = LONGSIDE_LEFT;
	}
	else {
		if (D.x > B->x) {
			tris = LONGSIDE_RIGHT;
		}
		else {  // D->x < B->x
			tris = LONGSIDE_LEFT;
		}
	}

	if (tris == LONGSIDE_RIGHT) {
		DrawFlatBottomTriangle(fb, zb, A, B, &D, cfun, tris, vodr, w);
		DrawFlatToppedTriangle(fb, zb, B, &D, C, cfun, tris, vodr, w);
	}
	else {   // LONGSIDE_LEFT
		DrawFlatBottomTriangle(fb, zb, A, &D, B, cfun, tris, vodr, w);
		DrawFlatToppedTriangle(fb, zb, &D, B, C, cfun, tris, vodr, w);
	}
}

ZBuffer CreateZBuffer(FrameBuffer fb) {
	return new double[fb.Width * fb.Height];
}

void ClearZBuffer(FrameBuffer fb, ZBuffer zb, double zbInitValue) {
	for (int i = 0; i < fb.Width * fb.Height; i++) {
		zb[i] = zbInitValue;
	}
}

#endif
