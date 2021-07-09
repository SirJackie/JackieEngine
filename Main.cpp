#include "Main.h"

CS_FPSCalculator  fpsCalculator;
FCamera           camera;
FObject           object;
FRasterizer       rasterizer;


void Setup (CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	object.Add(FVector4D(-1.0, -1.0,  1.0, 1.0));
	object.Add(FVector4D( 1.0, -1.0,  1.0, 1.0));
	object.Add(FVector4D( 1.0,  1.0,  1.0, 1.0));
	object.Add(FVector4D(-1.0,  1.0,  1.0, 1.0));
	object.Add(FVector4D(-1.0, -1.0, -1.0, 1.0));
	object.Add(FVector4D( 1.0, -1.0, -1.0, 1.0));
	object.Add(FVector4D( 1.0,  1.0, -1.0, 1.0));
	object.Add(FVector4D(-1.0,  1.0, -1.0, 1.0));
}

void Update(CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	camera = FCamera(
		0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f,
		-0.1f, -1000.0f, 60.0f, fb.width, fb.height
	);
	rasterizer = FRasterizer(fb);

	camera.ProjectObject(object);
	rasterizer.DrawPoint(object);

	fpsCalculator.Count(deltaTime);
	fb.PrintLn(fpsCalculator.ToString());
	fb.PrintLn(camera.ToString());
	fb.PrintLn(object.ToString());
}
