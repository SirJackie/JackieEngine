#ifndef __JKEG_RasterizingSupport__
#define __JKEG_RasterizingSupport__

#include "../CrossBufferLayer/BasicDataTypeDeclarations.h"
#include "../CrossBufferLayer/CrossBuffer.h"
#include "MathSupport.h"
#include "ObjectSupport.h"

extern CS_FrameBuffer texImage;


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

	Vertex& Transform(Vertex& v) const
	{
		float zInv = 1.0f / v.pos.z;
		// divide all position components and attributes by z
		// (we want to be interpolating our attributes in the
		//  same space where the x,y interpolation is taking
		//  place to prevent distortion)
		v *= zInv;
		// adjust position x,y from perspective normalized space
		// to screen dimension space after perspective divide
		v.pos.x = (v.pos.x + 1.0f) * xFactor;
		v.pos.y = (-v.pos.y + 1.0f) * yFactor;
		// store 1/z in z (we will need the interpolated 1/z
		// so that we can recover the attributes after interp.)
		v.pos.z = zInv;

		return v;
	}
	Vertex GetTransformed(const Vertex& v) const
	{
		return Transform(Vertex(v));
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

void DrawFlatTriangle(
	CS_FrameBuffer& fb,
	Vertex& it0,
	Vertex& it1,
	Vertex& it2,
	Vertex& dv0,
	Vertex& dv1,
	Vertex itEdge1
);

#endif
