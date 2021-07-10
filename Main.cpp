#include "Main.h"

CS_FPSCalculator  fpsCalculator;
FCamera           camera;
FObject           object;
FRasterizer       rasterizer;
f32               walkSpeed = 0.01f;
f32               mouseSensitivity = 40.0f;
csbool            rotate = csFalse;


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

	// Open Mouse Locking
	mouse.OpenInfinityMode();
}

void Update(CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	// Rotation
	if(rotate){
		object.Rotate(0.05f * deltaTime, -0.05f * deltaTime, 0.0f);
	}

	if(kb.IsKeyPressed(CSK_W)){
		camera.Walk(FVector4D( 0.0f, 0.0f, -1.0f, 1.0f) * walkSpeed * deltaTime);
	}
	if(kb.IsKeyPressed(CSK_S)){
		camera.Walk(FVector4D( 0.0f, 0.0f,  1.0f, 1.0f) * walkSpeed * deltaTime);
	}
	if(kb.IsKeyPressed(CSK_A)){
		camera.Walk(FVector4D(-1.0f, 0.0f,  0.0f, 1.0f) * walkSpeed * deltaTime);
	}
	if(kb.IsKeyPressed(CSK_D)){
		camera.Walk(FVector4D( 1.0f, 0.0f,  0.0f, 1.0f) * walkSpeed * deltaTime);
	}
	if(kb.IsKeyPressed(CSK_Space)){
		camera.Elevator( walkSpeed * deltaTime);
	}
	if(kb.IsKeyPressed(CSK_Shift)){
		camera.Elevator(-walkSpeed * deltaTime);
	}
	if(kb.IsKeyFirstTimePressed(CSK_R)){
		rotate = !rotate;
	}
	camera.Rotate(
		(f32)mouse.deltaY / (f32)mouse.windowHeight * mouseSensitivity,
		(f32)mouse.deltaX / (f32)mouse.windowWidth  * mouseSensitivity,
		0.0f
	);
	

	// Projection and Rasterization
	camera.ProjectObject(object);
	rasterizer.DrawPoint(object);

	// Count FPS and Print Things
	fpsCalculator.Count(deltaTime);
	fb.Print(mouse.ToString());
	fb.PrintLn(kb.ToString());

	fb.PrintLn(fpsCalculator.ToString());

	fb.PrintLn("Press WASD to Move, Rotate the Mouse to Look.");
	fb.PrintLn("Press R to Rotate the Cube, Space to Rise, Shift to Fall\n");
	
	fb.PrintLn(camera.ToString());
	fb.PrintLn(object.ToString());
}
