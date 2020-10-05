#pragma once

#define PRESSED   1
#define UNPRESSED 0

#define Keyboard int*

struct Mouse {
	int LButtonState;
	int RButtonState;
	int X;
	int Y;
	int LastX;
	int LastY;
	int DeltaX;
	int DeltaY;
};

void InitMouse(Mouse* mouse) {
	mouse->LButtonState = 0;
	mouse->RButtonState = 0;
	mouse->X            = 0;
	mouse->Y            = 0;
	mouse->LastX        = 0;
	mouse->LastY        = 0;
	mouse->DeltaX       = 0;
	mouse->DeltaY       = 0;
}

void CalcMouseDelta(Mouse* mouse) {
	mouse->DeltaX = mouse->X - mouse->LastX;
	mouse->DeltaY = mouse->Y - mouse->LastY;
}
