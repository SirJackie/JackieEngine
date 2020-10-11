#define PRESSED   1
#define UNPRESSED 0

#define Keyboard int*

struct Mouse {
	int LButtonState;
	int RButtonState;
	int RealX;
	int RealY;
	int RealLastX;
	int RealLastY;
	int RealDeltaX;
	int RealDeltaY;
	int DeltaRatio;
	float DeltaX;
	float DeltaY;
	BOOL* WantToLockOrNot;
	BOOL* NowLockingOrNot;
	BOOL* HideCursorOrNot;
};
