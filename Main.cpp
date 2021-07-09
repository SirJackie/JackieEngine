#include "Main.h"

CS_FPSCalculator  fpsCalculator;
FCamera           camera;
FObject           object;
FRasterizer       rasterizer;
f32               walkSpeed = 0.02f;


void Setup (CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	// Initialize FrameBuffer-required Components
	camera = FCamera(
		0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f,
		-0.1f, -1000.0f, 60.0f, fb.width, fb.height
	);
	rasterizer = FRasterizer(fb);

	// Create Cube
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
	// Rotation
	object.Rotate(0.05f * deltaTime, -0.05f * deltaTime, 0.0f);

	if(kb.IsKeyPressed(CSK_W)){
		camera.Walk(FVector4D( 0.0f, 0.0f, -1.0f, 0.0f) * walkSpeed * deltaTime);
	}
	if(kb.IsKeyPressed(CSK_S)){
		camera.Walk(FVector4D( 0.0f, 0.0f,  1.0f, 0.0f) * walkSpeed * deltaTime);
	}
	if(kb.IsKeyPressed(CSK_A)){
		camera.Walk(FVector4D(-1.0f, 0.0f,  0.0f, 0.0f) * walkSpeed * deltaTime);
	}
	if(kb.IsKeyPressed(CSK_D)){
		camera.Walk(FVector4D( 1.0f, 0.0f,  0.0f, 0.0f) * walkSpeed * deltaTime);
	}

	// Projection and Rasterization
	camera.ProjectObject(object);
	rasterizer.DrawPoint(object);

	// Count FPS and Print Things
	fpsCalculator.Count(deltaTime);
	fb.PrintLn(fpsCalculator.ToString());
	fb.PrintLn(camera.ToString());
	fb.PrintLn(object.ToString());
	fb.PrintLn((i32)kb.IsKeyPressed(CSK_W));
}
