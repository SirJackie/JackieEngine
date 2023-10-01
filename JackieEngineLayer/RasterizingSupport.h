#ifndef __JKEG_RasterizingSupport__
#define __JKEG_RasterizingSupport__

#include "../CrossBufferLayer/BasicDataTypeDeclarations.h"
#include "../CrossBufferLayer/CrossBuffer.h"
#include "MathSupport.h"
#include "ObjectSupport.h"


class FZBuffer {
public:
	f32 *bufptr;
	i32  width;
	i32  height;

	void Alloc();
	void FillBuffer();
	void Resize(i32 width_, i32 height_);

	FZBuffer();
	FZBuffer(const FZBuffer& zb);
	FZBuffer& operator=(const FZBuffer& zb);
	~FZBuffer();
};


class FRasterizer {
public:
	CS_FrameBuffer* ptrfb;
	FZBuffer zb;

	FRasterizer();
	FRasterizer(CS_FrameBuffer& fb_);
	FRasterizer(const FRasterizer& rst);
	FRasterizer& operator=(const FRasterizer& rst);
	~FRasterizer();

	void DrawProtectedCube(i32 x0, i32 y0, i32 x1, i32 y1, ui8 r_, ui8 g_, ui8 b_);
	void DrawRadiusCube(i32 x, i32 y, i32 radius);
	void DrawTriangle           (const FVectorTex& v0_, const FVectorTex& v1_, const FVectorTex& v2_, CS_FrameBuffer& texture);
	void DrawFlatBottomTriangle (const FVectorTex& v0_, const FVectorTex& v1_, const FVectorTex& v2_, CS_FrameBuffer& texture);
	void DrawFlatTopTriangle    (const FVectorTex& v0_, const FVectorTex& v1_, const FVectorTex& v2_, CS_FrameBuffer& texture);
	void DrawFlatTriangle       (i32 yTop, i32 yBottom, FVectorTex xLeft, FVectorTex xRight, const FVectorTex& xLeftStep, const FVectorTex& xRightStep, CS_FrameBuffer& texture);

	void Draw3DPoint(FVector3D& point);
	void Draw4DPoint(FVector4D& point);
	void DrawPoint(FObject& obj_);
	void DrawTriangle(FObject& obj_);
};

#endif
