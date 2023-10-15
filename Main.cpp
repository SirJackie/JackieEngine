#include "Main.h"
#include "JackieEngineLayer/MathSupport.h"
#include "JackieEngineLayer/RasterizingSupport.h"

#include <algorithm>
using std::min;
using std::max;

static constexpr float dTheta = PI;
float offset_z = 2.0f;
float theta_x = 0.5f;
float theta_y = 0.5f;
float theta_z = 0.0f;
float deltaTheta = 0.0005f;
int autoRotate = 1;
ObjectHolder obj;
PubeScreenTransformer pst;
CS_FPSCalculator fps;

void Setup (CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	pst.SetWidthHeight(fb.width, fb.height);
	texImage.LoadFromBMP("../Images/Lena.bmp");

	// Init Z-Buffer
	zBuffer = new float[fb.width * fb.height];
	CS_Memset(zBuffer, 0.0f, fb.width * fb.height * sizeof(float));  // We're wroking on 1/z space, so it's 0.0f instead of +Infinity

	// Init ObjectHolder
	float cubeSize = 1.0f;
	float halfSize = cubeSize / 2.0f;

	// A
	obj.vec_o.emplace_back(
		Vertex(
			Vec3(-halfSize, -halfSize, -halfSize),
			Vec2(0.0f, 0.0f)
		)
	);

	// B
	obj.vec_o.emplace_back(
		Vertex(
			Vec3(halfSize, -halfSize, -halfSize),
			Vec2(1.0f, 0.0f)
		)
	);

	// C
	obj.vec_o.emplace_back(
		Vertex(
			Vec3(halfSize, halfSize, -halfSize),
			Vec2(1.0f, 1.0f)
		)
	);

	// D
	obj.vec_o.emplace_back(
		Vertex(
			Vec3(-halfSize, halfSize, -halfSize),
			Vec2(0.0f, 1.0f)
		)
	);

	// E
	obj.vec_o.emplace_back(
		Vertex(
			Vec3(-halfSize, -halfSize, halfSize),
			Vec2(1.0f, 0.0f)
		)
	);

	// F
	obj.vec_o.emplace_back(
		Vertex(
			Vec3(halfSize, -halfSize, halfSize),
			Vec2(0.0f, 0.0f)
		)
	);

	// G
	obj.vec_o.emplace_back(
		Vertex(
			Vec3(halfSize, halfSize, halfSize),
			Vec2(0.0f, 1.0f)
		)
	);

	// H
	obj.vec_o.emplace_back(
		Vertex(
			Vec3(-halfSize, halfSize, halfSize),
			Vec2(1.0f, 1.0f)
		)
	);

	// ADB
	obj.triAi_o.emplace_back(0); obj.triBi_o.emplace_back(3); obj.triCi_o.emplace_back(1);
	// BDC
	obj.triAi_o.emplace_back(1); obj.triBi_o.emplace_back(3); obj.triCi_o.emplace_back(2);
	// FGH
	obj.triAi_o.emplace_back(5); obj.triBi_o.emplace_back(6); obj.triCi_o.emplace_back(7);
	// FHE
	obj.triAi_o.emplace_back(5); obj.triBi_o.emplace_back(7); obj.triCi_o.emplace_back(4);
	// BCG
	obj.triAi_o.emplace_back(1); obj.triBi_o.emplace_back(2); obj.triCi_o.emplace_back(6);
	// BGF
	obj.triAi_o.emplace_back(1); obj.triBi_o.emplace_back(6); obj.triCi_o.emplace_back(5);
	// AEH
	obj.triAi_o.emplace_back(0); obj.triBi_o.emplace_back(4); obj.triCi_o.emplace_back(7);
	// AHD
	obj.triAi_o.emplace_back(0); obj.triBi_o.emplace_back(7); obj.triCi_o.emplace_back(3);
	// DHG
	obj.triAi_o.emplace_back(3); obj.triBi_o.emplace_back(7); obj.triCi_o.emplace_back(6);
	// DGC
	obj.triAi_o.emplace_back(3); obj.triBi_o.emplace_back(6); obj.triCi_o.emplace_back(2);
	// ABF
	obj.triAi_o.emplace_back(0); obj.triBi_o.emplace_back(1); obj.triCi_o.emplace_back(5);
	// AFE
	obj.triAi_o.emplace_back(0); obj.triBi_o.emplace_back(5); obj.triCi_o.emplace_back(4);
}

