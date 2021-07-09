#include "RasterizingSupport.h"

FRasterizer::FRasterizer(){
	ptrfb = csNullPtr;
}

FRasterizer::FRasterizer(CS_FrameBuffer& fb_){
	ptrfb = &fb_;
}

void FRasterizer::DrawPoint(FObject& obj_)
{
	for (ui32 i = 0; i < obj_.tmpVl.size(); i++) {
		CS_PutPixel
		(
			*ptrfb, (i32)obj_.tmpVl[i].x, (i32)obj_.tmpVl[i].y,
			255, 255, 255
		);
	}
}
