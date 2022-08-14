#include "RasterizingSupport.h"

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
	fb.PutPixel(
		(int)it0.pos.x,
		(int)it0.pos.y,
		(int)it0.tex.x * 255,
		(int)it0.tex.y * 255,
		(int)255
	);
	fb.PutPixel(
		(int)it1.pos.x,
		(int)it1.pos.y,
		(int)it1.tex.x * 255,
		(int)it1.tex.y * 255,
		(int)255
	);
	fb.PutPixel(
		(int)it2.pos.x,
		(int)it2.pos.y,
		(int)it2.tex.x * 255,
		(int)it2.tex.y * 255,
		(int)255
	);
}

void DrawFlatBottomTriangle(CS_FrameBuffer & fb, Vertex & it0, Vertex & it1, Vertex & it2)
{
	fb.PutPixel(
		(int)it0.pos.x,
		(int)it0.pos.y,
		(int)it0.tex.x * 255,
		(int)it0.tex.y * 255,
		(int)255
	);
	fb.PutPixel(
		(int)it1.pos.x,
		(int)it1.pos.y,
		(int)it1.tex.x * 255,
		(int)it1.tex.y * 255,
		(int)255
	);
	fb.PutPixel(
		(int)it2.pos.x,
		(int)it2.pos.y,
		(int)it2.tex.x * 255,
		(int)it2.tex.y * 255,
		(int)255
	);
}
