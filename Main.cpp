#include "Main.h"
#include "JackieEngineLayer/MathSupport.h"

void Setup (CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	
}

void Update(CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	Mat3 mat_identity = Mat3::Identity();
	Mat3 mat_scaling = Mat3::Scaling(5.0f);
	Mat3 mat_rotationZ = Mat3::RotationZ(1.0f);
	Mat3 mat_rotationY = Mat3::RotationY(1.0f);
	Mat3 mat_rotationX = Mat3::RotationX(1.0f);

	int a = 0;
}
