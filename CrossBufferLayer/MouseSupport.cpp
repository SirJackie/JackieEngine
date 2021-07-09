#include "MouseSupport.h"

CS_Mouse::CS_Mouse(){
    x = 0;
    y = 0;
    lastX = 0;
    lastY = 0;
    deltaX = 0;
    deltaY = 0;
    windowWidth = 0;
    windowHeight = 0;

    lBtnState = csFalse;
    mBtnState = csFalse;
    rBtnState = csFalse;
    infinityMode = csFalse;
}

CS_Mouse::CS_Mouse(i32 windowWidth_, i32 windowHeight_){
    x = 0;
    y = 0;
    lastX = 0;
    lastY = 0;
    deltaX = 0;
    deltaY = 0;
    windowWidth = windowWidth_;
    windowHeight = windowHeight_;

    lBtnState = csFalse;
    mBtnState = csFalse;
    rBtnState = csFalse;
    infinityMode = csFalse;
}

string CS_Mouse::ToString(){
    stringstream ss;
    
    ss << "MouseX: ";
    ss << x;
    ss << "; MouseY: ";
    ss << y;

    ss << "; WindowWidth: ";
    ss << windowWidth;
    ss << "; WindowHeight: ";
    ss << windowHeight;
    

    ss << "; LBtnState: ";
    if (lBtnState == csTrue) {
        ss << "True";
    }
    else {
        ss << "False";
    }


    ss << "; MBtnState: ";
    if (mBtnState == csTrue) {
        ss << "True";
    }
    else {
        ss << "False";
    }


    ss << "; RBtnState: ";
    if (rBtnState == csTrue) {
        ss << "True";
    }
    else {
        ss << "False";
    }

    ss << "; InfinityMode: ";
    if (infinityMode == csTrue) {
        ss << "True";
    }
    else {
        ss << "False";
    }
    
    ss << "\n";
    return ss.str();
}

void CS_Mouse::OpenInfinityMode(){
    infinityMode = csTrue;
}

void CS_Mouse::CloseInfinityMode(){
    infinityMode = csFalse;
}

csbool CS_Mouse::IsInfinityModeOpened()
{
    return infinityMode;
}
