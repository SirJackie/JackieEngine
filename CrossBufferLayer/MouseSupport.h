#ifndef __CSBF_MouseSupport__
#define __CSBF_MouseSupport__

#include "BasicDataTypeDeclarations.h"


class CS_Mouse {
public:
	i32 x;
    i32 y;
    i32 lastX;
    i32 lastY;
    i32 deltaX;
    i32 deltaY;
    i32 windowWidth;
    i32 windowHeight;

    csbool lBtnState;
    csbool mBtnState;
    csbool rBtnState;
    csbool infinityMode;

    CS_Mouse();
    CS_Mouse(i32 screenWidth_, i32 screenHeight_);
    void OpenInfinityMode();
    void CloseInfinityMode();
    csbool IsInfinityModeOpened();
    string ToString();
};

#endif
