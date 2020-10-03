#pragma once

#include "CrossBuffer.h"
#include "TextOutput.h"

int Color = 0;
float DeltaColor = 0.1;

float FPS = 0;
int deltaTimeCount;
int frameCount;

void OnCreate() {
	;
}

void Setup(FrameBuffer fb, int width, int height) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Pixel(fb, x, y) = RGB888(255, 255, 0);
		}
	}
}

int BallX = 100;
int BallY = 100;

void Update(FrameBuffer fb, int width, int height, int deltaTime, BOOL IsKeyPressing, int KeyCode, BOOL IsMousePressing, int MouseX, int MouseY) {
	/*
	** Draw Things
	*/
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Pixel(fb, x, y) = RGB888(Color, Color, Color);
		}
	}

	if (IsKeyPressing == TRUE) {
		if (KeyCode == 'W') {
			BallY -= deltaTime / 2;
		}
		if (KeyCode == 'S') {
			BallY += deltaTime / 2;
		}
		if (KeyCode == 'A') {
			BallX -= deltaTime / 2;
		}
		if (KeyCode == 'D') {
			BallX += deltaTime / 2;
		}
	}

	if (BallX < 0) {
		BallX = 0;
	}
	else if (BallX > width - 100) {
		BallX = width - 100;
	}

	if (BallY < 0) {
		BallY = 0;
	}
	else if (BallY > height - 100) {
		BallY = height - 100;
	}

	for (int y = BallY; y < BallY + 100; y++) {
		for (int x = BallX; x < BallX + 100; x++) {
			Pixel(fb, x, y) = RGB888(255, 0, 0);
		}
	}


	/*
	** Calculate FPS
	*/
	deltaTimeCount += deltaTime;
	frameCount += 1;

	if (deltaTimeCount > 1000) {
		FPS = (float)frameCount / ((float)deltaTimeCount / 1000);
		deltaTimeCount -= 1000;
		frameCount = 0;
	}

	char buffer[100];
	sprintf_s(
		buffer,
		"FPS: %f; DeltaTime: %d",
		FPS,
		deltaTime
	);
	DrawShadowString(fb, 10, 10, buffer);

	sprintf_s(
		buffer,
		"IsKeyPressing: %d\nKeyCode: %d\nIsMousePressing: %d\nMouseX: %d\nMouseY: %d",
		IsKeyPressing,
		KeyCode,
		IsMousePressing,
		MouseX,
		MouseY
	);
	DrawShadowString(fb, 10, 30, buffer);


	/*
	** Change Color
	*/
	Color += (int)(DeltaColor * (float)deltaTime);

	if (Color >= 250) {
		DeltaColor = -0.1;
	}

	else if (Color <= 5) {
		DeltaColor = 0.1;
	}

}

void OnDestroy() {
	;
}
