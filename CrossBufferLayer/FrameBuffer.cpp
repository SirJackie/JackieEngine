#include "FrameBuffer.h"
#include <vector>
using std::vector;

int clamp(int min, int x, int max) {
	int result = x;

	if (min > result) {
		result = min;
	}

	if (max < result) {
		result = max;
	}

	return result;
}

void FrameBuffer::AllocateBuffer(int width, int height) {
	Width        = width  > 1 ? width  : 1;
	Height       = height > 1 ? height : 1;
	Pitch        = Width;
	pBits        = new Color[Pitch * Height];
	externalBits = false;
}

void FrameBuffer::DisAllocateBuffer() {
	if (externalBits == true) {
		;                // Do Nothing
	}
	else {
		delete[] pBits;  // Release the buffer
	}
}

void FrameBuffer::ClearBuffer() {
	// Clear the buffer
	for (int y = 0; y < Height - 1; y++) {
		for (int x = 0; x < Width - 1; x++) {
			SetPixel((*this), x, y, CreateColor(0, 0, 0));
		}
	}
}

void FrameBuffer::InitCursor() {
	InitCurX = CurX = INIT_CUR_X < (Width  - TEXT_WIDTH ) ? INIT_CUR_X : 0;
	InitCurY = CurY = INIT_CUR_Y < (Height - TEXT_HEIGHT) ? INIT_CUR_Y : 0;
}

FrameBuffer::FrameBuffer() {
	AllocateBuffer(1, 1);
	ClearBuffer();
	InitCursor();
	wannaLoadBitmap = false;
}

FrameBuffer::FrameBuffer(int Width_, int Height_) {
	AllocateBuffer(Width_, Height_);
	ClearBuffer();
	InitCursor();
	wannaLoadBitmap = false;
}

FrameBuffer::FrameBuffer(int Width_, int Height_, int Pitch_, Color* pBits_) {
	Width        = Width_  > 1 ? Width_  : 1;
	Height       = Height_ > 1 ? Height_ : 1;
	Pitch        = Pitch_;
	pBits        = pBits_;
	externalBits = true;
	// External Buffer should be cleared.
	InitCursor();
	wannaLoadBitmap = false;
}

FrameBuffer::FrameBuffer(const FrameBuffer& fb) {
	AllocateBuffer(fb.Width, fb.Height);
	DrawBuffer(fb, 0, 0);                 // Draw fb to this buffer
	InitCursor();
	wannaLoadBitmap = false;
}

void FrameBuffer::LoadBMP(string bitmapAddress_, vector<FrameBuffer*>& fbLoadingQueue) {
	this->wannaLoadBitmap = true;
	this->bitmapAddress = bitmapAddress_;
	fbLoadingQueue.push_back(this);
}

FrameBuffer& FrameBuffer::operator=(const FrameBuffer& fb) {
	DisAllocateBuffer();                  // Disallocate old buffer first
	AllocateBuffer(fb.Width, fb.Height);  // Then allocate a new one
	DrawBuffer(fb, 0, 0);                 // Draw fb to this buffer
	InitCursor();                         // Init Cursor
	wannaLoadBitmap = false;

	return (*this);                       // Support a = b = c
}

FrameBuffer::~FrameBuffer() {
	DisAllocateBuffer();
}

void FrameBuffer::DrawChar(int x, int y, Color color, char ch)
{
	int* bitmapPointer;
	for (int deltaY = 0; deltaY < 16; deltaY++) {
		bitmapPointer = (int*)(Font + ((int)ch * 16 * 8) + (8 * deltaY));
		if (bitmapPointer[0] == 255) { SetPixel((*this), (x + 0), (y + deltaY), color); }
		if (bitmapPointer[1] == 255) { SetPixel((*this), (x + 1), (y + deltaY), color); }
		if (bitmapPointer[2] == 255) { SetPixel((*this), (x + 2), (y + deltaY), color); }
		if (bitmapPointer[3] == 255) { SetPixel((*this), (x + 3), (y + deltaY), color); }
		if (bitmapPointer[4] == 255) { SetPixel((*this), (x + 4), (y + deltaY), color); }
		if (bitmapPointer[5] == 255) { SetPixel((*this), (x + 5), (y + deltaY), color); }
		if (bitmapPointer[6] == 255) { SetPixel((*this), (x + 6), (y + deltaY), color); }
		if (bitmapPointer[7] == 255) { SetPixel((*this), (x + 7), (y + deltaY), color); }
	}
}

