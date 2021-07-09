#include "KeyboardSupport.h"

CS_Keyboard::CS_Keyboard()
{
    for (i32 i = 0; i < 256; i++) {
        keyBuffer[i] = csFalse;
    }
}

csbool CS_Keyboard::IsKeyPressed(i8 key)
{
    return (keyBuffer[key] != csFalse);
}

csbool CS_Keyboard::IsKeyFirstTimePressed(i8 key)
{
    if (keyBuffer[key] == 1) {
        return csTrue;
    }
    else {
        return csFalse;
    }
}

void CS_Keyboard::SimuLayerSetKeyIsPressed(i8 key)
{
    keyBuffer[key] = csTrue;
}

void CS_Keyboard::SimuLayerSetKeyIsReleased(i8 key)
{
    keyBuffer[key] = csFalse;
}

void CS_Keyboard::SimuLayerSetKeyState(i8 key, csbool state)
{
    if (state == csTrue) {
        keyBuffer[key] += 1;
    }
    else {
        keyBuffer[key] = 0;
    }
}

string CS_Keyboard::ToString(){
    string str = "{";
    
    if(keyBuffer[CSK_Esc] != csFalse) str += "CSK_Esc, ";
    if(keyBuffer[CSK_F1] != csFalse) str += "CSK_F1, ";
    if(keyBuffer[CSK_F2] != csFalse) str += "CSK_F2, ";
    if(keyBuffer[CSK_F3] != csFalse) str += "CSK_F3, ";
    if(keyBuffer[CSK_F4] != csFalse) str += "CSK_F4, ";
    if(keyBuffer[CSK_F5] != csFalse) str += "CSK_F5, ";
    if(keyBuffer[CSK_F6] != csFalse) str += "CSK_F6, ";
    if(keyBuffer[CSK_F7] != csFalse) str += "CSK_F7, ";
    if(keyBuffer[CSK_F8] != csFalse) str += "CSK_F8, ";
    if(keyBuffer[CSK_F9] != csFalse) str += "CSK_F9, ";
    if(keyBuffer[CSK_F10] != csFalse) str += "CSK_F10, ";
    if(keyBuffer[CSK_F11] != csFalse) str += "CSK_F11, ";
    if(keyBuffer[CSK_F12] != csFalse) str += "CSK_F12, ";

    if(keyBuffer[CSK_BackQuote] != csFalse) str += "CSK_BackQuote, ";
    if(keyBuffer[CSK_Num1] != csFalse) str += "CSK_Num1, ";
    if(keyBuffer[CSK_Num2] != csFalse) str += "CSK_Num2, ";
    if(keyBuffer[CSK_Num3] != csFalse) str += "CSK_Num3, ";
    if(keyBuffer[CSK_Num4] != csFalse) str += "CSK_Num4, ";
    if(keyBuffer[CSK_Num5] != csFalse) str += "CSK_Num5, ";
    if(keyBuffer[CSK_Num6] != csFalse) str += "CSK_Num6, ";
    if(keyBuffer[CSK_Num7] != csFalse) str += "CSK_Num7, ";
    if(keyBuffer[CSK_Num8] != csFalse) str += "CSK_Num8, ";
    if(keyBuffer[CSK_Num9] != csFalse) str += "CSK_Num9, ";
    if(keyBuffer[CSK_Num0] != csFalse) str += "CSK_Num0, ";
    if(keyBuffer[CSK_Minus] != csFalse) str += "CSK_Minus, ";
    if(keyBuffer[CSK_Plus] != csFalse) str += "CSK_Plus, ";
    if(keyBuffer[CSK_Backspace] != csFalse) str += "CSK_Backspace, ";

    if(keyBuffer[CSK_Tab] != csFalse) str += "CSK_Tab, ";
    if(keyBuffer[CSK_Q] != csFalse) str += "CSK_Q, ";
    if(keyBuffer[CSK_W] != csFalse) str += "CSK_W, ";
    if(keyBuffer[CSK_E] != csFalse) str += "CSK_E, ";
    if(keyBuffer[CSK_R] != csFalse) str += "CSK_R, ";
    if(keyBuffer[CSK_T] != csFalse) str += "CSK_T, ";
    if(keyBuffer[CSK_Y] != csFalse) str += "CSK_Y, ";
    if(keyBuffer[CSK_U] != csFalse) str += "CSK_U, ";
    if(keyBuffer[CSK_I] != csFalse) str += "CSK_I, ";
    if(keyBuffer[CSK_O] != csFalse) str += "CSK_O, ";
    if(keyBuffer[CSK_P] != csFalse) str += "CSK_P, ";
    if(keyBuffer[CSK_LeftSquareBracket] != csFalse) str += "CSK_LeftSquareBracket, ";
    if(keyBuffer[CSK_RightSquareBracket] != csFalse) str += "CSK_RightSquareBracket, ";
    if(keyBuffer[CSK_BackSlash] != csFalse) str += "CSK_BackSlash, ";

    if(keyBuffer[CSK_CapsLock] != csFalse) str += "CSK_CapsLock, ";
    if(keyBuffer[CSK_A] != csFalse) str += "CSK_A, ";
    if(keyBuffer[CSK_S] != csFalse) str += "CSK_S, ";
    if(keyBuffer[CSK_D] != csFalse) str += "CSK_D, ";
    if(keyBuffer[CSK_F] != csFalse) str += "CSK_F, ";
    if(keyBuffer[CSK_G] != csFalse) str += "CSK_G, ";
    if(keyBuffer[CSK_H] != csFalse) str += "CSK_H, ";
    if(keyBuffer[CSK_J] != csFalse) str += "CSK_J, ";
    if(keyBuffer[CSK_K] != csFalse) str += "CSK_K, ";
    if(keyBuffer[CSK_L] != csFalse) str += "CSK_L, ";
    if(keyBuffer[CSK_Semicolon] != csFalse) str += "CSK_Semicolon, ";
    if(keyBuffer[CSK_Quote] != csFalse) str += "CSK_Quote, ";
    if(keyBuffer[CSK_Enter] != csFalse) str += "CSK_Enter, ";

    if(keyBuffer[CSK_Shift] != csFalse) str += "CSK_Shift, ";
    if(keyBuffer[CSK_Z] != csFalse) str += "CSK_Z, ";
    if(keyBuffer[CSK_X] != csFalse) str += "CSK_X, ";
    if(keyBuffer[CSK_C] != csFalse) str += "CSK_C, ";
    if(keyBuffer[CSK_V] != csFalse) str += "CSK_V, ";
    if(keyBuffer[CSK_B] != csFalse) str += "CSK_B, ";
    if(keyBuffer[CSK_N] != csFalse) str += "CSK_N, ";
    if(keyBuffer[CSK_M] != csFalse) str += "CSK_M, ";
    if(keyBuffer[CSK_Comma] != csFalse) str += "CSK_Comma, ";
    if(keyBuffer[CSK_FullStop] != csFalse) str += "CSK_FullStop, ";
    if(keyBuffer[CSK_Slash] != csFalse) str += "CSK_Slash, ";
    if(keyBuffer[CSK_RightShift] != csFalse) str += "CSK_RightShift, ";

    if(keyBuffer[CSK_Ctrl] != csFalse) str += "CSK_Ctrl, ";
    if(keyBuffer[CSK_Win] != csFalse) str += "CSK_Win, ";
    if(keyBuffer[CSK_Alt] != csFalse) str += "CSK_Alt, ";
    if(keyBuffer[CSK_Space] != csFalse) str += "CSK_Space, ";
    if(keyBuffer[CSK_RightAlt] != csFalse) str += "CSK_RightAlt, ";
    if(keyBuffer[CSK_RightCtrl] != csFalse) str += "CSK_RightCtrl, ";

    if(keyBuffer[CSK_Up] != csFalse) str += "CSK_Up, ";
    if(keyBuffer[CSK_Down] != csFalse) str += "CSK_Down, ";
    if(keyBuffer[CSK_Left] != csFalse) str += "CSK_Left, ";
    if(keyBuffer[CSK_Right] != csFalse) str += "CSK_Right, ";

    if(keyBuffer[CSK_Insert] != csFalse) str += "CSK_Insert, ";
    if(keyBuffer[CSK_Delete] != csFalse) str += "CSK_Delete, ";
    if(keyBuffer[CSK_Home] != csFalse) str += "CSK_Home, ";
    if(keyBuffer[CSK_End] != csFalse) str += "CSK_End, ";
    if(keyBuffer[CSK_PageUp] != csFalse) str += "CSK_PageUp, ";
    if(keyBuffer[CSK_PageDown] != csFalse) str += "CSK_PageDown, ";

    if(keyBuffer[CSK_PrintScreen] != csFalse) str += "CSK_PrintScreen, ";
    if(keyBuffer[CSK_ScrollLock] != csFalse) str += "CSK_ScrollLock, ";
    if(keyBuffer[CSK_PauseAndBreak] != csFalse) str += "CSK_PauseAndBreak, ";

    if(keyBuffer[CSK_Keypad0] != csFalse) str += "CSK_Keypad0, ";
    if(keyBuffer[CSK_Keypad1] != csFalse) str += "CSK_Keypad1, ";
    if(keyBuffer[CSK_Keypad2] != csFalse) str += "CSK_Keypad2, ";
    if(keyBuffer[CSK_Keypad3] != csFalse) str += "CSK_Keypad3, ";
    if(keyBuffer[CSK_Keypad4] != csFalse) str += "CSK_Keypad4, ";
    if(keyBuffer[CSK_Keypad5] != csFalse) str += "CSK_Keypad5, ";
    if(keyBuffer[CSK_Keypad6] != csFalse) str += "CSK_Keypad6, ";
    if(keyBuffer[CSK_Keypad7] != csFalse) str += "CSK_Keypad7, ";
    if(keyBuffer[CSK_Keypad8] != csFalse) str += "CSK_Keypad8, ";
    if(keyBuffer[CSK_Keypad9] != csFalse) str += "CSK_Keypad9, ";
    if(keyBuffer[CSK_KeypadDot] != csFalse) str += "CSK_KeypadDot, ";
    if(keyBuffer[CSK_KeypadNumLock] != csFalse) str += "CSK_KeypadNumLock, ";
    if(keyBuffer[CSK_KeypadEnter] != csFalse) str += "CSK_KeypadEnter, ";
    if(keyBuffer[CSK_KeypadAdd] != csFalse) str += "CSK_KeypadAdd, ";
    if(keyBuffer[CSK_KeypadMinus] != csFalse) str += "CSK_KeypadMinus, ";
    if(keyBuffer[CSK_KeypadMultiply] != csFalse) str += "CSK_KeypadMultiply, ";
    if(keyBuffer[CSK_KeypadDevide] != csFalse) str += "CSK_KeypadDevide, ";

    str += "}\n";
    return str;
}
