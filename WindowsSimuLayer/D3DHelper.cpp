#include "D3DHelper.h"

WSL_D3DHelper::WSL_D3DHelper()
{
	pDirect3D   = csNullPtr;
	pDevice     = csNullPtr;
	pBackBuffer = csNullPtr;
	rect = {0, nullptr};
}

WSL_D3DHelper::WSL_D3DHelper(HWND& hWnd)
{
	// Initialize Direct3D Objects
	pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	pDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE,
		&d3dpp, &pDevice
	);

	pDevice = pDevice;
	pBackBuffer = csNullPtr;
	rect = { 0, nullptr };
}

void WSL_D3DHelper::LockBuffer()
{
	pDevice->Clear(
		0, NULL, D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0, 0, 0), 0.0f, 0
	);
	pBackBuffer = NULL;
	pDevice->GetBackBuffer(
		0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer
	);
	pBackBuffer->LockRect(&rect, NULL, NULL);
}

void WSL_D3DHelper::UnlockBuffer()
{
	pBackBuffer->UnlockRect();
	pBackBuffer->Release();
	pDevice->Present(NULL, NULL, NULL, NULL);
}

void WSL_D3DHelper::PaintFrameBufferHere(CS_FrameBuffer& fb)
{
	i32  bufferPitch = (rect.Pitch) >> 2;
	int realScreenWidth = fb.width * HIGH_DPI_SCALING_FACTOR;
	int lineUpDelta = bufferPitch - realScreenWidth;  // for lining-up when screenWidth < bufferPitch, not really creating new line.
	int hdsfMinusOne = HIGH_DPI_SCALING_FACTOR - 1;

	for (int iLine = 0; iLine < HIGH_DPI_SCALING_FACTOR; iLine++) {

		// DPI Scaling
		// #1 to #n pixel in #ii line
		i32* pBitsNow = (i32*)(rect.pBits);
		ui8* pRed = fb.redBuffer;
		ui8* pGreen = fb.greenBuffer;
		ui8* pBlue = fb.blueBuffer;

		for (int iSkip = 0; iSkip < iLine; iSkip++) {
			pBitsNow += realScreenWidth;  // skip ii line first, which mutally complementary with preceding lines
			pBitsNow += lineUpDelta;      // for lining-up when screenWidth < bufferPitch, not really creating new line.
		}

		for (i32 y = 0; y < fb.height; y++) {
			for (i32 x = 0; x < fb.width; x++) {

				for (int iiii = 0; iiii < HIGH_DPI_SCALING_FACTOR; iiii++){
					// #n pixel
					*pBitsNow =
						(i32)
						(
							(0xff << 24) |
							(((*pRed) & 0xff) << 16) |
							(((*pGreen) & 0xff) << 8) |
							((*pBlue) & 0xff)
						);
					pBitsNow++;
				}

				pRed++;
				pGreen++;
				pBlue++;
			}
			pBitsNow += lineUpDelta;      // for lining-up when screenWidth < bufferPitch, not really creating new line.
			
			for (int iSkip = 0; iSkip < hdsfMinusOne; iSkip++) {
				pBitsNow += realScreenWidth;  // skip ii line first, which mutally complementary with preceding lines
				pBitsNow += lineUpDelta;      // for lining-up when screenWidth < bufferPitch, not really creating new line.
			}
		}
	}
}

void WSL_D3DHelper::Release()
{
	if (pDevice)
	{
		pDevice->Release();
		pDevice = NULL;
	}
	if (pDirect3D)
	{
		pDirect3D->Release();
		pDirect3D = NULL;
	}
}
