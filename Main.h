#ifndef __CSBF_Main__
#define __CSBF_Main__

#include "./CrossBufferLayer/CrossBuffer.h"
#include "./JackieEngineLayer/JackieEngine.h"
#include <vector>
#include <sstream>
using std::vector;
using std::stringstream;

/* Define Window Class Properties */
#define WindowTitle (i32*)L"Jackie Engine"


void Setup (CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime);
void Update(CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime);

#endif
