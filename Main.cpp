#include "Main.h"
#include "JackieEngineLayer/MathSupport.h"

void Setup (CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	
}

void Update(CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	Vec3 v1(4.0f, 8.0f, 12.0f);

	Vec3 v2 = v1 + Vec3(1.0f, 2.0f, 3.0f);
	Vec3 v3 = v1;
	v3 += Vec3(1.0f, 2.0f, 3.0f);

	Vec3 v4 = v1 - Vec3(1.0f, 2.0f, 3.0f);
	Vec3 v5 = v1;
	v5 -= Vec3(1.0f, 2.0f, 3.0f);

	float dotProduct = Vec3(1.0f, 2.0f, 3.0f) * Vec3(1.0f, 2.0f, 3.0f);
	Vec3 v6 = -Vec3(1.0f, 2.0f, 3.0f);

	int a = 0;
}
