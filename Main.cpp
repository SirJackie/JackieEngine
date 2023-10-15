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
Cube cube(1.0f);
PubeScreenTransformer pst;
CS_FPSCalculator fps;

void Setup (CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	pst.SetWidthHeight(fb.width, fb.height);
	texImage.LoadFromBMP("../Images/TestingTexture_512x512.bmp");

	// Init Z-Buffer
	zBuffer = new float[fb.width * fb.height];
	CS_Memset(zBuffer, 0.0f, fb.width * fb.height * sizeof(float));  // We're wroking on 1/z space, so it's 0.0f instead of +Infinity
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

	auto lines = cube.GetLines();
	auto triangles = cube.GetTriangles();

	Mat3 rotation =
		Mat3::RotationX(theta_x) *
		Mat3::RotationY(theta_y) *
		Mat3::RotationZ(theta_z);

	// Transform
	for (auto& v : triangles.vertices) {
		v.pos *= rotation;
		v.pos += Vec3(0.0f, 0.0f, offset_z);
		pst.Transform(v);
	}

	// Draw Indicies
	Rectangle screenRect = { 0, fb.width - 1, 0, fb.height - 1 };
	for (int i = 0; i < lines.indices.size(); i += 2) {
		LineClip(
			fb, &screenRect,

			(int)triangles.vertices[lines.indices[i + 0]].pos.x,  // x0
			(int)triangles.vertices[lines.indices[i + 0]].pos.y,  // x1

			(int)triangles.vertices[lines.indices[i + 1]].pos.x,  // y0
			(int)triangles.vertices[lines.indices[i + 1]].pos.y,  // y1

			255, 255, 255  // rgb
		);
	}

	// Draw Verticies
	for (int i = 0; i < triangles.vertices.size(); i++) {
		int x = (int)triangles.vertices[i].pos.x;
		int y = (int)triangles.vertices[i].pos.y;

		fb.PutPixel(
			min( fb.width - 1,  max( 0, x )),
			min( fb.height - 1, max( 0, y )),
			255,
			0,
			0
		);
	}

	// Draw Triangles
	CS_Memset(zBuffer, 0.0f, fb.width * fb.height * sizeof(float));  // We're wroking on 1/z space, so it's 0.0f instead of +Infinity

	for (int i = 0; i < triangles.indices.size(); i += 3) {
		DrawTriangle(
			fb,
			triangles.vertices[triangles.indices[i + 0]],
			triangles.vertices[triangles.indices[i + 1]],
			triangles.vertices[triangles.indices[i + 2]]
		);
	}

	fps.Count(deltaTime);
	fb.PrintLn(fps.ToString());
}
