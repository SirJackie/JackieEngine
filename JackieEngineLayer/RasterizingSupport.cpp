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
	const f32& yTop    = v0_.pos.y;
	const f32& yBottom = v2_.pos.y;

	FVectorTex xLeftStep  = (v1_ - v0_) / (yBottom - yTop);
	FVectorTex xRightStep = (v2_ - v0_) / (yBottom - yTop);

	DrawFlatTriangle(
		ceil(yTop - 0.5f),
		ceil(yBottom - 0.5f),
		v0_ + (ceil(yTop - 0.5f) + 0.5f - yTop) * xLeftStep,   // xLeft  with Pre-stepping
		v0_ + (ceil(yTop - 0.5f) + 0.5f - yTop) * xRightStep,  // xRight with Pre-stepping
		xLeftStep,
		xRightStep,
		texture
	);
}

void FRasterizer::DrawFlatTopTriangle(const FVectorTex& v0_, const FVectorTex& v1_, const FVectorTex& v2_, CS_FrameBuffer& texture){
	const f32& yTop    = v0_.pos.y;
	const f32& yBottom = v2_.pos.y;

	FVectorTex xLeftStep  = (v2_ - v0_) / (yBottom - yTop);
	FVectorTex xRightStep = (v2_ - v1_) / (yBottom - yTop);

	DrawFlatTriangle(
		ceil(yTop - 0.5f),
		ceil(yBottom - 0.5f),
		v0_ + (ceil(yTop - 0.5f) + 0.5f - yTop) * xLeftStep,   // xLeft  with Pre-stepping
		v1_ + (ceil(yTop - 0.5f) + 0.5f - yTop) * xRightStep,  // xRight with Pre-stepping
		xLeftStep,
		xRightStep,
		texture
	);
}

void FRasterizer::DrawFlatTriangle(i32 yTop, i32 yBottom, FVectorTex xLeft, FVectorTex xRight, const FVectorTex& xLeftStep, const FVectorTex& xRightStep, CS_FrameBuffer& texture)
{
	for (i32 y = yTop; y < yBottom; y++) {

		i32 xLeftInt  = ceil(xLeft.pos.x  - 0.5f);
		i32 xRightInt = ceil(xRight.pos.x - 0.5f);

		FVectorTex xNowStep = (xRight - xLeft) / (xRight.pos.x - xLeft.pos.x);
		FVectorTex xNow = xLeft;
		xNow = xNow + ((float)xLeftInt + 0.5f - xLeft.pos.x) * xNowStep;  // Pre-stepping

		for (i32 x = xLeftInt; x < xRightInt; x++) {
			i32 position = CS_iclamp(0, xNow.tex.y * texture.width,  texture.height - 1) *
						   texture.width +
						   CS_iclamp(0, xNow.tex.x * texture.height, texture.width  - 1);

			CS_PutPixel(
				*ptrfb, xNow.pos.x, xNow.pos.y,
				texture.redBuffer   [position],
				texture.greenBuffer [position],
				texture.blueBuffer  [position]
			);

			xNow += xNowStep;
		}

		xLeft += xLeftStep;
		xRight += xRightStep;
	}
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
		
		FVectorTex& v0 = obj_.tmpVl[obj_.il[i    ]];
		FVectorTex& v1 = obj_.tmpVl[obj_.il[i + 1]];
		FVectorTex& v2 = obj_.tmpVl[obj_.il[i + 2]];

		if (((v1 - v0).pos % (v2 - v0).pos * v0.pos) > 0.0f) {
			// Passed the Back Face Culling, Draw this triangle
			DrawTriangle(
				v0,
				v1,
				v2,
				texture
			);
		}
	}
}
