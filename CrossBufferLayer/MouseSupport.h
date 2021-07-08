#ifndef __CSBF_MouseSupport__
#define __CSBF_MouseSupport__

#include "BasicDataTypeDeclarations.h"


class CS_Mouse {
public:
	i32 x;
    i32 y;
    i32 windowWidth;
    i32 windowHeight;

    csbool lBtnState;
    csbool mBtnState;
    csbool rBtnState;
    csbool infinityMode;

    CS_Mouse();
    CS_Mouse(i32 screenWidth_, i32 screenHeight_);
    string GetStrStatus();
    void OpenInfinityMode();
    void CloseInfinityMode();
    csbool IsInfinityModeOpened();
};

#endif
