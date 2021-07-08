#include "KeyboardHelper.h"

WSL_KeyboardHelper::WSL_KeyboardHelper()
{
	CS_Memset(windowsKeyBuffer, 0, 256);
}

void WSL_KeyboardHelper::MoveWinBufIntoKeyBuf()
{
	kb.SimuLayerSetKeyState(CSK_Esc, windowsKeyBuffer[27]);
	kb.SimuLayerSetKeyState(CSK_F1, windowsKeyBuffer[112]);
	kb.SimuLayerSetKeyState(CSK_F2, windowsKeyBuffer[113]);
	kb.SimuLayerSetKeyState(CSK_F3, windowsKeyBuffer[114]);
	kb.SimuLayerSetKeyState(CSK_F4, windowsKeyBuffer[115]);
	kb.SimuLayerSetKeyState(CSK_F5, windowsKeyBuffer[116]);
	kb.SimuLayerSetKeyState(CSK_F6, windowsKeyBuffer[117]);
	kb.SimuLayerSetKeyState(CSK_F7, windowsKeyBuffer[118]);
	kb.SimuLayerSetKeyState(CSK_F8, windowsKeyBuffer[119]);
	kb.SimuLayerSetKeyState(CSK_F9, windowsKeyBuffer[120]);
	// kb.SimuLayerSetKeyState(CSK_F10, windowsKeyBuffer[26]);
	// kb.SimuLayerSetKeyState(CSK_F11, windowsKeyBuffer[28]);
	// kb.SimuLayerSetKeyState(CSK_F12, windowsKeyBuffer[29]);

	// kb.SimuLayerSetKeyState(CSK_BackQuote, windowsKeyBuffer[25]);
	kb.SimuLayerSetKeyState(CSK_Num1, windowsKeyBuffer[49]);
	kb.SimuLayerSetKeyState(CSK_Num2, windowsKeyBuffer[50]);
	kb.SimuLayerSetKeyState(CSK_Num3, windowsKeyBuffer[51]);
	kb.SimuLayerSetKeyState(CSK_Num4, windowsKeyBuffer[52]);
	kb.SimuLayerSetKeyState(CSK_Num5, windowsKeyBuffer[53]);
	kb.SimuLayerSetKeyState(CSK_Num6, windowsKeyBuffer[54]);
	kb.SimuLayerSetKeyState(CSK_Num7, windowsKeyBuffer[55]);
	kb.SimuLayerSetKeyState(CSK_Num8, windowsKeyBuffer[56]);
	kb.SimuLayerSetKeyState(CSK_Num9, windowsKeyBuffer[57]);
	kb.SimuLayerSetKeyState(CSK_Num0, windowsKeyBuffer[48]);
	// kb.SimuLayerSetKeyState(CSK_Minus, windowsKeyBuffer[10]);
	// kb.SimuLayerSetKeyState(CSK_Plus, windowsKeyBuffer[11]);
	kb.SimuLayerSetKeyState(CSK_Backspace, windowsKeyBuffer[8]);

	kb.SimuLayerSetKeyState(CSK_Tab, windowsKeyBuffer[9]);
	kb.SimuLayerSetKeyState(CSK_Q, windowsKeyBuffer[81]);
	kb.SimuLayerSetKeyState(CSK_W, windowsKeyBuffer[87]);
	kb.SimuLayerSetKeyState(CSK_E, windowsKeyBuffer[69]);
	kb.SimuLayerSetKeyState(CSK_R, windowsKeyBuffer[82]);
	kb.SimuLayerSetKeyState(CSK_T, windowsKeyBuffer[84]);
	kb.SimuLayerSetKeyState(CSK_Y, windowsKeyBuffer[89]);
	kb.SimuLayerSetKeyState(CSK_U, windowsKeyBuffer[85]);
	kb.SimuLayerSetKeyState(CSK_I, windowsKeyBuffer[73]);
	kb.SimuLayerSetKeyState(CSK_O, windowsKeyBuffer[79]);
	kb.SimuLayerSetKeyState(CSK_P, windowsKeyBuffer[80]);
	// kb.SimuLayerSetKeyState(CSK_LeftSquareBracket, windowsKeyBuffer[12]);
	// kb.SimuLayerSetKeyState(CSK_RightSquareBracket, windowsKeyBuffer[14]);
	// kb.SimuLayerSetKeyState(CSK_BackSlash, windowsKeyBuffer[15]);

	kb.SimuLayerSetKeyState(CSK_CapsLock, windowsKeyBuffer[20]);
	kb.SimuLayerSetKeyState(CSK_A, windowsKeyBuffer[65]);
	kb.SimuLayerSetKeyState(CSK_S, windowsKeyBuffer[83]);
	kb.SimuLayerSetKeyState(CSK_D, windowsKeyBuffer[68]);
	kb.SimuLayerSetKeyState(CSK_F, windowsKeyBuffer[70]);
	kb.SimuLayerSetKeyState(CSK_G, windowsKeyBuffer[71]);
	kb.SimuLayerSetKeyState(CSK_H, windowsKeyBuffer[72]);
	kb.SimuLayerSetKeyState(CSK_J, windowsKeyBuffer[74]);
	kb.SimuLayerSetKeyState(CSK_K, windowsKeyBuffer[75]);
	kb.SimuLayerSetKeyState(CSK_L, windowsKeyBuffer[76]);
	// kb.SimuLayerSetKeyState(CSK_Semicolon, windowsKeyBuffer[18]);
	// kb.SimuLayerSetKeyState(CSK_Quote, windowsKeyBuffer[21]);
	kb.SimuLayerSetKeyState(CSK_Enter, windowsKeyBuffer[13]);

	kb.SimuLayerSetKeyState(CSK_Shift, windowsKeyBuffer[16]);
	kb.SimuLayerSetKeyState(CSK_Z, windowsKeyBuffer[90]);
	kb.SimuLayerSetKeyState(CSK_X, windowsKeyBuffer[88]);
	kb.SimuLayerSetKeyState(CSK_C, windowsKeyBuffer[67]);
	kb.SimuLayerSetKeyState(CSK_V, windowsKeyBuffer[86]);
	kb.SimuLayerSetKeyState(CSK_B, windowsKeyBuffer[66]);
	kb.SimuLayerSetKeyState(CSK_N, windowsKeyBuffer[78]);
	kb.SimuLayerSetKeyState(CSK_M, windowsKeyBuffer[77]);
	// kb.SimuLayerSetKeyState(CSK_Comma, windowsKeyBuffer[22]);
	// kb.SimuLayerSetKeyState(CSK_FullStop, windowsKeyBuffer[23]);
	// kb.SimuLayerSetKeyState(CSK_Slash, windowsKeyBuffer[24]);
	// kb.SimuLayerSetKeyState(CSK_RightShift, windowsKeyBuffer[123]);

	kb.SimuLayerSetKeyState(CSK_Ctrl, windowsKeyBuffer[17]);
	kb.SimuLayerSetKeyState(CSK_Win, windowsKeyBuffer[91]);
	// kb.SimuLayerSetKeyState(CSK_Alt, windowsKeyBuffer[125]);
	kb.SimuLayerSetKeyState(CSK_Space, windowsKeyBuffer[32]);
	// kb.SimuLayerSetKeyState(CSK_RightAlt, windowsKeyBuffer[126]);
	// kb.SimuLayerSetKeyState(CSK_RightCtrl, windowsKeyBuffer[124]);

	kb.SimuLayerSetKeyState(CSK_Up, windowsKeyBuffer[38]);
	kb.SimuLayerSetKeyState(CSK_Down, windowsKeyBuffer[40]);
	kb.SimuLayerSetKeyState(CSK_Left, windowsKeyBuffer[37]);
	kb.SimuLayerSetKeyState(CSK_Right, windowsKeyBuffer[39]);

	kb.SimuLayerSetKeyState(CSK_Insert, windowsKeyBuffer[45]);
	kb.SimuLayerSetKeyState(CSK_Delete, windowsKeyBuffer[46]);
	kb.SimuLayerSetKeyState(CSK_Home, windowsKeyBuffer[36]);
	kb.SimuLayerSetKeyState(CSK_End, windowsKeyBuffer[35]);
	kb.SimuLayerSetKeyState(CSK_PageUp, windowsKeyBuffer[33]);
	kb.SimuLayerSetKeyState(CSK_PageDown, windowsKeyBuffer[34]);

	// kb.SimuLayerSetKeyState(CSK_PrintScreen, windowsKeyBuffer[30]);
	// kb.SimuLayerSetKeyState(CSK_ScrollLock, windowsKeyBuffer[31]);
	kb.SimuLayerSetKeyState(CSK_PauseAndBreak, windowsKeyBuffer[19]);

	kb.SimuLayerSetKeyState(CSK_Keypad0, windowsKeyBuffer[96]);
	kb.SimuLayerSetKeyState(CSK_Keypad1, windowsKeyBuffer[97]);
	kb.SimuLayerSetKeyState(CSK_Keypad2, windowsKeyBuffer[98]);
	kb.SimuLayerSetKeyState(CSK_Keypad3, windowsKeyBuffer[99]);
	kb.SimuLayerSetKeyState(CSK_Keypad4, windowsKeyBuffer[100]);
	kb.SimuLayerSetKeyState(CSK_Keypad5, windowsKeyBuffer[101]);
	kb.SimuLayerSetKeyState(CSK_Keypad6, windowsKeyBuffer[102]);
	kb.SimuLayerSetKeyState(CSK_Keypad7, windowsKeyBuffer[103]);
	kb.SimuLayerSetKeyState(CSK_Keypad8, windowsKeyBuffer[104]);
	kb.SimuLayerSetKeyState(CSK_Keypad9, windowsKeyBuffer[105]);
	kb.SimuLayerSetKeyState(CSK_KeypadDot, windowsKeyBuffer[110]);
	// kb.SimuLayerSetKeyState(CSK_KeypadNumLock, windowsKeyBuffer[122]);
	// kb.SimuLayerSetKeyState(CSK_KeypadEnter, windowsKeyBuffer[121]);
	kb.SimuLayerSetKeyState(CSK_KeypadAdd, windowsKeyBuffer[107]);
	kb.SimuLayerSetKeyState(CSK_KeypadMinus, windowsKeyBuffer[109]);
	kb.SimuLayerSetKeyState(CSK_KeypadMultiply, windowsKeyBuffer[106]);
	kb.SimuLayerSetKeyState(CSK_KeypadDevide, windowsKeyBuffer[111]);
}