void Update(CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {

	// Delta-Time Calculation
	const float dt = (float)deltaTime / 1000.0f;
	
	// Rotation Key Control
	if (kb.IsKeyPressed('W'))
	{
		theta_x += dTheta * dt;
	}
	if (kb.IsKeyPressed('S'))
	{
		theta_x -= dTheta * dt;
	}
	if (kb.IsKeyPressed('A'))
	{
		theta_y += dTheta * dt;
	}
	if (kb.IsKeyPressed('D'))
	{
		theta_y -= dTheta * dt;
	}
	if (kb.IsKeyPressed('Q'))
	{
		theta_z += dTheta * dt;
	}
	if (kb.IsKeyPressed('E'))
	{
		theta_z -= dTheta * dt;
	}

	// Move Forward or Backward
	if (kb.IsKeyPressed('R'))
	{
		offset_z += 2.0f * dt;
	}
	if (kb.IsKeyPressed('F'))
	{
		offset_z -= 2.0f * dt;
	}

	// 3D Transform

	obj.Duplicate();

	Mat3 rotation =
		Mat3::RotationX(theta_x) *
		Mat3::RotationY(theta_y) *
		Mat3::RotationZ(theta_z);

	// Transform
	for (int i = 0; i < obj.vec.size(); i++) {
		obj.vec[i].pos *= rotation;
		obj.vec[i].pos += Vec3(0.0f, 0.0f, offset_z);
		pst.Transform(obj.vec[i]);
	}

	// // Draw Lines
	// Rectangle screenRect = { 0, fb.width - 1, 0, fb.height - 1 };
	// 
	// for (int i = 0; i < obj.triAi.size(); i++) {
	//     DrawVertexLine(fb, screenRect, obj.vec[obj.triAi[i]], obj.vec[obj.triBi[i]]);
	//     DrawVertexLine(fb, screenRect, obj.vec[obj.triBi[i]], obj.vec[obj.triCi[i]]);
	// 	   DrawVertexLine(fb, screenRect, obj.vec[obj.triAi[i]], obj.vec[obj.triCi[i]]);
	// }

	// Draw Triangles
	CS_Memset(zBuffer, 0.0f, fb.width * fb.height * sizeof(float));  // We're wroking on 1/z space, so it's 0.0f instead of +Infinity

	for (int i = 0; i < obj.triAi.size(); i++) {
		DrawTriangle(
			fb,
			obj.vec[obj.triAi[i]],
			obj.vec[obj.triBi[i]],
			obj.vec[obj.triCi[i]]
		);
	}

	fps.Count(deltaTime);
	fb.PrintLn("WASDQE to Rotate, RF to Zoom, G to Enable/Disable Auto Rotation.");
	fb.Print(fps.ToString());
	fb.Print("autoRotate = ");
	fb.Print((int)autoRotate);
	fb.Print("\ntheta_x = ");
	fb.Print(theta_x);
	fb.Print("\ntheta_y = ");
	fb.Print(theta_y);
	fb.Print("\ntheta_z = ");
	fb.Print(theta_z);
	fb.Print("\noffset_z = ");
	fb.Print(offset_z);

	if (autoRotate >= 1) {
		theta_x += deltaTheta * deltaTime;
		theta_y += deltaTheta * deltaTime;
		//theta_z += deltaTheta * deltaTime;
	}

	int Deadzone = 250 / deltaTime;  // 1/4 seconds

	if (kb.IsKeyPressed(CSK_G)) {
		if (autoRotate == 1) {
			autoRotate = -Deadzone;  // Disable, And Also Maintain 15 frames of Key-Press-Dead-Zone
		}
		else if (autoRotate == 0) {
			autoRotate += Deadzone;  // Enable, And Also Maintain 15 frames of Key-Press-Dead-Zone
		}
		else {
			;  // Inside the Key-Press-Dead-Zone, do nothing
		}
	}

	if (autoRotate > 1) {
		autoRotate--;  // Decrement Key-Press-Dead-Zone Negatively
	}
	else if (autoRotate < 0) {
		autoRotate++;  // Decrement Key-Press-Dead-Zone Positively
	}
}