void FrameBuffer::DrawString(Color color, const char* stringPointer)
{
	
	// Use a while loop to prevent the
	// Interlocking "CurX + TEXT_WIDTH > Width"
	// ----------------------------------------
	// This will only happens on the first time
	// checking, so the checking below will not
	// do this.
	bool XAvailableFlag = false;
	while (XAvailableFlag == false) {
		if (CurX + TEXT_WIDTH > Width) {
			CurY += TEXT_HEIGHT;
			CurX = InitCurX;
		}
		else {
			XAvailableFlag = true;
		}
		if (CurY + TEXT_HEIGHT > Height) {
			return;
		}
	}


	for (; *stringPointer != 0x00; stringPointer++) {

		// Before Drawing
		if (*stringPointer == '\n') {
			CurY += TEXT_HEIGHT;
			CurX = InitCurX;
			continue;
		}

		// Drawing
		int CurXMinusOne = CurX - 1;
		int CurYMinusOne = CurY - 1;
		int TmpX = CurXMinusOne > 0 ? CurXMinusOne : 0;
		int TmpY = CurYMinusOne > 0 ? CurYMinusOne : 0;

		this->DrawChar(CurX, CurY, color, *stringPointer);

		CurX += TEXT_WIDTH;

		// After

		if (CurX + TEXT_WIDTH > Width) {
			CurY += TEXT_HEIGHT;
			CurX = InitCurX;
		}

		if (CurY + TEXT_HEIGHT > Height) {
			return;
		}

	}
	return;
}

void FrameBuffer::DrawBuffer(const FrameBuffer& fb, int PositionX, int PositionY) {

	int StartX = clamp(0, PositionX, this->Width);
	int StartY = clamp(0, PositionY, this->Height);
	int EndX = clamp(0, PositionX + fb.Width, this->Width);
	int EndY = clamp(0, PositionY + fb.Height, this->Height);

	for (int y = StartY; y < EndY; y++) {
		for (int x = StartX; x < EndX; x++) {
			SetPixel(
				(*this), x, y,
				GetPixel(
					fb,
					x - PositionX,
					y - PositionY
				)
			);
		}
	}
}

void FrameBuffer::Draw(const char* stringPointer) {

	Color White = CreateColor(255, 255, 255);
	Color Black = CreateColor(0, 0, 0);

	// Use a while loop to prevent the
	// Interlocking "CurX + TEXT_WIDTH > Width"
	// ----------------------------------------
	// This will only happens on the first time
	// checking, so the checking below will not
	// do this.
	bool XAvailableFlag = false;
	while (XAvailableFlag == false) {
		if (CurX + TEXT_WIDTH > Width) {
			CurY += TEXT_HEIGHT;
			CurX = InitCurX;
		}
		else{
			XAvailableFlag = true;
		}
		if (CurY + TEXT_HEIGHT > Height) {
			return;
		}
	}
	

	for (; *stringPointer != 0x00; stringPointer++) {

		// Before Drawing
		if (*stringPointer == '\n') {
			CurY += TEXT_HEIGHT;
			CurX = InitCurX;
			continue;
		}

		// Drawing
		int CurXMinusOne = CurX - 1;
		int CurYMinusOne = CurY - 1;
		int TmpX = CurXMinusOne > 0 ? CurXMinusOne : 0;
		int TmpY = CurYMinusOne > 0 ? CurYMinusOne : 0;

		this->DrawChar(CurX, CurY, Black, *stringPointer);  // Draw Black Shadow
		this->DrawChar(TmpX, TmpY, White, *stringPointer);  // Draw White Cover

		CurX += TEXT_WIDTH;

		// After

		if (CurX + TEXT_WIDTH > Width) {
			CurY += TEXT_HEIGHT;
			CurX = InitCurX;
		}

		if (CurY + TEXT_HEIGHT > Height) {
			return;
		}

	}
	return;
}

void FrameBuffer::Draw(const FrameBuffer& fb) {
	CurX += 3;
	DrawBuffer(fb, CurX, CurY);
	CurY += fb.Height - 16;
	CurX += fb.Width  + 4;
}
