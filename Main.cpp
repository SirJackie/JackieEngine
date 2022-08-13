#include "Main.h"
#include "JackieEngineLayer/MathSupport.h"

void Setup (CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	
}

void Update(CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	Vec3 v1(4.0f, 8.0f, 12.0f);

	Vec3 v2 = v1 * 4.0f;
	Vec3 v3 = v1;
	v3 *= 4.0f;

	Vec3 v4 = v1 / 4.0f;
	Vec3 v5 = v1;
	v5 /= 4.0f;

	int a = 0;
}
