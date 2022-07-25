#ifndef __CSBF_MouseSupport__
#define __CSBF_MouseSupport__

#include "BasicDataTypeDeclarations.h"


class CS_Mouse {

private:
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
	
public:
    CS_Mouse();
    CS_Mouse(i32 screenWidth_, i32 screenHeight_);
    void OpenInfinityMode();
    void CloseInfinityMode();
    string ToString();

public:
	// Getters
	i32 GetX();
	i32 GetY();
	i32 GetLastX();
	i32 GetLastY();
	i32 GetDeltaX();
	i32 GetDeltaY();
	i32 GetWindowWidth();
	i32 GetWindowHeight();
	csbool IsInfinityModeOpened();

public:
	// Setters
	// The following setters are only for the framework to use internally
	// DO NOT USE THE FOLLOWING SETTERS IN YOUR PROGRAM !!!
	void SetX(i32 x_);
	void SetY(i32 y_);
	void SetLastX(i32 lastX_);
	void SetLastY(i32 lastY_);
	void SetDeltaX(i32 deltaX_);
	void SetDeltaY(i32 deltaY_);
	void SetLBtnState(csbool lBtnState_);
	void SetMBtnState(csbool mBtnState_);
	void SetRBtnState(csbool rBtnState_);
};

#endif
