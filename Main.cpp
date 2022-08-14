#include "Main.h"
#include "JackieEngineLayer/MathSupport.h"

void Setup (CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	
}

void Update(CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	Mat3 m1(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9
	);

	Mat3 m2(
		9, 8, 7,
		6, 5, 4,
		3, 2, 1
	);

	Mat3 m3 = m1 * m2;
	Mat3 m4 = m1;
	m4 *= m2;

	int a = 0;
}
