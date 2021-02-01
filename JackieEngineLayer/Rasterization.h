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

void DrawVector4D(FrameBuffer fb, int width, int height, Vector4D* vec, int radius) {
	int CentralX = (int)vec->x;
	int CentralY = (int)vec->y;
	int StartX = clamp(0, CentralX - radius, width);
	int EndX = clamp(0, CentralX + radius, width);
	int StartY = clamp(0, CentralY - radius, height);
	int EndY = clamp(0, CentralY + radius, height);

	for (int y = StartY; y < EndY; y++) {
		for (int x = StartX; x < EndX; x++) {
			SetPixelLB(fb, height, x, y, CreateColor(255, 255, 255, 255));
		}
	}
}


/*
** Drawing Functions for FlatMesh4D
*/

void DrawFlatMesh4D(FrameBuffer fb, 
	Vector4D* v0, Vector4D* v1, Vector4D* v2, Color color, float* ZBuffer
)
{
	int width = fb.Width;
	int height = fb.Height;

	/*
	** Calculate Planar Equation For Z-Buffer
	*/

	Vector4D v0v1 = CreateVector4DFromPointToPoint(v0, v1);
	Vector4D v0v2 = CreateVector4DFromPointToPoint(v0, v2);
	Vector4D v1v2 = CreateVector4DFromPointToPoint(v1, v2);
	Vector4D v2v0 = CreateVector4DFromPointToPoint(v2, v0);
	Vector4D v0v1crossv0v2 = Vector4DCrossVector4D(&v0v1, &v0v2);

	float A = v0v1crossv0v2.x;
	float B = v0v1crossv0v2.y;
	float C = v0v1crossv0v2.z;
	float D = -1.0f * (A * v0->x + B * v0->y + C * v0->z);



	/*
	** Calculate Bounding Box
	*/

	int StartX = min3(v0->x, v1->x, v2->x);
	int StartY = min3(v0->y, v1->y, v2->y);
	int EndX   = max3(v0->x, v1->x, v2->x);
	int EndY   = max3(v0->y, v1->y, v2->y);

	StartX     = clamp(0, StartX, width  - 1);
	StartY     = clamp(0, StartY, height - 1);
	EndX       = clamp(0, EndX,   width  - 1);
	EndY       = clamp(0, EndY,   height - 1);

	// Caution : Width and Height are already -1 when they were given
	//           -1 here is to prevent the overflow caused by
	//           y <= EndY and x <= EndX below

	// Tip     : y <= EndY and x <= EndX below is to fix the gaps
	//           between two triangles when Rasterize


	/*
	** Pre-Getting Vectors' x, y to speed up (avoid memory-address finding)
	*/

	float v0x = v0->x;
	float v0y = v0->y;
	float v1x = v1->x;
	float v1y = v1->y;
	float v2x = v2->x;
	float v2y = v2->y;

	float v1v2x = v1v2.x;
	float v1v2y = v1v2.y;
	float v0v1x = v0v1.x;
	float v0v1y = v0v1.y;
	float v2v0x = v2v0.x;
	float v2v0y = v2v0.y;


	/*
	** Declaration Of Temporal Variables
	*/

	float v1px;
	float v1py;
	float v0px;
	float v0py;
	float v2px;
	float v2py;

	float zresult1;
	float zresult2;
	float zresult3;

	float Zp;         // Z Value of the current pixel
	float ctmp;       // Color Temp for the current pixel


	/*
	** Rasterize
	*/

	for (int y = StartY; y <= EndY; y++)
	{
		for (int x = StartX; x <= EndX; x++)
		{

			//v1p = CreateVector4DFromPointToPoint(v1, &p);
			v1px = v1x - x;
			v1py = v1y - y;
			//v0p = CreateVector4DFromPointToPoint(v0, &p);
			v0px = v0x - x;
			v0py = v0y - y;
			//v2p = CreateVector4DFromPointToPoint(v2, &p);
			v2px = v2x - x;
			v2py = v2y - y;

			//zresult1 = Vector4DCrossVector4D(&v1v2, &v1p);
			zresult1 = v1v2x * v1py - v1v2y * v1px;
			//zresult2 = Vector4DCrossVector4D(&v0v1, &v0p);
			zresult2 = v0v1x * v0py - v0v1y * v0px;
			//zresult3 = Vector4DCrossVector4D(&v2v0, &v2p);
			zresult3 = v2v0x * v2py - v2v0y * v2px;


			/*
			** If the current pixel is inside the triangle
			*/

			if (zresult1 > 0 && zresult2 > 0 && zresult3 > 0 ||
				zresult1 < 0 && zresult2 < 0 && zresult3 < 0)
			{


				/*
				** Calculate Z Value
				*/

				Zp = (-1.0f * A * x - B * y - D) / C;


				/*
				** If the Z Value is bigger than the value in Z-Buffer
				*/

				if (Zp > ZBuffer[y * width + x]) {
					


					/*
					** Cover the value in Z-Buffer with Z Value
					*/

					ZBuffer[y * width + x] = Zp;
					

					/*
					** Calculate Color With Z Value
					*/

					float ctmp = 1.0f - ((fabs(Zp) - 0.96f) * 50.0f);
					ctmp = fclamp(0.1f, ctmp, 1.0f);


					/*
					** Draw the current pixel
					*/

					int rtmp = GetColorR(color);
					int gtmp = GetColorG(color);
					int btmp = GetColorB(color);

					SetPixelLB(fb, height, x, y, CreateColor((int)(rtmp * ctmp), (int)(gtmp * ctmp), (int)(btmp * ctmp), 255));
				}
			}
		}
	}
}


