#include "Main.h"

CS_FPSCalculator fpsCalculator;
Object4D obj;


void Setup (CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	obj.add(FVector4D(-1.0, -1.0, 1.0, 1.0));
	obj.add(FVector4D(1.0, -1.0, 1.0, 1.0));
	obj.add(FVector4D(1.0, 1.0, 1.0, 1.0));
	obj.add(FVector4D(-1.0, 1.0, 1.0, 1.0));
	obj.add(FVector4D(-1.0, -1.0, -1.0, 1.0));
	obj.add(FVector4D(1.0, -1.0, -1.0, 1.0));
	obj.add(FVector4D(1.0, 1.0, -1.0, 1.0));
	obj.add(FVector4D(-1.0, 1.0, -1.0, 1.0));
}

void Update(CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	fpsCalculator.Count(deltaTime);
	fb.PrintLn(fpsCalculator.GetStrStatus());
	
	stringstream ss;

	// Camera4D Testing
	ss << "Camera4D Testing: \n";
	FCamera4D cam(
		0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f,
		-0.1f, -1000.0f, 60.0f, fb.width, fb.height
	);

	ss << cam.str();

	// Object4D Testing
	ss << obj.vecs.size();
	ss << "\n";
	Object4D obj2 = obj;
	cam.ProjectObject(obj2);

	for (ui32 i = 0; i < obj2.vecs.size(); i++) {
		ss << obj2.vecs[i].str();
		ss << "\n";
		CS_PutPixel(fb, (i32)obj2.vecs[i].x, (i32)obj2.vecs[i].y, 255, 255, 255);

	}

	fb.PrintLn(ss.str().c_str());
}
