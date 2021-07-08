#ifndef __CSBF_KeyboardHelper__
#define __CSBF_KeyboardHelper__

#include "../CrossBufferLayer/CrossBuffer.h"


class WSL_KeyboardHelper {
public:
	CS_Keyboard kb;
	i8 windowsKeyBuffer[256];

	WSL_KeyboardHelper();
	void MoveWinBufIntoKeyBuf();
};

#endif
