/*
** This is a Demo of CrossBuffer
** You can change everything if you like
*/

#ifndef __CROSSBUFFER_H__
#define __CROSSBUFFER_H__
#include "CrossBuffer.h"
#endif

#ifndef __TEXTOUTPUT_H__
#define __TEXTOUTPUT_H__
#include "TextOutput.h"
#endif

#ifndef __INPUT_H__
#define __INPUT_H__
#include "Input.h"
#endif

/* Background Color Transform Variables */
int   Color = 0;
float DeltaColor = 0.1f;

/* FPS Counting Variables */
float FPS = 0;
int   deltaTimeCount;
int   frameCount;

/* Temp Variables */
int RedCubeX = 100;
int RedCubeY = 100;

int GreenCubeX;
int GreenCubeY;

/* Mouse Sensitivity */
float MouseSensitivity = 650.0f;


/*
** On Create Callback Function
*/
void OnCreate() {
	;
}


/*
** Setup Callback Function
*/
void Setup(FrameBuffer fb, int width, int height, int deltaTime, Keyboard keyboard, Mouse mouse) {
	GreenCubeX = mouse.RealX;
	GreenCubeY = mouse.RealY;
	/* Fill Yellow On The Screen */
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			SetPixel(fb, x, y, RGB888(255, 255, 0));
		}
	}
}


/*
** Update Callback Function
*/
void Update(FrameBuffer fb, int width, int height, int deltaTime, Keyboard keyboard, Mouse mouse) {
	/*
	** Process Background
	*/

	/* Draw Background */
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			SetPixel(fb, x, y, RGB888(Color, Color, Color));
		}
	}

	/* Calculate The Color Of The Background In The Next Frame*/
	Color += (int)(DeltaColor * (float)deltaTime);

	if (Color >= 250) {
		DeltaColor = -0.1f;
	}

	else if (Color <= 5) {
		DeltaColor = 0.1f;
	}


	/*
	** Process Red Cube That Controlled By WASD
	*/

	/* Process Keyboard Input For Red Cube */
	if (keyboard['W'] == 1) {
		RedCubeY -= deltaTime / 2;
	}
	if (keyboard['S'] == 1) {
		RedCubeY += deltaTime / 2;
	}
	if (keyboard['A'] == 1) {
		RedCubeX -= deltaTime / 2;
	}
	if (keyboard['D'] == 1) {
		RedCubeX += deltaTime / 2;
	}

	/* Boundary Treatment For Red Cube */
	if (RedCubeX < 0) {
		RedCubeX = 0;
	}
	else if (RedCubeX > width - 100) {
		RedCubeX = width - 100;
	}

	if (RedCubeY < 0) {
		RedCubeY = 0;
	}
	else if (RedCubeY > height - 100) {
		RedCubeY = height - 100;
	}

	/* Draw Red Cube */
	for (int y = RedCubeY; y < RedCubeY + 100; y++) {
		for (int x = RedCubeX; x < RedCubeX + 100; x++) {
			SetPixel(fb, x, y, RGB888(255, 0, 0));
		}
	}


	/*
	** Process Green Cube That Controlled By Mouse
	*/

	/* Process Mouse Delta For Green Cube */
	GreenCubeX += MouseSensitivity * mouse.DeltaX;
	GreenCubeY += MouseSensitivity * mouse.DeltaY;

	/* Boundary Treatment For Green Cube */
	if (GreenCubeX < 0) {
		GreenCubeX = 0;
	}
	else if (GreenCubeX > width - 100) {
		GreenCubeX = width - 100;
	}

	if (GreenCubeY < 0) {
		GreenCubeY = 0;
	}
	else if (GreenCubeY > height - 100) {
		GreenCubeY = height - 100;
	}

	/* Draw Green Cube */
	for (int y = GreenCubeY; y < GreenCubeY + 100; y++) {
		for (int x = GreenCubeX; x < GreenCubeX + 100; x++) {
			SetPixel(fb, x, y, RGB888(mouse.LButtonState * 255, 255, mouse.RButtonState * 255));
		}
	}


	/*
	** FPS Processing
	*/

	/* Calculate FPS */
	deltaTimeCount += deltaTime;
	frameCount += 1;

	if (deltaTimeCount > 1000) {
		FPS = (float)frameCount / ((float)deltaTimeCount / 1000);
		deltaTimeCount -= 1000;
		frameCount = 0;
	}

	/* Show FPS On Screen */
	char buffer[1000];
	sprintf_s(
		buffer,
		"FPS: %f; DeltaTime: %d",
		FPS,
		deltaTime
	);
	DrawShadowString(fb, 10, 10, buffer);


	/*
	** Show Mouse Input On Screen
	*/
	sprintf_s(
		buffer,
		"WindowWidth:%d\nWindowHeight:%d\nMouseLButtonState: %d\nMouseRButtonState: %d\nMouseRealDeltaX: %d\nMouseRealDeltaY: %d\nMouseDeltaRatio: %d\nMouseDeltaX: %f\nMouseDeltaY: %f",
		width,
		height,
		mouse.LButtonState,
		mouse.RButtonState,
		mouse.RealDeltaX,
		mouse.RealDeltaY,
		mouse.DeltaRatio,
		mouse.DeltaX,
		mouse.DeltaY
	);
	DrawShadowString(fb, 10, 30, buffer);
}

void OnDestroy() {
	;
}
