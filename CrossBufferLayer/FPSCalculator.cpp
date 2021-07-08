#include "FPSCalculator.h"

CS_FPSCalculator::CS_FPSCalculator() {
	fps             = 0.0f;
	deltaTimeCount  = 0;
	frameCount      = 0;
}

void CS_FPSCalculator::Count(i32 deltaTime)
{
	/* Calculate FPS */
	deltaTimeCount += deltaTime;
	frameCount += 1;

	if (deltaTimeCount > 1000) {
		fps = (float)frameCount / ((float)deltaTimeCount / 1000);
		deltaTimeCount -= 1000;
		frameCount = 0;
	}
}

f32 CS_FPSCalculator::GetCurrentFPS()
{
	return fps;
}
