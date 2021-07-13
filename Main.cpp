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
		0.0f, 0.0f, 5.0f, -1.85897f, 0.217391f, 0.0f,
		-0.1f, -1000.0f, 60.0f, fb.width, fb.height
	);
	rasterizer = FRasterizer(fb);

	object = FObject(CS_Path().join("..").join("Resources").join("Lena.bmp"));

	// Create Cube's Vertecies
	object.Add(FVectorTex(FVector4D(-1.0, -1.0,  1.0, 1.0), FVector3D(0.0f, 1.0f, 1.0f)));  // v0
	object.Add(FVectorTex(FVector4D( 1.0, -1.0,  1.0, 1.0), FVector3D(1.0f, 1.0f, 1.0f)));  // v1
	object.Add(FVectorTex(FVector4D( 1.0,  1.0,  1.0, 1.0), FVector3D(1.0f, 0.0f, 1.0f)));  // v2
	object.Add(FVectorTex(FVector4D(-1.0,  1.0,  1.0, 1.0), FVector3D(0.0f, 0.0f, 1.0f)));  // v3
	object.Add(FVectorTex(FVector4D(-1.0, -1.0, -1.0, 1.0), FVector3D(1.0f, 1.0f, 1.0f)));  // v4
	object.Add(FVectorTex(FVector4D( 1.0, -1.0, -1.0, 1.0), FVector3D(0.0f, 1.0f, 1.0f)));  // v5
	object.Add(FVectorTex(FVector4D( 1.0,  1.0, -1.0, 1.0), FVector3D(0.0f, 0.0f, 1.0f)));  // v6
	object.Add(FVectorTex(FVector4D(-1.0,  1.0, -1.0, 1.0), FVector3D(1.0f, 0.0f, 1.0f)));  // v7

	// Create Cube's Indecies
	object.Add(0, 1, 3);  // n1
	object.Add(2, 3, 1);  // n2
	object.Add(5, 4, 6);  // f1
	object.Add(7, 6, 4);  // f2
	object.Add(4, 0, 7);  // l1
	object.Add(3, 7, 0);  // l2
	object.Add(1, 5, 2);  // r1
	object.Add(6, 2, 5);  // r2
	object.Add(3, 2, 7);  // t1
	object.Add(6, 7, 2);  // t2
	object.Add(5, 0, 4);  // b1
	object.Add(5, 1, 0);  // b2

	// Open Mouse Locking
	mouse.OpenInfinityMode();
}

f32 positionX = 10.0f;
f32 positionY = 10.0f;

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
	rasterizer.DrawTriangle(object);

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