/*
** Scan-Line Rasterization
**/

#define TriangleSide int
#define LONGSIDE_RIGHT 0
#define LONGSIDE_LEFT  1

typedef Color(*ColorFunction) (double, double, double);

/*
** Flat Bottom Triangle Drawing Functions
*/

void FBDrawColorPixel(FrameBuffer fb, int x, int y, double r, double s, double t, TriangleSide tris, ColorFunction cfun, double w) {
	if (tris == LONGSIDE_RIGHT) {
		SetPixel(fb, x, y, cfun(r + t * w, s, t - t * w));
	}
	else {
		SetPixel(fb, x, y, cfun(r + s * w, t, s - s * w));
	}
}

void FBDrawHLine(FrameBuffer fb, int y, int x0, int x1, double a, TriangleSide tris, ColorFunction cfun, double w) {
	int llen = x1 - x0;
	double lIPStep = -1.0f / llen;
	double b = 1;

	for (int xHat = x0; xHat < x1; xHat++) {
		FBDrawColorPixel(fb, xHat, y, a, b - a * b, a * b - a - b + 1, tris, cfun, w);
		b += lIPStep;
	}
}

void DrawFlatBottomTriangle(FrameBuffer fb, int x0, int yStart, int x1, int x2, int yEnd, TriangleSide tris, ColorFunction cfun, double w) {
	double l1DeltaX = x1 - x0;
	double l1DeltaY = yEnd - yStart;
	double l1m = l1DeltaX / l1DeltaY;  // The Negative Slope of line 1
	double l1len = sqrt(l1DeltaX * l1DeltaX + l1DeltaY * l1DeltaY);  // The Length of line 1
	double l1IPStep = -1.0f / l1DeltaY;

	double l2DeltaX = x2 - x0;
	double l2DeltaY = l1DeltaY;
	double l2m = l2DeltaX / l2DeltaY;  // The Negative Slope of line 1

	double i = 1.0f * x0;
	double j = 1.0f * x0;
	double a = 1.0f;

	for (int yHat = yStart; yHat <= yEnd; yHat++) {
		FBDrawHLine(fb, yHat, (int)i, (int)j, a, tris, cfun, w);
		i += l1m;
		j += l2m;
		a += l1IPStep;
	}
}


/*
** Flat Topped Triangle Drawing Functions
*/

void FTDrawColorPixel(FrameBuffer fb, int x, int y, double r, double s, double t, TriangleSide tris, ColorFunction cfun, double w) {
	if (tris == LONGSIDE_RIGHT) {
		SetPixel(fb, x, y, cfun(s * w, r, s - s * w + t));
	}
	else {
		SetPixel(fb, x, y, cfun(r * w, s, r - r * w + t));
	}
}

void FTDrawHLine(FrameBuffer fb, int y, int x0, int x1, double a, TriangleSide tris, ColorFunction cfun, double w) {
	int llen = x1 - x0;
	double lIPStep = -1.0f / llen;
	double b = 1;

	for (int xHat = x0; xHat < x1; xHat++) {
		FTDrawColorPixel(fb, xHat, y, a * b, a - a * b, 1 - a, tris, cfun, w);
		b += lIPStep;
	}
}

void DrawFlatToppedTriangle(FrameBuffer fb, int x1, int x2, int yStart, int x0, int yEnd, TriangleSide tris, ColorFunction cfun, double w) {
	double l1DeltaX = x0 - x1;
	double l1DeltaY = yEnd - yStart;
	double l1m = l1DeltaX / l1DeltaY;  // The Negative Slope of line 1
	double l1IPStep = -1.0f / l1DeltaY;

	double l2DeltaX = x0 - x2;
	double l2DeltaY = l1DeltaY;
	double l2m = l2DeltaX / l2DeltaY;  // The Negative Slope of line 1

	double i = 1.0f * x1;
	double j = 1.0f * x2;
	double a = 1.0f;

	for (int yHat = yStart; yHat <= yEnd; yHat++) {
		FTDrawHLine(fb, yHat, (int)i, (int)j, a, tris, cfun, w);
		i += l1m;
		j += l2m;
		a += l1IPStep;
	}
}


/*
** Draw Whole Triangle
*/

void DrawTriangle(FrameBuffer fb, Vector4D* A, Vector4D* B, Vector4D* C, ColorFunction cfun) {
	Vector4D* swap;
	if ((A->y) > (B->y)) {
		swap = A;
		A = B;
		B = swap;
	}
	if ((A->y) > (C->y)) {
		swap = A;
		A = C;
		C = swap;
	}
	if ((B->y) > (C->y)) {
		swap = B;
		B = C;
		C = swap;
	}

	double lsm = (C->x - A->x) / (C->y - A->y);
	Vector4D D = CreateVector4D(A->x + lsm * (B->y - A->y), B->y, 1, 1);
	double lsIPStep = -1 / (C->y - A->y);
	double w = 1 + lsIPStep * (B->y - A->y);
	TriangleSide tris;

	if (((B->x) < (A->x)) && ((B->x) < (C->x))) {
		tris = LONGSIDE_RIGHT;
		DrawFlatBottomTriangle(fb, A->x, A->y, B->x, D.x, B->y, tris, cfun, w);
		DrawFlatToppedTriangle(fb, B->x, D.x, B->y, C->x, C->y, tris, cfun, w);
	}
	else {
		tris = LONGSIDE_LEFT;
		DrawFlatBottomTriangle(fb, A->x, A->y, D.x, B->x, B->y, tris, cfun, w);
		DrawFlatToppedTriangle(fb, D.x, B->x, B->y, C->x, C->y, tris, cfun, w);
	}
}

#endif
