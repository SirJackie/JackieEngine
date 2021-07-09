#ifndef __CSBF_FPSCalculator__
#define __CSBF_FPSCalculator__

#include "BasicDataTypeDeclarations.h"


class CS_FPSCalculator {
private:
	f32 fps;
	i32 deltaTimeCount;
	i32 frameCount;
public:
	CS_FPSCalculator();
	void    Count(i32 deltaTime);
	f32     GetCurrentFPS();
	string  ToString();
};

#endif
