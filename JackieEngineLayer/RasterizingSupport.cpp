#include "RasterizingSupport.h"

#include <algorithm>
using std::min;

CS_FrameBuffer texImage;

void DrawTriangle(CS_FrameBuffer & fb, Vertex & v0, Vertex & v1, Vertex & v2)
{
	// using pointers so we can swap (for sorting purposes)
	Vertex* pv0 = &v0;
	Vertex* pv1 = &v1;
	Vertex* pv2 = &v2;

	// sorting vertices by y
	if (pv1->pos.y < pv0->pos.y) std::swap(pv0, pv1);
	if (pv2->pos.y < pv1->pos.y) std::swap(pv1, pv2);
	if (pv1->pos.y < pv0->pos.y) std::swap(pv0, pv1);

	if (pv0->pos.y == pv1->pos.y) // natural flat top
	{
		// sorting top vertices by x
		if (pv1->pos.x < pv0->pos.x) std::swap(pv0, pv1);

		DrawFlatTopTriangle(fb, *pv0, *pv1, *pv2);
	}
	else if (pv1->pos.y == pv2->pos.y) // natural flat bottom
	{
		// sorting bottom vertices by x
		if (pv2->pos.x < pv1->pos.x) std::swap(pv1, pv2);

		DrawFlatBottomTriangle(fb, *pv0, *pv1, *pv2);
	}
	else // general triangle
	{
		// find splitting vertex interpolant
		float alphaSplit =
			(pv1->pos.y - pv0->pos.y) /
			(pv2->pos.y - pv0->pos.y);
		auto vi = interpolate(*pv0, *pv2, alphaSplit);

		if (pv1->pos.x < vi.pos.x) // major right
		{
			DrawFlatBottomTriangle(fb, *pv0, *pv1, vi);
			DrawFlatTopTriangle(fb, *pv1, vi, *pv2);
		}
		else // major left
		{
			DrawFlatBottomTriangle(fb, *pv0, vi, *pv1);
			DrawFlatTopTriangle(fb, vi, *pv1, *pv2);
		}
	}
}

void DrawFlatTopTriangle(CS_FrameBuffer & fb, Vertex & it0, Vertex & it1, Vertex & it2)
{
	// calulcate dVertex / dy
	// change in interpolant for every 1 change in y
	float delta_y = it2.pos.y - it0.pos.y;
	auto dit0 = (it2 - it0) / delta_y;
	auto dit1 = (it2 - it1) / delta_y;

	// create right edge interpolant
	auto itEdge1 = it1;

	// call the flat triangle render routine
	DrawFlatTriangle(fb, it0, it1, it2, dit0, dit1, itEdge1);
}

void DrawFlatBottomTriangle(CS_FrameBuffer & fb, Vertex & it0, Vertex & it1, Vertex & it2)
{
	// calulcate dVertex / dy
	// change in interpolant for every 1 change in y
	float delta_y = it2.pos.y - it0.pos.y;
	auto dit0 = (it1 - it0) / delta_y;
	auto dit1 = (it2 - it0) / delta_y;

	// create right edge interpolant
	auto itEdge1 = it0;

	// call the flat triangle render routine
	DrawFlatTriangle(fb, it0, it1, it2, dit0, dit1, itEdge1);
}

void DrawFlatTriangle(CS_FrameBuffer& fb, Vertex & it0, Vertex & it1, Vertex & it2, Vertex & dv0, Vertex & dv1, Vertex itEdge1)
{
	// create edge interpolant for left edge (always v0)
	auto itEdge0 = it0;

	// calculate start and end scanlines
	int yStart = (int)ceil(it0.pos.y - 0.5f);
	int yEnd = (int)ceil(it2.pos.y - 0.5f); // the scanline AFTER the last line drawn

												  // do interpolant prestep
	itEdge0 += dv0 * (float(yStart) + 0.5f - it0.pos.y);
	itEdge1 += dv1 * (float(yStart) + 0.5f - it0.pos.y);

	for (int y = yStart; y < yEnd; y++, itEdge0 += dv0, itEdge1 += dv1)
	{
		// calculate start and end pixels
		int xStart = (int)ceil(itEdge0.pos.x - 0.5f);
		int xEnd = (int)ceil(itEdge1.pos.x - 0.5f); // the pixel AFTER the last pixel drawn

		// create scanline interpolant startpoint
		// (some waste for interpolating x,y,z, but makes life easier not having
		//  to split them off, and z will be needed in the future anyways...)
		auto iLine = itEdge0;

		// calculate delta scanline interpolant / dx
		float dx = itEdge1.pos.x - itEdge0.pos.x;
		auto diLine = (itEdge1 - iLine) / dx;

		// prestep scanline interpolant
		iLine += diLine * (float(xStart) + 0.5f - itEdge0.pos.x);

		for (int x = xStart; x < xEnd; x++, iLine += diLine)
		{
			// recover interpolated z from interpolated 1/z
			float z = 1.0f / iLine.pos.z;
			// recover interpolated attributes
			// (wasted effort in multiplying pos (x,y,z) here, but
			//  not a huge deal, not worth the code complication to fix)
			auto attr = iLine * z;
			// invoke pixel shader with interpolated vertex attributes
			// and use result to set the pixel color on the screen

			//fb.PutPixel(x, y, (int)(attr.tex.x * 255), (int)(attr.tex.y * 255), 255);

			int pixelX = (int) min (  attr.tex.x*(float)texImage.width , (float)(texImage.width -1));
			int pixelY = (int) min (  attr.tex.y*(float)texImage.height, (float)(texImage.height-1));

			fb.PutPixel(
				x,
				y,
				texImage.redBuffer   [pixelY * texImage.width + pixelX],
				texImage.greenBuffer [pixelY * texImage.width + pixelX],
				texImage.blueBuffer  [pixelY * texImage.width + pixelX]
			);

			//gfx.PutPixel(x, y, effect.ps(attr));
		}
	}
}

void DrawBresenhamLine(CS_FrameBuffer& fb, int x0, int y0, int x1, int y1, unsigned char r, unsigned char g, unsigned char b) {
	// Crucial 1 : 45 - 90 deg support
	// Crucial 2 : the 3rd quadrant support
	// Crucial 3 : the 2nd and 4th quadrant support

	// -----------------------------------------------

	// Crucial 1
	bool steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		std::swap(x0, y0);
		std::swap(x1, y1);
	}

	// Crucial 2
	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	int dx = x1 - x0;
	int dy = abs(y1 - y0);  // Crucial 3
	int y = y0;
	int p = 2 * dy - dx;

	int stepY = y0 > y1 ? -1 : 1;  // Crucial 3

	for (int x = x0; x < x1; x++) {

		// Crucial 1
		if (steep) {
			fb.PutPixel(y, x, r, g, b);
		}
		else {
			fb.PutPixel(x, y, r, g, b);
		}

		if (p < 0) {
			p += 2 * dy;
		}
		else {
			p += 2 * dy - 2 * dx;
			y += stepY;  // Crucial 3
		}
	}

}