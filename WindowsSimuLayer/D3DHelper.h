#ifndef __CSBF_WindowsSimuLayer_D3DHelper__
#define __CSBF_WindowsSimuLayer_D3DHelper__

#include <d3d9.h>
#include "../CrossBufferLayer/FrameBuffer.h"


class WSL_D3DHelper {
public:
	IDirect3D9* pDirect3D;
	IDirect3DDevice9* pDevice;
	IDirect3DSurface9* pBackBuffer;
	D3DLOCKED_RECT rect;

	WSL_D3DHelper();
	WSL_D3DHelper(HWND& hWnd);
	void LockBuffer();
	void UnlockBuffer();
	void PaintFrameBufferHere(const CS_FrameBuffer& fb);
	void Release();
};

#endif
