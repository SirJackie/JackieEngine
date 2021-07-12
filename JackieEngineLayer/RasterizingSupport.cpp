#include "RasterizingSupport.h"

FRasterizer::FRasterizer(){
	ptrfb = csNullPtr;
}

FRasterizer::FRasterizer(CS_FrameBuffer& fb_){
	ptrfb = &fb_;
}

void FRasterizer::DrawProtectedCube(i32 x0, i32 y0, i32 x1, i32 y1, ui8 r_, ui8 g_, ui8 b_){
	i32 width  = ptrfb->width;
	i32 height = ptrfb->height;

	x0 = CS_iclamp(0, x0, width);
	x1 = CS_iclamp(x0, x1, width);

	y0 = CS_iclamp(0, y0, height);
	y1 = CS_iclamp(y0, y1, height);

	for(i32 y = y0; y < y1; y++){
		ui8*  rEnd = (ui8*)(ptrfb->redBuffer   + y * width + x1);
		ui8*  gEnd = (ui8*)(ptrfb->greenBuffer + y * width + x1);
		ui8*  bEnd = (ui8*)(ptrfb->blueBuffer  + y * width + x1);
		for(
			ui8 *r = (ui8*)(ptrfb->redBuffer   + y * width + x0),
			    *g = (ui8*)(ptrfb->greenBuffer + y * width + x0),
			    *b = (ui8*)(ptrfb->blueBuffer  + y * width + x0);
			r<rEnd;
			r++ && g++ && b++ 
		){
			*r = r_;
			*g = g_;
			*b = b_;
		}
	}	
}

void FRasterizer::DrawRadiusCube(i32 x, i32 y, i32 radius){
	DrawProtectedCube(
		x - radius, y - radius,
		x + radius, y + radius,
		255, 255, 255
	);
}

void FRasterizer::DrawTriangle(const FVectorTex& v0_, const FVectorTex& v1_, const FVectorTex& v2_, CS_FrameBuffer& texture){
	// Sort Y Order
	FVectorTex *v0 = (FVectorTex*)&v0_;
	FVectorTex *v1 = (FVectorTex*)&v1_;
	FVectorTex *v2 = (FVectorTex*)&v2_;
	if(v0->pos.y > v1->pos.y) swap(v0, v1);
	if(v0->pos.y > v2->pos.y) swap(v0, v2);
	if(v1->pos.y > v2->pos.y) swap(v1, v2);

	if(v1->pos.y == v2->pos.y){
		// ptrfb->PrintLn("Flat Bottom Triangle");
		if(v1->pos.x > v2->pos.x) swap(v1, v2);
		DrawFlatBottomTriangle(
			*v0, *v1, *v2,
			texture
		);
		return;
	}

	if(v0->pos.y == v1->pos.y){
		// ptrfb->PrintLn("Flat Top Triangle");
		if(v0->pos.x > v1->pos.x) swap(v0, v1);
		DrawFlatTopTriangle(
			*v0, *v1, *v2,
			texture
		);
		return;
	}

	f32 m = v1->pos.y - v0->pos.y;
	f32 n = v2->pos.y - v0->pos.y;
	FVectorTex vcenter = v0->InterpolateTo(*v2, m / n);
	
	if(vcenter.pos.x < v1->pos.x){
		// ptrfb->PrintLn("Longside Left Triangle");
		DrawFlatBottomTriangle(
			*v0, vcenter, *v1,
			texture
		);
		DrawFlatTopTriangle(
			vcenter, *v1, *v2,
			texture
		);
	}

	else{
		// ptrfb->PrintLn("Longside Right Triangle");
		DrawFlatBottomTriangle(
			*v0, *v1, vcenter,
			texture
		);
		DrawFlatTopTriangle(
			*v1, vcenter, *v2,
			texture
		);
	}

}

