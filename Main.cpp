#include "Main.h"

CS_FPSCalculator  fpsCalculator;
FObject4D         obj;
FCamera4D         camera;
FRasterizer       rasterizer;


void Setup (CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	obj.Add(FVector4D(-1.0, -1.0, 1.0, 1.0));
	obj.Add(FVector4D(1.0, -1.0, 1.0, 1.0));
	obj.Add(FVector4D(1.0, 1.0, 1.0, 1.0));
	obj.Add(FVector4D(-1.0, 1.0, 1.0, 1.0));
	obj.Add(FVector4D(-1.0, -1.0, -1.0, 1.0));
	obj.Add(FVector4D(1.0, -1.0, -1.0, 1.0));
	obj.Add(FVector4D(1.0, 1.0, -1.0, 1.0));
	obj.Add(FVector4D(-1.0, 1.0, -1.0, 1.0));
}

void Update(CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	fpsCalculator.Count(deltaTime);
	fb.PrintLn(fpsCalculator.GetStrStatus());

	camera = FCamera4D(
		0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f,
		-0.1f, -1000.0f, 60.0f, fb.width, fb.height
	);

	rasterizer = FRasterizer(fb);
	
	//stringstream ss;
	//ss << "Camera4D Testing: \n";
	//ss << camera.str();
	//ss << obj.vl.size();
	//ss << "\n";
	//fb.PrintLn(ss.str().c_str());

	camera.ProjectObject(obj);
	rasterizer.DrawPoint(obj);
}
