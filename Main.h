#include <stdio.h>
#include <math.h>
#include "./CrossBufferLayer/CrossBuffer.h"
#include "./JackieEngineLayer/JackieEngine.h"

/* Define Window Class Properties */
#define WindowClassName L"Jackie Engine Class"
#define WindowTitle     L"Jackie Engine"

#define TriangleSide int
#define LONGSIDE_RIGHT 0
#define LONGSIDE_LEFT  1

typedef Color(*ColorFunction) (double, double, double);

Color realCfun(double r, double s, double t) {
	return CreateColor(
		(int)(255 * r),
		(int)(255 * s),
		(int)(255 * t)
	);
}

ColorFunction cfun = realCfun;

double expo1, expo2, expo3, expo4, expo5;


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

void Setup(FrameBuffer fb, Keyboard kb, int deltaTime) {
	;
}


int x1 = 0;
int x2 = 1000;
int yStart = 100;
int x0 = 500;
int yEnd = 500;

void Update(FrameBuffer fb, Keyboard kb, int deltaTime) {
	DrawFlatToppedTriangle(fb, x1, x2, yStart, x0, yEnd, LONGSIDE_RIGHT, cfun, 0.0f);

	if (kb['W']) {
		yStart -= 3;
	}
	if (kb['S']) {
		yStart += 3;
	}
	if (kb['A']) {
		x1 -= 3;
	}
	if (kb['D']) {
		x1 += 3;
	}

	if (kb['Z']) {
		x2 -= 3;
	}
	if (kb['X']) {
		x2 += 3;
	}

	if (kb['I']) {
		yEnd -= 3;
	}
	if (kb['K']) {
		yEnd += 3;
	}

	if (kb['J']) {
		x0 -= 3;
	}
	if (kb['L']) {
		x0 += 3;
	}

	CalcFPS(fb, deltaTime);
	char buffer[1000];
	sprintf_s(buffer, 1000, "Expose: %f; %f; %f; %f; %f", expo1, expo2, expo3, expo4, expo5);
	DrawShadowString(fb, 10, 36, buffer);
}

