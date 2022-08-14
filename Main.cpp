#include "Main.h"
#include "JackieEngineLayer/MathSupport.h"

void Setup (CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	
}

void Update(CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	Vec2 vec(1.0f, 1.0f);
	Mat2 mat(
		1, 2,
		3, 4
	);

	Vec2 result1 = vec * mat;
	Vec2 result2 = vec;
	result2 *= mat;

	int a = 0;
}
