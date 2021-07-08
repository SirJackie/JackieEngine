#include "KeyboardHelper.h"

LSL_KeyboardHelper::LSL_KeyboardHelper()
{
	CS_Memset(linuxKeyBuffer, 0, 3000);
}

void LSL_KeyboardHelper::MoveLnxBufIntoKeyBuf()
{
	kb.SimuLayerSetKeyState(CSK_Esc, linuxKeyBuffer[27]);
	kb.SimuLayerSetKeyState(CSK_F1, linuxKeyBuffer[1882]);
	kb.SimuLayerSetKeyState(CSK_F2, linuxKeyBuffer[1883]);
	kb.SimuLayerSetKeyState(CSK_F3, linuxKeyBuffer[1884]);
	kb.SimuLayerSetKeyState(CSK_F4, linuxKeyBuffer[1885]);
	kb.SimuLayerSetKeyState(CSK_F5, linuxKeyBuffer[1886]);
	kb.SimuLayerSetKeyState(CSK_F6, linuxKeyBuffer[1887]);
	kb.SimuLayerSetKeyState(CSK_F7, linuxKeyBuffer[1888]);
	kb.SimuLayerSetKeyState(CSK_F8, linuxKeyBuffer[1889]);
	kb.SimuLayerSetKeyState(CSK_F9, linuxKeyBuffer[1890]);
	kb.SimuLayerSetKeyState(CSK_F10, linuxKeyBuffer[1891]);
	kb.SimuLayerSetKeyState(CSK_F11, linuxKeyBuffer[1892]);
	kb.SimuLayerSetKeyState(CSK_F12, linuxKeyBuffer[1893]);

	kb.SimuLayerSetKeyState(CSK_BackQuote, linuxKeyBuffer[96]);
	kb.SimuLayerSetKeyState(CSK_Num1, linuxKeyBuffer[49]);
	kb.SimuLayerSetKeyState(CSK_Num2, linuxKeyBuffer[50]);
	kb.SimuLayerSetKeyState(CSK_Num3, linuxKeyBuffer[51]);
	kb.SimuLayerSetKeyState(CSK_Num4, linuxKeyBuffer[52]);
	kb.SimuLayerSetKeyState(CSK_Num5, linuxKeyBuffer[53]);
	kb.SimuLayerSetKeyState(CSK_Num6, linuxKeyBuffer[54]);
	kb.SimuLayerSetKeyState(CSK_Num7, linuxKeyBuffer[55]);
	kb.SimuLayerSetKeyState(CSK_Num8, linuxKeyBuffer[56]);
	kb.SimuLayerSetKeyState(CSK_Num9, linuxKeyBuffer[57]);
	kb.SimuLayerSetKeyState(CSK_Num0, linuxKeyBuffer[48]);
	kb.SimuLayerSetKeyState(CSK_Minus, linuxKeyBuffer[45]);
	kb.SimuLayerSetKeyState(CSK_Plus, linuxKeyBuffer[61]);
	kb.SimuLayerSetKeyState(CSK_Backspace, linuxKeyBuffer[8]);

	kb.SimuLayerSetKeyState(CSK_Tab, linuxKeyBuffer[9]);
	kb.SimuLayerSetKeyState(CSK_Q, linuxKeyBuffer[113]);
	kb.SimuLayerSetKeyState(CSK_W, linuxKeyBuffer[119]);
	kb.SimuLayerSetKeyState(CSK_E, linuxKeyBuffer[101]);
	kb.SimuLayerSetKeyState(CSK_R, linuxKeyBuffer[114]);
	kb.SimuLayerSetKeyState(CSK_T, linuxKeyBuffer[116]);
	kb.SimuLayerSetKeyState(CSK_Y, linuxKeyBuffer[121]);
	kb.SimuLayerSetKeyState(CSK_U, linuxKeyBuffer[117]);
	kb.SimuLayerSetKeyState(CSK_I, linuxKeyBuffer[105]);
	kb.SimuLayerSetKeyState(CSK_O, linuxKeyBuffer[111]);
	kb.SimuLayerSetKeyState(CSK_P, linuxKeyBuffer[112]);
	kb.SimuLayerSetKeyState(CSK_LeftSquareBracket, linuxKeyBuffer[91]);
	kb.SimuLayerSetKeyState(CSK_RightSquareBracket, linuxKeyBuffer[93]);
	kb.SimuLayerSetKeyState(CSK_BackSlash, linuxKeyBuffer[92]);

	kb.SimuLayerSetKeyState(CSK_CapsLock, linuxKeyBuffer[1081]);
	kb.SimuLayerSetKeyState(CSK_A, linuxKeyBuffer[97]);
	kb.SimuLayerSetKeyState(CSK_S, linuxKeyBuffer[115]);
	kb.SimuLayerSetKeyState(CSK_D, linuxKeyBuffer[100]);
	kb.SimuLayerSetKeyState(CSK_F, linuxKeyBuffer[102]);
	kb.SimuLayerSetKeyState(CSK_G, linuxKeyBuffer[103]);
	kb.SimuLayerSetKeyState(CSK_H, linuxKeyBuffer[104]);
	kb.SimuLayerSetKeyState(CSK_J, linuxKeyBuffer[106]);
	kb.SimuLayerSetKeyState(CSK_K, linuxKeyBuffer[107]);
	kb.SimuLayerSetKeyState(CSK_L, linuxKeyBuffer[108]);
	kb.SimuLayerSetKeyState(CSK_Semicolon, linuxKeyBuffer[59]);
	kb.SimuLayerSetKeyState(CSK_Quote, linuxKeyBuffer[39]);
	kb.SimuLayerSetKeyState(CSK_Enter, linuxKeyBuffer[13]);

	kb.SimuLayerSetKeyState(CSK_Shift, linuxKeyBuffer[2049]);
	kb.SimuLayerSetKeyState(CSK_Z, linuxKeyBuffer[122]);
	kb.SimuLayerSetKeyState(CSK_X, linuxKeyBuffer[120]);
	kb.SimuLayerSetKeyState(CSK_C, linuxKeyBuffer[99]);
	kb.SimuLayerSetKeyState(CSK_V, linuxKeyBuffer[118]);
	kb.SimuLayerSetKeyState(CSK_B, linuxKeyBuffer[98]);
	kb.SimuLayerSetKeyState(CSK_N, linuxKeyBuffer[110]);
	kb.SimuLayerSetKeyState(CSK_M, linuxKeyBuffer[109]);
	kb.SimuLayerSetKeyState(CSK_Comma, linuxKeyBuffer[44]);
	kb.SimuLayerSetKeyState(CSK_FullStop, linuxKeyBuffer[46]);
	kb.SimuLayerSetKeyState(CSK_Slash, linuxKeyBuffer[47]);
	kb.SimuLayerSetKeyState(CSK_RightShift, linuxKeyBuffer[2053]);

	kb.SimuLayerSetKeyState(CSK_Ctrl, linuxKeyBuffer[2048]);
	kb.SimuLayerSetKeyState(CSK_Win, linuxKeyBuffer[2051]);
	kb.SimuLayerSetKeyState(CSK_Alt, linuxKeyBuffer[2050]);
	kb.SimuLayerSetKeyState(CSK_Space, linuxKeyBuffer[32]);
	kb.SimuLayerSetKeyState(CSK_RightAlt, linuxKeyBuffer[2054]);
	kb.SimuLayerSetKeyState(CSK_RightCtrl, linuxKeyBuffer[2052]);

	kb.SimuLayerSetKeyState(CSK_Up, linuxKeyBuffer[1906]);
	kb.SimuLayerSetKeyState(CSK_Down, linuxKeyBuffer[1905]);
	kb.SimuLayerSetKeyState(CSK_Left, linuxKeyBuffer[1904]);
	kb.SimuLayerSetKeyState(CSK_Right, linuxKeyBuffer[1903]);

	kb.SimuLayerSetKeyState(CSK_Insert, linuxKeyBuffer[1897]);
	kb.SimuLayerSetKeyState(CSK_Delete, linuxKeyBuffer[127]);
	kb.SimuLayerSetKeyState(CSK_Home, linuxKeyBuffer[1898]);
	kb.SimuLayerSetKeyState(CSK_End, linuxKeyBuffer[1901]);
	kb.SimuLayerSetKeyState(CSK_PageUp, linuxKeyBuffer[1899]);
	kb.SimuLayerSetKeyState(CSK_PageDown, linuxKeyBuffer[1902]);

	// kb.SimuLayerSetKeyState(CSK_PrintScreen, linuxKeyBuffer[30]);
	kb.SimuLayerSetKeyState(CSK_ScrollLock, linuxKeyBuffer[1895]);
	kb.SimuLayerSetKeyState(CSK_PauseAndBreak, linuxKeyBuffer[1896]);

	kb.SimuLayerSetKeyState(CSK_Keypad0, linuxKeyBuffer[1922]);
	kb.SimuLayerSetKeyState(CSK_Keypad1, linuxKeyBuffer[1913]);
	kb.SimuLayerSetKeyState(CSK_Keypad2, linuxKeyBuffer[1914]);
	kb.SimuLayerSetKeyState(CSK_Keypad3, linuxKeyBuffer[1915]);
	kb.SimuLayerSetKeyState(CSK_Keypad4, linuxKeyBuffer[1916]);
	kb.SimuLayerSetKeyState(CSK_Keypad5, linuxKeyBuffer[1917]);
	kb.SimuLayerSetKeyState(CSK_Keypad6, linuxKeyBuffer[1918]);
	kb.SimuLayerSetKeyState(CSK_Keypad7, linuxKeyBuffer[1919]);
	kb.SimuLayerSetKeyState(CSK_Keypad8, linuxKeyBuffer[1920]);
	kb.SimuLayerSetKeyState(CSK_Keypad9, linuxKeyBuffer[1921]);
	kb.SimuLayerSetKeyState(CSK_KeypadDot, linuxKeyBuffer[1923]);
	kb.SimuLayerSetKeyState(CSK_KeypadNumLock, linuxKeyBuffer[1907]);
	kb.SimuLayerSetKeyState(CSK_KeypadEnter, linuxKeyBuffer[1912]);
	kb.SimuLayerSetKeyState(CSK_KeypadAdd, linuxKeyBuffer[1911]);
	kb.SimuLayerSetKeyState(CSK_KeypadMinus, linuxKeyBuffer[1910]);
	kb.SimuLayerSetKeyState(CSK_KeypadMultiply, linuxKeyBuffer[1909]);
	kb.SimuLayerSetKeyState(CSK_KeypadDevide, linuxKeyBuffer[1908]);
}
