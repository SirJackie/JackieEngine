#include <stdio.h>
#include <math.h>
#include "./CrossBufferLayer/CrossBuffer.h"
#include "./JackieEngineLayer/JackieEngine.h"

/* Define Window Class Properties */
#define WindowClassName L"Jackie Engine Class"
#define WindowTitle     L"Jackie Engine"


/*
** Global Variables
*/

Camera4D  cam;
Vector4D  vecs[8];
Matrix4D  Mrotation;
char*     buffer;
char      realbuffer[1000];
double    keyboardSensitivity  = 0.005f;
BOOL      rotateOrNot          = TRUE;
double    rotateDegree         = 0.0;
int       rotateKeyDelay       = 0;
ZBuffer zb;


/*
** Color Function
*/

Color cfun(double r, double s, double t) {
	return CreateColor(
		(int)(255 * r),
		(int)(255 * s),
		(int)(255 * t)
	);
}


/*
** Setup()
*/

void Setup(FrameBuffer fb, Keyboard kb, int deltaTime) {
	zb = CreateZBuffer(fb);
	
	/*
	** Camera
	*/

	cam = CreateCamera4D(
		0.0, 0.0, 4.0, 0.0, 0.0, 0.0,
		-0.1f, -1000.0, 60.0, fb.Width, fb.Height
	);
	CalcCamera4DMatrices(&cam);


	/*
	** Vectors
	*/

	vecs[0] = CreateVector4D(-1.0, -1.0,  1.0, 1.0);
	vecs[1] = CreateVector4D( 1.0, -1.0,  1.0, 1.0);
	vecs[2] = CreateVector4D( 1.0,  1.0,  1.0, 1.0);
	vecs[3] = CreateVector4D(-1.0,  1.0,  1.0, 1.0);
	vecs[4] = CreateVector4D(-1.0, -1.0, -1.0, 1.0);
	vecs[5] = CreateVector4D( 1.0, -1.0, -1.0, 1.0);
	vecs[6] = CreateVector4D( 1.0,  1.0, -1.0, 1.0);
	vecs[7] = CreateVector4D(-1.0,  1.0, -1.0, 1.0);
}


/*
** Update()
*/

