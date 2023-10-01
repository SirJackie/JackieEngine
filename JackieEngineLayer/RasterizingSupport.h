#ifndef __JKEG_RasterizingSupport__
#define __JKEG_RasterizingSupport__

#include "../CrossBufferLayer/BasicDataTypeDeclarations.h"
#include "../CrossBufferLayer/CrossBuffer.h"
#include "MathSupport.h"
#include "ObjectSupport.h"
#include <algorithm>
using std::swap;

extern CS_FrameBuffer texImage;


class PubeScreenTransformer
{
public:
	PubeScreenTransformer()
		:
		xFactor(0.0f),
		yFactor(0.0f),
		screenWidth(0),
		screenHeight(0)
	{}

	void SetWidthHeight(int screenWidth_, int screenHeight_)
	{
		// Define the Aspect Ration and fovY here for now (pretty dirty)
		float fovY = PI / 6.0f;  // 30 degrees
		float aspectRatio = ((float)screenWidth_) / ((float)screenHeight_);

		yFactor = 1.0f * tan(fovY);
		xFactor = yFactor * aspectRatio;

		screenWidth = screenWidth_;
		screenHeight = screenHeight_;
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
		v.pos.x = ((v.pos.x + xFactor) / (2.0f * xFactor)) * (float)screenWidth;
		v.pos.y = ((-v.pos.y + yFactor) / (2.0f * yFactor)) * (float)screenHeight;
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
	float screenWidth;
	float screenHeight;
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

void DrawBresenhamLine(CS_FrameBuffer& fb, int x0, int y0, int x1, int y1, unsigned char r, unsigned char g, unsigned char b);

#define LEFT_EDGE   1
#define RIGHT_EDGE  2
#define BOTTOM_EDGE 4
#define TOP_EDGE    8

struct Rectangle
{
	int xmin, xmax, ymin, ymax;
};

void initRectangle(struct Rectangle* rect, int xmin, int ymin, int xmax, int ymax);
int CompCode(int x, int y, struct Rectangle* rect);
int LineClip(CS_FrameBuffer& fb, struct Rectangle* rect, int x0, int y0, int x1, int y1, unsigned char r, unsigned char g, unsigned char b);

#endif
