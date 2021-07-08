#ifndef __CSBF_KeyboardSupport__
#define __CSBF_KeyboardSupport__

#include "BasicDataTypeDeclarations.h"


class CS_Keyboard {
public:
	i32 keyBuffer[256];
	CS_Keyboard();
	csbool IsKeyPressed(i8 key);
	csbool IsKeyFirstTimePressed(i8 key);
	void   SimuLayerSetKeyIsPressed(i8 key);
	void   SimuLayerSetKeyIsReleased(i8 key);
	void   SimuLayerSetKeyState(i8 key, csbool state);
	string GetStrStatus();
};


/*
** Unique Cross-platformed Global Keyboard Index Declaration
*/

#define CSK_Esc                     27
#define CSK_F1                      112
#define CSK_F2                      113
#define CSK_F3                      114
#define CSK_F4                      115
#define CSK_F5                      116
#define CSK_F6                      117
#define CSK_F7                      118
#define CSK_F8                      119
#define CSK_F9                      120
#define CSK_F10                     26
#define CSK_F11                     28
#define CSK_F12                     29

#define CSK_BackQuote               25
#define CSK_Num1                    49
#define CSK_Num2                    50
#define CSK_Num3                    51
#define CSK_Num4                    52
#define CSK_Num5                    53
#define CSK_Num6                    54
#define CSK_Num7                    55
#define CSK_Num8                    56
#define CSK_Num9                    57
#define CSK_Num0                    48
#define CSK_Minus                   10
#define CSK_Plus                    11
#define CSK_Backspace               8

#define CSK_Tab                     9
#define CSK_Q                       81
#define CSK_W                       87
#define CSK_E                       69
#define CSK_R                       82
#define CSK_T                       84
#define CSK_Y                       89
#define CSK_U                       85
#define CSK_I                       73
#define CSK_O                       79
#define CSK_P                       80
#define CSK_LeftSquareBracket       12
#define CSK_RightSquareBracket      14
#define CSK_BackSlash               15

#define CSK_CapsLock                20
#define CSK_A                       65
#define CSK_S                       83
#define CSK_D                       68
#define CSK_F                       70
#define CSK_G                       71
#define CSK_H                       72
#define CSK_J                       74
#define CSK_K                       75
#define CSK_L                       76
#define CSK_Semicolon               18
#define CSK_Quote                   21
#define CSK_Enter                   13

#define CSK_Shift                   16
#define CSK_Z                       90
#define CSK_X                       88
#define CSK_C                       67
#define CSK_V                       86
#define CSK_B                       66
#define CSK_N                       78
#define CSK_M                       77
#define CSK_Comma                   22
#define CSK_FullStop                23
#define CSK_Slash                   24
#define CSK_RightShift              123

#define CSK_Ctrl                    17
#define CSK_Win                     91
#define CSK_Alt                     125
#define CSK_Space                   32
#define CSK_RightAlt                126
#define CSK_RightCtrl               124

#define CSK_Up                      38
#define CSK_Down                    40
#define CSK_Left                    37
#define CSK_Right                   39

#define CSK_Insert                  45
#define CSK_Delete                  46
#define CSK_Home                    36
#define CSK_End                     35
#define CSK_PageUp                  33
#define CSK_PageDown                34

#define CSK_PrintScreen             30
#define CSK_ScrollLock              31
#define CSK_PauseAndBreak           19

#define CSK_Keypad0                 96
#define CSK_Keypad1                 97
#define CSK_Keypad2                 98
#define CSK_Keypad3                 99
#define CSK_Keypad4                 100
#define CSK_Keypad5                 101
#define CSK_Keypad6                 102
#define CSK_Keypad7                 103
#define CSK_Keypad8                 104
#define CSK_Keypad9                 105
#define CSK_KeypadDot               110
#define CSK_KeypadNumLock           122
#define CSK_KeypadEnter             121
#define CSK_KeypadAdd               107
#define CSK_KeypadMinus             109
#define CSK_KeypadMultiply          106
#define CSK_KeypadDevide            111


#endif
