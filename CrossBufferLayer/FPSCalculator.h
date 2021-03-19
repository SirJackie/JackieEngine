#ifndef __CSBF_FPSCalculator__
#define __CSBF_FPSCalculator__

#include "FrameBuffer.h"
#include "IOSupport.h"

/*
** FPS Calculating
*/

class FPSCalculator {
private:
	float FPS;
	int   DeltaTimeCount;
	int   FrameCount;
public:
	FPSCalculator();
	void Count(int deltaTime);
	void ShowOnScreen(FrameBuffer& fb);
};

#endif
