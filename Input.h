#define PRESSED   1
#define UNPRESSED 0

#define Keyboard int*

struct Mouse {
	int LButtonState;
	int RButtonState;
	int RealX;
	int RealY;
	int RealDeltaX;
	int RealDeltaY;
	int DeltaRatio;
	float DeltaX;
	float DeltaY;
	BOOL* WantToLockOrNot;
	BOOL* NowLockingOrNot;
	BOOL* HideCursorOrNot;
};

void LockMouse(Mouse mouse) {
	*(mouse.WantToLockOrNot) = TRUE;
	*(mouse.NowLockingOrNot) = TRUE;
	*(mouse.HideCursorOrNot) = TRUE;
}

void UnlockMouse(Mouse mouse) {
	*(mouse.WantToLockOrNot) = FALSE;
	*(mouse.NowLockingOrNot) = FALSE;
	*(mouse.HideCursorOrNot) = FALSE;
}
