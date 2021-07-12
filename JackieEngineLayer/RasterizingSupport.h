#ifndef __JKEG_RasterizingSupport__
#define __JKEG_RasterizingSupport__

#include "../CrossBufferLayer/BasicDataTypeDeclarations.h"
#include "../CrossBufferLayer/CrossBuffer.h"
#include "MathSupport.h"
#include "ObjectSupport.h"

class FRasterizer {
public:
	CS_FrameBuffer* ptrfb;

	FRasterizer();
	FRasterizer(CS_FrameBuffer& fb_);

	void DrawProtectedCube(i32 x0, i32 y0, i32 x1, i32 y1, ui8 r_, ui8 g_, ui8 b_);
	void DrawRadiusCube(i32 x, i32 y, i32 radius);
	void DrawTriangle           (const FVectorTex& v0_, const FVectorTex& v1_, const FVectorTex& v2_, CS_FrameBuffer& texture);
	void DrawFlatBottomTriangle (const FVectorTex& v0_, const FVectorTex& v1_, const FVectorTex& v2_, CS_FrameBuffer& texture);
	void DrawFlatTopTriangle    (const FVectorTex& v0_, const FVectorTex& v1_, const FVectorTex& v2_, CS_FrameBuffer& texture);
	void DrawFlatTriangle       (i32 yStart, i32 yEnd, FVectorTex xLeft, FVectorTex xRight, const FVectorTex& xLeftStep, const FVectorTex& xRightStep);

	void Draw3DPoint(FVector3D& point);
	void Draw4DPoint(FVector4D& point);
	void DrawPoint(FObject& obj_);
	void DrawTriangle(FObject& obj_, CS_FrameBuffer& texture);
};

#endif
