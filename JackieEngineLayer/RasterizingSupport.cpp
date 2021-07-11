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

void FRasterizer::DrawTriangle(const FVector4D& v0_, const FVector4D& v1_, const FVector4D& v2_, ui8 r, ui8 g, ui8 b){
	// Sort Y Order
	FVector4D *v0 = (FVector4D*)&v0_;
	FVector4D *v1 = (FVector4D*)&v1_;
	FVector4D *v2 = (FVector4D*)&v2_;
	if(v0->y > v1->y) swap(v0, v1);
	if(v0->y > v2->y) swap(v0, v2);
	if(v1->y > v2->y) swap(v1, v2);

	if(v1->y == v2->y){
		// ptrfb->PrintLn("Flat Bottom Triangle");
		if(v1->x > v2->x) swap(v1, v2);
		DrawFlatBottomTriangle(
			v0->y, v2->y, v0->x, v1->x, v2->x, r, g, b
		);
		return;
	}

	if(v0->y == v1->y){
		// ptrfb->PrintLn("Flat Top Triangle");
		if(v0->x > v1->x) swap(v0, v1);
		DrawFlatTopTriangle(
			v0->y, v2->y, v0->x, v1->x, v2->x, r, g, b
		);
		return;
	}

	f32 m = v1->y - v0->y;
	f32 n = v2->y - v0->y;
	FVector4D vcenter = v0->InterpolateTo(*v2, m / n);
	
	if(vcenter.x < v1->x){
		// ptrfb->PrintLn("Longside Left Triangle");
		DrawFlatBottomTriangle(
			v0->y, v1->y,
			v0->x, vcenter.x, v1->x,
			r, g, b
		);
		DrawFlatTopTriangle(
			v1->y, v2->y,
			vcenter.x, v1->x, v2->x,
			r, g, b
		);
	}

	else{
		// ptrfb->PrintLn("Longside Right Triangle");
		DrawFlatBottomTriangle(
			v0->y, v1->y,
			v0->x, v1->x, vcenter.x,
			r, g, b
		);
		DrawFlatTopTriangle(
			v1->y, v2->y,
			v1->x, vcenter.x, v2->x,
			r, g, b
		);
	}

}

void FRasterizer::DrawFlatBottomTriangle(f32 yStart, f32 yEnd, f32 x0_, f32 x1_, f32 x2_, ui8 r, ui8 g, ui8 b){
	i32 ys = (i32)ceil(yStart - 0.5f);
	i32 ye = (i32)ceil(yEnd   - 0.5f);

	f32 xStartStep = (x1_ - x0_) / (yEnd - yStart);
	f32 xEndStep   = (x2_ - x0_) / (yEnd - yStart);

	f32 xStart = x0_;
	f32 xEnd   = x0_;

	// Pre-steping
	xStart += ((float)ys - 0.5f - yStart) * xStartStep;
	xEnd   += ((float)ys - 0.5f - yStart) * xEndStep;

	for(i32 y = ys; y < ye; y++){
		xStart += xStartStep;
		xEnd   += xEndStep;

		i32 xs = (i32)ceil(xStart - 0.5f);
		i32 xe = (i32)ceil(xEnd   - 0.5f);

		for(i32 x = xs; x < xe; x++){
			CS_PutPixel(*ptrfb, x, y, r, g, b);
		}
	}
}

void FRasterizer::DrawFlatTopTriangle(f32 yStart, f32 yEnd, f32 x0_, f32 x1_, f32 x2_, ui8 r, ui8 g, ui8 b){
	i32 ys = (i32)ceil(yStart - 0.5f);
	i32 ye = (i32)ceil(yEnd   - 0.5f);

	f32 xStartStep = (x2_ - x0_) / (yEnd - yStart);
	f32 xEndStep   = (x2_ - x1_) / (yEnd - yStart);

	f32 xStart = x0_;
	f32 xEnd   = x1_;

	// Pre-steping
	xStart += ((float)ys - 0.5f - yStart) * xStartStep;
	xEnd   += ((float)ys - 0.5f - yStart) * xEndStep;

	for(i32 y = ys; y < ye; y++){
		xStart += xStartStep;
		xEnd   += xEndStep;

		i32 xs = (i32)ceil(xStart - 0.5f);
		i32 xe = (i32)ceil(xEnd   - 0.5f);

		for(i32 x = xs; x < xe; x++){
			CS_PutPixel(*ptrfb, x, y, r, g, b);
		}
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

void FRasterizer::DrawTriangle(FObject& obj_){
	for(ui32 i = 0; i < obj_.il.size(); i+=3){
		DrawTriangle(
			obj_.tmpVl[ obj_.il[i    ] ].pos,
			obj_.tmpVl[ obj_.il[i + 1] ].pos,
			obj_.tmpVl[ obj_.il[i + 2] ].pos,
			255, 255, 255
		);
	}
}
