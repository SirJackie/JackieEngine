#include "Main.h"
#include "JackieEngineLayer/MathSupport.h"

void Setup (CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	
}

void Update(CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	Vec2 v1(3.0f, 4.0f);

	// operator + tests
	Vec2 v2 = v1;
	v2 += Vec2(1.0f, 2.0f);
	Vec2 v3 = v1 + Vec2(1.0f, 2.0f);

	// operator - tests
	Vec2 v4 = v1;
	v4 -= Vec2(0.5f, 1.0f);
	Vec2 v5 = v1 - Vec2(0.5f, 1.0f);

	int a = 0;
}