///*
//** Global Variables
//*/
//
//Camera4D  cam;
//Vector4D  vecs[8];
//Matrix4D  Mrotation;
//char*     buffer;
//char      realbuffer[1000];
//float     keyboardSensitivity  = 0.005f;
//BOOL      rotateOrNot          = TRUE;
//float     rotateDegree         = 0.0f;
//int       rotateKeyDelay       = 0;
//
//
///*
//** Setup()
//*/
//
//void Setup(FrameBuffer fb, Keyboard kb, int deltaTime) {
//	
//	
//	/*
//	** Camera
//	*/
//
//	cam = CreateCamera4D(
//		0.0f, 0.0f, 7.0f, 0.0f, 0.0f, 0.0f,
//		-0.1f, -1000.0f, 60.0f, fb.Width, fb.Height
//	);
//	CalcCamera4DMatrices(&cam);
//
//
//	/*
//	** Vectors
//	*/
//
//	vecs[0] = CreateVector4D(-1.0f, -1.0f,  1.0f, 1.0f);
//	vecs[1] = CreateVector4D( 1.0f, -1.0f,  1.0f, 1.0f);
//	vecs[2] = CreateVector4D( 1.0f,  1.0f,  1.0f, 1.0f);
//	vecs[3] = CreateVector4D(-1.0f,  1.0f,  1.0f, 1.0f);
//	vecs[4] = CreateVector4D(-1.0f, -1.0f, -1.0f, 1.0f);
//	vecs[5] = CreateVector4D( 1.0f, -1.0f, -1.0f, 1.0f);
//	vecs[6] = CreateVector4D( 1.0f,  1.0f, -1.0f, 1.0f);
//	vecs[7] = CreateVector4D(-1.0f,  1.0f, -1.0f, 1.0f);
//}
//
//
///*
//** Update()
//*/
//
//void Update(FrameBuffer fb, Keyboard kb, int deltaTime) {
//	
//
//	/*
//	** Calculating FPS
//	*/
//
//	CalcFPS(fb, deltaTime);
//
//
//	/*
//	** Position Responder
//	*/
//
//	if (kb['W'] == TRUE) {
//		cam.position.z -= 1.0f * keyboardSensitivity * deltaTime;
//	}
//	if (kb['S'] == TRUE) {
//		cam.position.z += 1.0f * keyboardSensitivity * deltaTime;
//	}
//
//	if (kb['A'] == TRUE) {
//		cam.position.x -= 0.5f * keyboardSensitivity * deltaTime;
//	}
//	if (kb['D'] == TRUE) {
//		cam.position.x += 0.5f * keyboardSensitivity * deltaTime;
//	}
//
//	if (kb['E'] == TRUE) {
//		cam.position.y -= 0.5f * keyboardSensitivity * deltaTime;
//	}
//	if (kb['Q'] == TRUE) {
//		cam.position.y += 0.5f * keyboardSensitivity * deltaTime;
//	}
//
//
//	/*
//	** Rotation Responder
//	*/
//
//	if (kb['I'] == TRUE) {
//		cam.rotation.x -= 5.0f * keyboardSensitivity * deltaTime;
//	}
//	if (kb['K'] == TRUE) {
//		cam.rotation.x += 5.0f * keyboardSensitivity * deltaTime;
//	}
//
//	if (kb['J'] == TRUE) {
//		cam.rotation.y -= 5.0f * keyboardSensitivity * deltaTime;
//	}
//	if (kb['L'] == TRUE) {
//		cam.rotation.y += 5.0f * keyboardSensitivity * deltaTime;
//	}
//
//	if (kb['U'] == TRUE) {
//		cam.rotation.z -= 5.0f * keyboardSensitivity * deltaTime;
//	}
//	if (kb['O'] == TRUE) {
//		cam.rotation.z += 5.0f * keyboardSensitivity * deltaTime;
//	}
//
//
//	/*
//	** R Key Responder
//	*/
//
//	if (kb['R'] == TRUE && rotateKeyDelay == 0) {
//		rotateOrNot = !(rotateOrNot);
//		rotateKeyDelay = 10;
//	}
//
//	if (rotateKeyDelay > 0) {
//		rotateKeyDelay -= 1;
//	}
//
//
//	/*
//	** Refresh Camera Matrices
//	*/
//
//	RefreshCamera4DMatrices(&cam);
//
//
//	/*
//	** Rotate the Vectors
//	*/
//
//	Mrotation = CreateRotationMatrix(rotateDegree, -30.0f, rotateDegree);
//
//	if (rotateOrNot == TRUE) {
//		rotateDegree += 0.03f * deltaTime;
//	}
//	if (rotateDegree >= 360.0f) {
//		rotateDegree =  0.0f;
//	}
//
//	for (int i = 0; i < 8; i++) {
//		vecs[i] = Vector4DTimesMatrix4D(
//			&(vecs[i]), &(Mrotation)
//		);
//	}
//
//
//	/*
//	** Do Projection
//	*/
//
//	for (int i = 0; i < 8; i++) {
//		vecs[i] = Vector4DTimesMatrix4D(
//			&(vecs[i]), &(cam.Mtransform)
//		);
//	}
//
//	for (int i = 0; i < 8; i++) {
//		Vector4DDevidedByW(&(vecs[i]));
//	}
//
//
//	/*
//	** Output Things
//	*/
//
//	// Camera Frustum
//	sprintf_s(
//		realbuffer, 1000,
//		"n:%f\nf:%f\nt:%f\nb:%f\nl:%f\nr:%f\n",
//		cam.n, cam.f, cam.t, cam.b, cam.l, cam.r
//	);
//	DrawShadowString(fb, 10, 42, realbuffer);
//
//	// Camera Position
//	buffer = OutputVector4D(&(cam.position));
//	DrawShadowString(fb, 10, 314, buffer);
//	free(buffer);
//
//	// Camera Rotation
//	buffer = OutputVector4D(&(cam.rotation));
//	DrawShadowString(fb, 10, 346, buffer);
//	free(buffer);
//
//	// Mtransform
//	buffer = OutputMatrix4D(&(cam.Mtransform));
//	DrawShadowString(fb, 10, 378, buffer);
//	free(buffer);
//
//	// Vector List
//	for (int i = 0; i < 8; i++) {
//		buffer = OutputVector4D(&(vecs[i]));
//		DrawShadowString(fb, 10, 154 + i * 16, buffer);
//		free(buffer);
//	}
//
//
//	/*
//	** Get And Clear Z-Buffer
//	*/
//
//	float* ZBuffer = (float*)malloc(sizeof(float) * fb.Width * fb.Height);
//	for (int y = 0; y < fb.Height; y++) {
//		for (int x = 0; x < fb.Width; x++) {
//			ZBuffer[y * fb.Width + x] = cam.f;
//		}
//	}
//
//
//	/*
//	** Do Rasterization
//	*/
//
//	DrawFlatMesh4D(fb, &(vecs[0]), &(vecs[1]), &(vecs[3]), CreateColor(255, 0, 255, 255), ZBuffer);
//	DrawFlatMesh4D(fb, &(vecs[2]), &(vecs[3]), &(vecs[1]), CreateColor(255, 255, 0, 255), ZBuffer);
//	DrawFlatMesh4D(fb, &(vecs[5]), &(vecs[4]), &(vecs[6]), CreateColor(255, 255, 255, 255), ZBuffer);
//	DrawFlatMesh4D(fb, &(vecs[7]), &(vecs[6]), &(vecs[4]), CreateColor(255, 255, 255, 255), ZBuffer);
//	DrawFlatMesh4D(fb, &(vecs[4]), &(vecs[0]), &(vecs[7]), CreateColor(255, 255, 255, 255), ZBuffer);
//	DrawFlatMesh4D(fb, &(vecs[3]), &(vecs[7]), &(vecs[0]), CreateColor(255, 255, 255, 255), ZBuffer);
//	//DrawFlatMesh4D(fb, &(vecs[1]), &(vecs[5]), &(vecs[2]), CreateColor(255, 255, 255, 255), ZBuffer);
//	//DrawFlatMesh4D(fb, &(vecs[6]), &(vecs[2]), &(vecs[5]), CreateColor(255, 255, 255, 255), ZBuffer);
//	//DrawFlatMesh4D(fb, &(vecs[3]), &(vecs[2]), &(vecs[7]), CreateColor(255, 255, 255, 255), ZBuffer);
//	//DrawFlatMesh4D(fb, &(vecs[6]), &(vecs[7]), &(vecs[2]), CreateColor(255, 255, 255, 255), ZBuffer);
//	//DrawFlatMesh4D(fb, &(vecs[5]), &(vecs[0]), &(vecs[4]), CreateColor(255, 255, 255, 255), ZBuffer);
//	//DrawFlatMesh4D(fb, &(vecs[5]), &(vecs[1]), &(vecs[0]), CreateColor(255, 255, 255, 255), ZBuffer);
//
//
//	/*
//	** Reset Vectors
//	*/
//
//	vecs[0] = CreateVector4D(-1.0f, -1.0f,  1.0f, 1.0f);
//	vecs[1] = CreateVector4D( 1.0f, -1.0f,  1.0f, 1.0f);
//	vecs[2] = CreateVector4D( 1.0f,  1.0f,  1.0f, 1.0f);
//	vecs[3] = CreateVector4D(-1.0f,  1.0f,  1.0f, 1.0f);
//	vecs[4] = CreateVector4D(-1.0f, -1.0f, -1.0f, 1.0f);
//	vecs[5] = CreateVector4D( 1.0f, -1.0f, -1.0f, 1.0f);
//	vecs[6] = CreateVector4D( 1.0f,  1.0f, -1.0f, 1.0f);
//	vecs[7] = CreateVector4D(-1.0f,  1.0f, -1.0f, 1.0f);
//
//
//	/*
//	** Delete Z-Buffer
//	*/
//
//	free(ZBuffer);
//}
