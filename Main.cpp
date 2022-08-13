#include "Main.h"
#include "JackieEngineLayer/MathSupport.h"

void Setup (CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	
}

void Update(CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	Vec3 v1(3.0f, 4.0f, 12.0f);
	float lensq = v1.LenSq();
	float len = v1.Len();

	Vec3 v2 = v1.GetNormalized();
	Vec3 v3 = v1;
	v3.Normalize();

	int a = 0;
}
