#pragma once

#include "CrossBuffer.h"

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
			Pixel(fb, x, y) = RGB888(Color, Color, Color);
		}
	}

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
