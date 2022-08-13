#include "Main.h"

unsigned char c = 0;
bool cIncrementFlag = false;

void Setup (CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	
}

void Update(CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	int cPrime = mouse.GetLBtnState() ? 255 - c : c;

	for (int y = 0; y < fb.height; y++) {
		for (int x = 0; x < fb.width; x++) {
			fb.PutPixel(x, y, c, c, c);
		}
	}

	for (int y = 200; y < fb.height - 200; y++) {
		for (int x = 200; x < fb.width - 200; x++) {
			fb.PutPixel(x, y, cPrime, cPrime, cPrime);
		}
	}

	c == 255 ? cIncrementFlag = false : NULL;
	c == 0 ? cIncrementFlag = true : NULL;
	cIncrementFlag ? c++ : c--;

	if (kb.IsKeyPressed('R')) {
		c = 0;
	}
}
