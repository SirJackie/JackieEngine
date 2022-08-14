#include "Main.h"
#include "JackieEngineLayer/MathSupport.h"

void Setup (CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	
}

void Update(CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	Mat2 mat_identity = Mat2::Identity();
	Mat2 mat_scaling = Mat2::Scaling(5.0f);
	Mat2 mat_rotation = Mat2::Rotation(1.0f);

	int a = 0;
}
