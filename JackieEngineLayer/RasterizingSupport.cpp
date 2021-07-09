#include "RasterizingSupport.h"

FRasterizer::FRasterizer()
{
	ptrfb = csNullPtr;
}

FRasterizer::FRasterizer(CS_FrameBuffer& fb)
{
	ptrfb = &fb;
}

void FRasterizer::DrawPoint(FObject& obj)
{
	for (ui32 i = 0; i < obj.tmpVl.size(); i++) {
		CS_PutPixel
		(
			*ptrfb, (i32)obj.tmpVl[i].x, (i32)obj.tmpVl[i].y,
			255, 255, 255
		);
	}
}
