#ifndef __STDIO_H__
#define __STDIO_H__
#include <stdio.h>
#endif

#ifndef __MATH_H__
#define __MATH_H__
#include <math.h>
#endif

#ifndef __LINEAR_ALGEBRA_H__
#define __LINEAR_ALGEBRA_H__
#include "LinearAlgebra.h"
#endif

#ifndef __CAMERA_SUPPORT_H__
#define __CAMERA_SUPPORT_H__
#include "CameraSupport.h"
#endif

#ifndef __MODEL_SUPPORT_H__
#define __MODEL_SUPPORT_H__
#include "ModelSupport.h"
#endif

#ifndef __CROSSBUFFER_H__
#define __CROSSBUFFER_H__
#include "CrossBuffer.h"
#endif


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

void DrawFlatMesh4D(FrameBuffer fb, int width, int height,
	Vector4D* v0, Vector4D* v1, Vector4D* v2, Color color, float* ZBuffer
)
{


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

	StartX     = clamp(0, StartX, width );
	StartY     = clamp(0, StartY, height);
	EndX       = clamp(0, EndX,   width );
	EndY       = clamp(0, EndY,   height);


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
