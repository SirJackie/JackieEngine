#ifndef __CSBF_KeyboardHelper__
#define __CSBF_KeyboardHelper__

#include "../CrossBufferLayer/CrossBuffer.h"

class LSL_KeyboardHelper {
public:
	CS_Keyboard kb;
	i8 linuxKeyBuffer[3000];

	LSL_KeyboardHelper();
	void MoveLnxBufIntoKeyBuf();
};

#endif
