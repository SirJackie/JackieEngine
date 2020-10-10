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
	int DeltaRatio;
	float DeltaX;
	float DeltaY;
};

void CalcMouseDelta(Mouse* mouse) {
	mouse->DeltaX = 1.0f * (mouse->X - mouse->LastX) / mouse->DeltaRatio;
	mouse->DeltaY = 1.0f * (mouse->Y - mouse->LastY) / mouse->DeltaRatio;
}
