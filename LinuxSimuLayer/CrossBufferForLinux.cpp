#include <stdio.h>
#include "SDLHelper.h"
#include "KeyboardHelper.h"
#include <SDL.h>
#include <stdlib.h>
#include <time.h>
#include "../Main.h"

// LinuxSimuLayer Variables and Declarations
LSL_SDLHelper       sdlHelper;
LSL_KeyboardHelper  keyboardHelper;
CS_Mouse            mouse;
bool quit = csFalse;
SDL_Event e;

// CrossBufferLayer Variables
CS_FrameBuffer fb;

// Time Counting Variables
csbool FirstTimeRunning = csTrue;
clock_t lastTime;
clock_t thisTime;

csbool lBtnState = csFalse, mBtnState = csFalse, rBtnState = csFalse;

csbool lastFrameInfinityState = csFalse;


/*
** Main Function
*/

int main( int argc, char* args[] )
{
    sdlHelper.CreateWindow(WindowTitle);

    i32 GlobalCenterX = sdlHelper.leftMargin + (sdlHelper.windowWidth  / 2);
    i32 GlobalCenterY = sdlHelper.topMargin  + (sdlHelper.windowHeight / 2);

    mouse = CS_Mouse(sdlHelper.windowWidth, sdlHelper.windowHeight);

    // While it's not the time to quit
    while(!quit)
    {
        SDL_ShowCursor(!mouse.infinityMode);

        if(mouse.x == 0 || mouse.y == 0){
            i32 tmpx, tmpy;
            SDL_GetGlobalMouseState(&tmpx, &tmpy);
            tmpx -= sdlHelper.leftMargin;
            tmpy -= sdlHelper.topMargin;
            mouse.x = tmpx;
            mouse.y = tmpy;
            mouse.lastX = mouse.x;
            mouse.lastY = mouse.y;
        }

        if(lastFrameInfinityState == csFalse && mouse.infinityMode == csTrue){
            // Make the next frame mouse.x|y equals to this frame
            SDL_WarpMouseGlobal(GlobalCenterX, GlobalCenterY);

            lastFrameInfinityState = csTrue;
        }

        else if(lastFrameInfinityState == csTrue && mouse.infinityMode == csFalse){
            SDL_WarpMouseInWindow
            (
                sdlHelper.window,
                CS_iclamp(0, mouse.x, sdlHelper.windowWidth),
                CS_iclamp(0, mouse.y, sdlHelper.windowHeight)
            );
            lastFrameInfinityState = csFalse;
        }

        else if(lastFrameInfinityState == csTrue &&mouse.infinityMode == csTrue){
            i32 tmpx, tmpy;
            SDL_GetGlobalMouseState(&tmpx, &tmpy);

            mouse.x += tmpx - GlobalCenterX;
            mouse.y += tmpy - GlobalCenterY;

            SDL_WarpMouseGlobal(GlobalCenterX, GlobalCenterY);
        }

        /* Process the Message Queue */
        while(SDL_PollEvent(&e) != 0)
        {

            // If exit
            if(e.type == SDL_QUIT)
            {
                SDL_ShowCursor(csTrue);
                quit = csTrue;
            }

            // If key pressed
            if(e.type == SDL_KEYDOWN)
            {
                int keycode = e.key.keysym.sym;
                if(keycode > 1073740000) keycode -= 1073740000;
                keyboardHelper.linuxKeyBuffer[keycode] = 1;
            }
            
            // If key released
            if(e.type == SDL_KEYUP){
                int keycode = e.key.keysym.sym;
                if(keycode > 1073740000) keycode -= 1073740000;
                keyboardHelper.linuxKeyBuffer[keycode] = 0;
            }

            // If mouse moved
            else if (SDL_MOUSEMOTION == e.type)
			{
                if(mouse.infinityMode == csFalse){
                    mouse.x = e.motion.x;
				    mouse.y = e.motion.y;
                }
            }

            if (SDL_MOUSEBUTTONDOWN == e.type) 
            {
                if(SDL_BUTTON_LEFT == e.button.button)
                {
                    mouse.lBtnState = csTrue;
                }
                else if(SDL_BUTTON_MIDDLE == e.button.button)
                {
                    mouse.mBtnState = csTrue;
                }
                else if(SDL_BUTTON_RIGHT == e.button.button)
                {
                    mouse.rBtnState = csTrue;
                }
            }

            if (SDL_MOUSEBUTTONUP == e.type) 
            {
                if(SDL_BUTTON_LEFT == e.button.button)
                {
                    mouse.lBtnState = csFalse;
                }
                else if(SDL_BUTTON_MIDDLE == e.button.button)
                {
                    mouse.mBtnState = csFalse;
                }
                else if(SDL_BUTTON_RIGHT == e.button.button)
                {
                    mouse.rBtnState = csFalse;
                }
            }
            
        }

        /* Process our Game Loop */
        // Update Time Counting Variables
        thisTime = clock();

        // Lock Surface
        sdlHelper.LockSurface();

        fb = CS_FrameBuffer
        (
            sdlHelper.windowWidth, sdlHelper.windowHeight
        );

        // Update Keyboard Status when there is or isn't message
        keyboardHelper.MoveLnxBufIntoKeyBuf();

        if(keyboardHelper.kb.IsKeyPressed(CSK_Esc)){
            quit = csTrue;
        }

        mouse.deltaX = mouse.x - mouse.lastX;
        mouse.deltaY = mouse.y - mouse.lastY;

        // If it is the First Time Running
        if (FirstTimeRunning) {
            Setup (fb, keyboardHelper.kb, mouse, 0);                     // Call the Setup()  in Main.h
            FirstTimeRunning = csFalse;
        }

        // If it is not the First Time Running
        else {
            Update(fb, keyboardHelper.kb, mouse, (thisTime - lastTime) / 1000);  // Call the Update() in Main.h
        }

        // Paint FrameBuffer on SDL Surface
        sdlHelper.PaintFrameBufferHere(fb);

        // Unlock Surface
        sdlHelper.UnlockSurface();

        // Update Time Counting Variables
        // lastTime in next frame = thisTime in this frame
        lastTime = thisTime;

        // Update Mouse Delta Counting Variables
        // lastX in next frame = x in this frame
        mouse.lastX = mouse.x;
        mouse.lastY = mouse.y;
    }

    // After Main Loop
    sdlHelper.Close();

    return 0;
}