void Update(FrameBuffer fb, Keyboard kb, int deltaTime) {
	

	/*
	** Calculating FPS
	*/

	CalcFPS(fb, deltaTime);


	/*
	** Position Responder
	*/

	if (kb['W'] == TRUE) {
		cam.position.z -= 1.0 * keyboardSensitivity * deltaTime;
	}
	if (kb['S'] == TRUE) {
		cam.position.z += 1.0 * keyboardSensitivity * deltaTime;
	}

	if (kb['A'] == TRUE) {
		cam.position.x -= 0.5f * keyboardSensitivity * deltaTime;
	}
	if (kb['D'] == TRUE) {
		cam.position.x += 0.5f * keyboardSensitivity * deltaTime;
	}

	if (kb['E'] == TRUE) {
		cam.position.y -= 0.5f * keyboardSensitivity * deltaTime;
	}
	if (kb['Q'] == TRUE) {
		cam.position.y += 0.5f * keyboardSensitivity * deltaTime;
	}


	/*
	** Rotation Responder
	*/

	if (kb['I'] == TRUE) {
		cam.rotation.x -= 5.0 * keyboardSensitivity * deltaTime;
	}
	if (kb['K'] == TRUE) {
		cam.rotation.x += 5.0 * keyboardSensitivity * deltaTime;
	}

	if (kb['J'] == TRUE) {
		cam.rotation.y -= 5.0 * keyboardSensitivity * deltaTime;
	}
	if (kb['L'] == TRUE) {
		cam.rotation.y += 5.0 * keyboardSensitivity * deltaTime;
	}

	if (kb['U'] == TRUE) {
		cam.rotation.z -= 5.0 * keyboardSensitivity * deltaTime;
	}
	if (kb['O'] == TRUE) {
		cam.rotation.z += 5.0 * keyboardSensitivity * deltaTime;
	}


	/*
	** R Key Responder
	*/

	if (kb['R'] == TRUE && rotateKeyDelay == 0) {
		rotateOrNot = !(rotateOrNot);
		rotateKeyDelay = 10;
	}

	if (rotateKeyDelay > 0) {
		rotateKeyDelay -= 1;
	}


	/*
	** Refresh Camera Matrices
	*/

	RefreshCamera4DMatrices(&cam);


	/*
	** Rotate the Vectors
	*/

	Mrotation = CreateRotationMatrix(rotateDegree, -30.0, rotateDegree);

	if (rotateOrNot == TRUE) {
		rotateDegree += (double)0.03 * (double)deltaTime;
	}
	if (rotateDegree >= 360.0) {
		rotateDegree =  0.0;
	}

	for (int i = 0; i < 8; i++) {
		vecs[i] = Vector4DTimesMatrix4D(
			&(vecs[i]), &(Mrotation)
		);
	}


	/*
	** Do Projection
	*/

	for (int i = 0; i < 8; i++) {
		vecs[i] = Vector4DTimesMatrix4D(
			&(vecs[i]), &(cam.Mtransform)
		);
	}

	for (int i = 0; i < 8; i++) {
		Vector4DDevidedByW(&(vecs[i]));
	}


	/*
	** Output Things
	*/

	// Camera Frustum
	sprintf_s(
		realbuffer, 1000,
		"n:%lf\nf:%lf\nt:%lf\nb:%lf\nl:%lf\nr:%lf\n",
		cam.n, cam.f, cam.t, cam.b, cam.l, cam.r
	);
	DrawShadowString(fb, 10, 42, realbuffer);

	// Camera Position
	buffer = OutputVector4D(&(cam.position));
	DrawShadowString(fb, 10, 314, buffer);
	free(buffer);

	// Camera Rotation
	buffer = OutputVector4D(&(cam.rotation));
	DrawShadowString(fb, 10, 346, buffer);
	free(buffer);

	// Mtransform
	buffer = OutputMatrix4D(&(cam.Mtransform));
	DrawShadowString(fb, 10, 378, buffer);
	free(buffer);

	sprintf_s(realbuffer, 1000, "Rotate Degree: %lf", rotateDegree);
	DrawShadowString(fb, 10, 458, realbuffer);

	// Vector List
	for (int i = 0; i < 8; i++) {
		buffer = OutputVector4D(&(vecs[i]));
		DrawShadowString(fb, 10, 154 + i * 16, buffer);
		free(buffer);
	}


	/*
	** Get And Clear Z-Buffer
	*/
	ClearZBuffer(fb, zb, -1.0);


	/*
	** Do Rasterization
	*/

	DrawTriangle(fb, zb, &(vecs[0]), &(vecs[1]), &(vecs[3]), cfun);  //n1
	DrawTriangle(fb, zb, &(vecs[2]), &(vecs[3]), &(vecs[1]), cfun);  //n2
	DrawTriangle(fb, zb, &(vecs[5]), &(vecs[4]), &(vecs[6]), cfun);  //f1
	DrawTriangle(fb, zb, &(vecs[7]), &(vecs[6]), &(vecs[4]), cfun);  //f2
	DrawTriangle(fb, zb, &(vecs[4]), &(vecs[0]), &(vecs[7]), cfun);  //l1
	DrawTriangle(fb, zb, &(vecs[3]), &(vecs[7]), &(vecs[0]), cfun);  //l2
	DrawTriangle(fb, zb, &(vecs[1]), &(vecs[5]), &(vecs[2]), cfun);  //r1
	DrawTriangle(fb, zb, &(vecs[6]), &(vecs[2]), &(vecs[5]), cfun);  //r2
	DrawTriangle(fb, zb, &(vecs[3]), &(vecs[2]), &(vecs[7]), cfun);  //t1
	DrawTriangle(fb, zb, &(vecs[6]), &(vecs[7]), &(vecs[2]), cfun);  //t2
	DrawTriangle(fb, zb, &(vecs[5]), &(vecs[0]), &(vecs[4]), cfun);  //b1
	DrawTriangle(fb, zb, &(vecs[5]), &(vecs[1]), &(vecs[0]), cfun);  //b2


	/*
	** Reset Vectors
	*/

	vecs[0] = CreateVector4D(-1.0, -1.0,  1.0, 1.0);
	vecs[1] = CreateVector4D( 1.0, -1.0,  1.0, 1.0);
	vecs[2] = CreateVector4D( 1.0,  1.0,  1.0, 1.0);
	vecs[3] = CreateVector4D(-1.0,  1.0,  1.0, 1.0);
	vecs[4] = CreateVector4D(-1.0, -1.0, -1.0, 1.0);
	vecs[5] = CreateVector4D( 1.0, -1.0, -1.0, 1.0);
	vecs[6] = CreateVector4D( 1.0,  1.0, -1.0, 1.0);
	vecs[7] = CreateVector4D(-1.0,  1.0, -1.0, 1.0);
}
