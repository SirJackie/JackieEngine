#include "Main.h"
#include "JackieEngineLayer/MathSupport.h"

void Setup (CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	
}

void Update(CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	Mat2 m1 = {
		1, 2,
		3, 4
	};

	Mat2 m2 = {
		5, 6,
		7, 8
	};

	Mat2 m3 = m1 * m2;

	Mat2 m4 = m1;
	m4 *= m2;

	int a = 0;
}
