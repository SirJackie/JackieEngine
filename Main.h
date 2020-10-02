#pragma once

#include "CrossBuffer.h"
#include "TextOutput.h"

int Color = 0;
int DeltaColor = 2;

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

void Update(FrameBuffer fb, int width, int height) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int a = RGB888(Color, Color, Color);
			Pixel(fb, x, y) = a;
		}
	}

	char chSmall[] = "the quick brown fox jumps over a lazy dog.";
	char chBig[] = "THE QUICK BROWN FOX JUMPS OVER A LAZY DOG.";
	DrawShadowString(fb, 100, 100, chSmall);
	DrawShadowString(fb, 100, 116, chBig);


	Color += DeltaColor;

	if (Color == 254) {
		DeltaColor = -2;
	}

	else if (Color == 0) {
		DeltaColor = 2;
	}

}

void OnDestroy() {
	;
}
