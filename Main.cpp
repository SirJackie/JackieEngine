#include "Main.h"
#include "JackieEngineLayer/MathSupport.h"

void Setup (CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	
}

void Update(CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	Vec2 v1(3.0f, 4.0f);

	// operator * tests
	Vec2 v2 = v1;
	v2 *= 5;
	Vec2 v3 = v1 * 5;

	// operator / tests
	Vec2 v4 = v1;
	v4 /= 5;
	Vec2 v5 = v1 / 5;

	int a = 0;
}
