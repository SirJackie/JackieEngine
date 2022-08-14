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

void DrawTriangle(CS_FrameBuffer& fb, Vertex& v0, Vertex& v1, Vertex& v2);

void DrawFlatTopTriangle(
	CS_FrameBuffer& fb,
	Vertex& it0,
	Vertex& it1,
	Vertex& it2
);

void DrawFlatBottomTriangle(
	CS_FrameBuffer& fb,
	Vertex& it0,
	Vertex& it1,
	Vertex& it2
);

#endif
