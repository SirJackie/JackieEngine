#include "Main.h"
#include "JackieEngineLayer/MathSupport.h"
#include "JackieEngineLayer/RasterizingSupport.h"

#include <algorithm>
using std::min;
using std::max;

static constexpr float dTheta = PI;
float offset_z = 1.5f;
float theta_x = -0.5f;
float theta_y = -0.5f;
float theta_z = 0.0f;
//Cube cube(1.0f);
ObjectHolder obj;
PubeScreenTransformer pst;
CS_FPSCalculator fps;

void Setup (CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	pst.SetWidthHeight(fb.width, fb.height);
	texImage.LoadFromBMP("../Images/TestingTexture_512x512.bmp");

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

	//auto lines = cube.GetLines();
	//auto triangles = cube.GetTriangles();
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

	// Draw Indicies
	Rectangle screenRect = { 0, fb.width - 1, 0, fb.height - 1 };
	
	for (int i = 0; i < obj.triAi.size(); i++) {
		DrawVertexLine(fb, screenRect, obj.vec[obj.triAi[i]], obj.vec[obj.triBi[i]]);
		DrawVertexLine(fb, screenRect, obj.vec[obj.triBi[i]], obj.vec[obj.triCi[i]]);
		DrawVertexLine(fb, screenRect, obj.vec[obj.triAi[i]], obj.vec[obj.triCi[i]]);
	}

	//// Draw Verticies
	//for (int i = 0; i < triangles.vertices.size(); i++) {
	//	int x = (int)triangles.vertices[i].pos.x;
	//	int y = (int)triangles.vertices[i].pos.y;

	//	fb.PutPixel(
	//		min( fb.width - 1,  max( 0, x )),
	//		min( fb.height - 1, max( 0, y )),
	//		255,
	//		0,
	//		0
	//	);
	//}

	// Draw Triangles
	CS_Memset(zBuffer, 0.0f, fb.width * fb.height * sizeof(float));  // We're wroking on 1/z space, so it's 0.0f instead of +Infinity

	//for (int i = 0; i < obj.triAi.size(); i += 3) {
	for (int i = 0; i < 4; i++) {
		DrawTriangle(
			fb,
			obj.vec[obj.triAi[i]],
			obj.vec[obj.triBi[i]],
			obj.vec[obj.triCi[i]]
		);
	}

	fps.Count(deltaTime);
	fb.PrintLn(fps.ToString());
}
