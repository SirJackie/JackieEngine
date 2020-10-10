/*
** This is a Demo of CrossBuffer
** You can change everything if you like
*/
#pragma once
#include "CrossBuffer.h"
#include "TextOutput.h"
#include "Input.h"

/* Background Color Transform Variables */
int   Color = 0;
float DeltaColor = 0.1;

/* FPS Counting Variables */
float FPS = 0;
int   deltaTimeCount;
int   frameCount;

/* Temp Variables */
int RedCubeX = 100;
int RedCubeY = 100;


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
		DeltaColor = -0.1;
	}

	else if (Color <= 5) {
		DeltaColor = 0.1;
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
		"LButtonState: %d\nRButtonState: %d\nMouseX: %d\nMouseY: %d\nMouseLastX: %d\nMouseLastY: %d\nMouseDeltaX: %f\nMouseDeltaY: %f",
		mouse.LButtonState,
		mouse.RButtonState,
		mouse.X,
		mouse.Y,
		mouse.LastX,
		mouse.LastY,
		mouse.DeltaX,
		mouse.DeltaY
	);
	DrawShadowString(fb, 10, 30, buffer);
}

void OnDestroy() {
	;
}
