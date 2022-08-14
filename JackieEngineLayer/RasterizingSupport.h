#ifndef __JKEG_RasterizingSupport__
#define __JKEG_RasterizingSupport__

#include "../CrossBufferLayer/BasicDataTypeDeclarations.h"
#include "../CrossBufferLayer/CrossBuffer.h"
#include "MathSupport.h"
#include "ObjectSupport.h"


class PubeScreenTransformer
{
public:
	PubeScreenTransformer()
		:
		xFactor(0.0f),
		yFactor(0.0f)
	{}

	void SetWidthHeight(int screenWidth, int screenHeight)
	{
		xFactor = float(screenWidth) / 2.0f;
		yFactor = float(screenHeight) / 2.0f;
	}

	Vec3& Transform(Vec3& v) const
	{
		const float zInv = 1.0f / v.z;
		v.x = (v.x * zInv + 1.0f) * xFactor;
		v.y = (-v.y * zInv + 1.0f) * yFactor;
		return v;
	}
	Vec3 GetTransformed(const Vec3& v) const
	{
		return Transform(Vec3(v));
	}
private:
	float xFactor;
	float yFactor;
};

//void DrawTriangle(const Vec3& v0, const Vec3& v1, const Vec3& v2)
//{
//	// using pointers so we can swap (for sorting purposes)
//	const Vec3* pv0 = &v0;
//	const Vec3* pv1 = &v1;
//	const Vec3* pv2 = &v2;
//
//	// sorting vertices by y
//	if (pv1->pos.y < pv0->pos.y) std::swap(pv0, pv1);
//	if (pv2->pos.y < pv1->pos.y) std::swap(pv1, pv2);
//	if (pv1->pos.y < pv0->pos.y) std::swap(pv0, pv1);
//
//	if (pv0->pos.y == pv1->pos.y) // natural flat top
//	{
//		// sorting top vertices by x
//		if (pv1->pos.x < pv0->pos.x) std::swap(pv0, pv1);
//
//		DrawFlatTopTriangle(*pv0, *pv1, *pv2);
//	}
//	else if (pv1->pos.y == pv2->pos.y) // natural flat bottom
//	{
//		// sorting bottom vertices by x
//		if (pv2->pos.x < pv1->pos.x) std::swap(pv1, pv2);
//
//		DrawFlatBottomTriangle(*pv0, *pv1, *pv2);
//	}
//	else // general triangle
//	{
//		// find splitting vertex interpolant
//		const float alphaSplit =
//			(pv1->pos.y - pv0->pos.y) /
//			(pv2->pos.y - pv0->pos.y);
//		const auto vi = interpolate(*pv0, *pv2, alphaSplit);
//
//		if (pv1->pos.x < vi.pos.x) // major right
//		{
//			DrawFlatBottomTriangle(*pv0, *pv1, vi);
//			DrawFlatTopTriangle(*pv1, vi, *pv2);
//		}
//		else // major left
//		{
//			DrawFlatBottomTriangle(*pv0, vi, *pv1);
//			DrawFlatTopTriangle(vi, *pv1, *pv2);
//		}
//	}
//}

#endif
