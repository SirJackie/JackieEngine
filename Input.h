#define PRESSED   1
#define UNPRESSED 0

#define Keyboard int*

struct Mouse {
	int LButtonState;
	int RButtonState;
	int RealDeltaX;
	int RealDeltaY;
	int DeltaRatio;
	float DeltaX;
	float DeltaY;
};
