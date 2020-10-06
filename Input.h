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

void CalcMouseDelta(Mouse* mouse) {
	mouse->DeltaX = mouse->X - mouse->LastX;
	mouse->DeltaY = mouse->Y - mouse->LastY;
}
