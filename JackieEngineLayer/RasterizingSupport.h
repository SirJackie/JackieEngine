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
	FRasterizer(CS_FrameBuffer& fb);
	void DrawPoint(FObject4D& obj);
};

#endif
