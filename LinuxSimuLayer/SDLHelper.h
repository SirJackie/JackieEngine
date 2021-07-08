#ifndef __CSBF_LinuxSimuLayer_SDLHelper__
#define __CSBF_LinuxSimuLayer_SDLHelper__

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <math.h>

// Support iotcl()
#include <unistd.h>        /* System V */
#include <sys/ioctl.h>     /* BSD and Linux */
#include <stropts.h>       /* XSI STREAMS */

#include "../CrossBufferLayer/CrossBuffer.h"


class LSL_SDLHelper{
public:
    i32 screenWidth;
	i32 screenHeight;
	i32 unit;
	i32 windowWidth;
	i32 windowHeight;
	i32 leftMargin;
	i32 topMargin;

    SDL_Window* window;
    SDL_Surface* screenSurface;
    
    LSL_SDLHelper();
    void GetResolution();
    void CreateWindow(const i32* title);
    void Maximize();
    void Minimize();

    i32 getWcharLen(const i32* wcharPtr);
    char* wchar2char(const i32* wcharPtr);
    SDL_Surface* LoadMedia(const i8* bmpAddress);
    void ReleaseMedia(SDL_Surface* media);
    void Close();
    void BlitSurfaceHere(SDL_Surface* from);
    void LockSurface();
    void UnlockSurface();
    void PaintFrameBufferHere(CS_FrameBuffer& fb);
};

#endif