void FRasterizer::DrawFlatBottomTriangle(const FVectorTex& v0_, const FVectorTex& v1_, const FVectorTex& v2_, CS_FrameBuffer& texture){
	f32 yTop    = v0_.pos.y;
	f32 yBottom = v2_.pos.y;

	FVectorTex xLeftStep  = (v1_ - v0_) / (yBottom - yTop);
	FVectorTex xRightStep = (v2_ - v0_) / (yBottom - yTop);

	FVectorTex xLeft  = v0_;
	FVectorTex xRight = v0_;

	// Pre-steping
	xLeft  = xLeft  + (ceil(yTop - 0.5f) + 0.5f - yTop) * xLeftStep;
	xRight = xRight + (ceil(yTop - 0.5f) + 0.5f - yTop) * xRightStep;

	for(i32 y = ceil(yTop - 0.5f); y < ceil(yBottom - 0.5f); y++){

		FVectorTex xNowStep = (xRight - xLeft) / (xRight.pos.x - xLeft.pos.x);
		FVectorTex xNow     = xLeft;
		xNow = xNow + (ceil(xLeft.pos.x - 0.5f) + 0.5f - xLeft.pos.x) * xNowStep; // Pre-stepping

		for(i32 x = ceil(xLeft.pos.x - 0.5f); x < ceil(xRight.pos.x); x++){
			CS_PutPixel(
				*ptrfb, xNow.pos.x, xNow.pos.y,
				texture.redBuffer[(i32)xNow.tex.y * texture.width + (i32)xNow.tex.x],
				texture.greenBuffer[(i32)xNow.tex.y * texture.width + (i32)xNow.tex.x],
				texture.blueBuffer[(i32)xNow.tex.y * texture.width + (i32)xNow.tex.x]
			);

			xNow = xNow + xNowStep;
		}
		
		xLeft  = xLeft  + xLeftStep;
		xRight = xRight + xRightStep;
	}
}

void FRasterizer::DrawFlatTopTriangle(const FVectorTex& v0_, const FVectorTex& v1_, const FVectorTex& v2_, CS_FrameBuffer& texture){
	f32 yTop    = v0_.pos.y;
	f32 yBottom = v2_.pos.y;

	FVectorTex xLeftStep  = (v2_ - v0_) / (yBottom - yTop);
	FVectorTex xRightStep = (v2_ - v1_) / (yBottom - yTop);

	FVectorTex xLeft  = v0_;
	FVectorTex xRight = v1_;

	// Pre-steping
	xLeft  = xLeft  + (ceil(yTop - 0.5f) + 0.5f - yTop) * xLeftStep;
	xRight = xRight + (ceil(yTop - 0.5f) + 0.5f - yTop) * xRightStep;

	for(i32 y = ceil(yTop - 0.5f); y < ceil(yBottom - 0.5f); y++){

		FVectorTex xNowStep = (xRight - xLeft) / (xRight.pos.x - xLeft.pos.x);
		FVectorTex xNow     = xLeft;
		xNow = xNow + (ceil(xLeft.pos.x - 0.5f) + 0.5f - xLeft.pos.x) * xNowStep; // Pre-stepping

		for(i32 x = ceil(xLeft.pos.x - 0.5f); x < ceil(xRight.pos.x); x++){
			CS_PutPixel(
				*ptrfb, xNow.pos.x, xNow.pos.y,
				texture.redBuffer[(i32)xNow.tex.y * texture.width + (i32)xNow.tex.x],
				texture.greenBuffer[(i32)xNow.tex.y * texture.width + (i32)xNow.tex.x],
				texture.blueBuffer[(i32)xNow.tex.y * texture.width + (i32)xNow.tex.x]
			);

			xNow = xNow + xNowStep;
		}
		
		xLeft  = xLeft  + xLeftStep;
		xRight = xRight + xRightStep;
	}
}

void FRasterizer::DrawFlatTriangle(i32 yStart, i32 yEnd, FVectorTex xLeft, FVectorTex xRight, const FVectorTex& xLeftStep, const FVectorTex& xRightStep)
{
	;
}

void FRasterizer::Draw3DPoint(FVector3D& point){
	DrawRadiusCube(point.x, point.y, 5);
}

void FRasterizer::Draw4DPoint(FVector4D& point){
	DrawRadiusCube(
		point.x, point.y,
		(1.0f + point.z) * 200.0f
	);
}

void FRasterizer::DrawPoint(FObject& obj_)
{
	for (ui32 i = 0; i < obj_.tmpVl.size(); i++) {
		Draw4DPoint(obj_.tmpVl[i].pos);
	}
}

void FRasterizer::DrawTriangle(FObject& obj_, CS_FrameBuffer& texture){
	for(ui32 i = 0; i < obj_.il.size(); i+=3){
		DrawTriangle(
			obj_.tmpVl[ obj_.il[i    ] ],
			obj_.tmpVl[ obj_.il[i + 1] ],
			obj_.tmpVl[ obj_.il[i + 2] ],
			texture
		);
	}
}
