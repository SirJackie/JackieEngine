#ifndef __CSBF_Main__
#define __CSBF_Main__

#include "./CrossBufferLayer/CrossBuffer.h"

/* Define Window Class Properties */
#define WindowTitle (i32*)L"CrossBuffer <Press WASD and IJKL to move the position>"


void Setup (CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime);
void Update(CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime);

#endif
