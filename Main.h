#pragma once

#include "CrossBuffer.h"

void OnCreate() {
	;
}

void Setup(FrameBuffer fb, int width, int height) {
	for (int y = 0; y < 100; y++) {
		for (int x = 0; x < 100; x++) {
			Pixel(fb, x, y) = RGB888(255, 0 , 0);
		}
	}
}

void Update(FrameBuffer fb, int width, int height) {
	for (int y = 0; y < 100; y++) {
		for (int x = 0; x < 100; x++) {
			Pixel(fb, x, y) = RGB888(255, 255, 255);
		}
	}
}

void OnDestroy() {
	;
}
