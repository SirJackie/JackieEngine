#ifndef __CSBF_IOSupport
#define __CSBF_IOSupport

#include "FrameBufferSupport.h"
#include "FontSupport.h"


/*
** Output
*/

void DrawChar(FrameBuffer fb, int x, int y, int color, char ch)
{
	int* bitmapPointer;
	for (int deltaY = 0; deltaY < 16; deltaY++) {
		bitmapPointer = (int*)(Font + ((int)ch * 16 * 8) + (8 * deltaY));
		if (bitmapPointer[0] == 255) { SetPixel(fb, (x + 0), (y + deltaY), color); }
		if (bitmapPointer[1] == 255) { SetPixel(fb, (x + 1), (y + deltaY), color); }
		if (bitmapPointer[2] == 255) { SetPixel(fb, (x + 2), (y + deltaY), color); }
		if (bitmapPointer[3] == 255) { SetPixel(fb, (x + 3), (y + deltaY), color); }
		if (bitmapPointer[4] == 255) { SetPixel(fb, (x + 4), (y + deltaY), color); }
		if (bitmapPointer[5] == 255) { SetPixel(fb, (x + 5), (y + deltaY), color); }
		if (bitmapPointer[6] == 255) { SetPixel(fb, (x + 6), (y + deltaY), color); }
		if (bitmapPointer[7] == 255) { SetPixel(fb, (x + 7), (y + deltaY), color); }
	}
}


void DrawString(FrameBuffer fb, int x, int y, int color, const char* stringPointer)
{
	int originX = x;
	for (; *stringPointer != 0x00; stringPointer++) {
		if (*stringPointer == '\n') {
			y += 16;
			x = originX;
			continue;
		}
		DrawChar(fb, x, y, color, *stringPointer);  // Draw This Char
		x += 8;

		if (x >= fb.Width) {
			y += 16;
			x = originX;
		}
		if (y >= fb.Height) {
			return;
		}
		
	}
	return;
}


void DrawShadowString(FrameBuffer fb, int x, int y, const char* stringPointer) {
	DrawString(fb, x,     y,     CreateColor(0,   0,   0  ), stringPointer);
	DrawString(fb, x + 1, y + 1, CreateColor(255, 255, 255), stringPointer);
}


/*
** Input
*/

#define Keyboard int*

#define    KEY_LBUTTON             0x01    // 鼠标左键（控制台不使用）
#define    KEY_RBUTTON             0x02    // 鼠标右键（控制台不使用）
#define    KEY_CANCEL              0x03    // 控制中断键，就是Ctrl+PauseBreak（控制台不使用）
#define    KEY_MBUTTON             0x04    // 鼠标中键（控制台不使用）
#define    KEY_XBUTTON1            0x05    // 鼠标X1键，具体哪个键根据实际情况而定（控制台不使用）
#define    KEY_XBUTTON2            0x06    // 鼠标X2键，具体哪个键根据实际情况而定（控制台不使用）
#define    KEY_BACK                0x08    // 退格键，就是Backspace
#define    KEY_TAB                 0x09    // 制表键，就是Tab
#define    KEY_CLEAR               0x0C    // Clear键，NumLock关闭时的数字键盘5
#define    KEY_RETURN              0x0D    // 回车键，就是Enter
#define    KEY_SHIFT               0x10    // 上档键，就是Shift
#define    KEY_CONTROL             0x11    // 控制键，就是Ctrl
#define    KEY_MENU                0x12    // 换挡键，就是Alt
#define    KEY_PAUSE               0x13    // 中断暂停键，就是PauseBreak
#define    KEY_CAPITAL             0x14    // 大小写锁定键，就是CapsLock
#define    KEY_KANA                0x15    // 输入法编辑器（InputMethodEditor简称IME）假名模式
#define    KEY_HANGEUL             0x15    // 输入法编辑器假名模式，老名字了，为了兼容性
#define    KEY_HANGUL              0x15    // 输入法编辑器假名模式，老名字了，为了兼容性
#define    KEY_JUNJA               0x17    // 输入法编辑器junja模式
#define    KEY_FINAL               0x18    // 输入法编辑器final模式
#define    KEY_HANJA               0x19    // 输入法编辑器汉字模式
#define    KEY_KANJI               0x19    // 输入法编辑器汉字模式
#define    KEY_ESCAPE              0x1B    // 退出键，就是Esc
#define    KEY_CONVERT             0x1C    // IMEconvert
#define    KEY_NONCONVERT          0x1D    // IMEnonconvert
#define    KEY_ACCEPT              0x1E    // IMEaccept
#define    KEY_MODECHANGE          0x1F    // IMEmodechangerequest
#define    KEY_SPACE               0x20    // 空格键，就是SpaceBar
#define    KEY_PRIOR               0x21    // 向上翻页键，就是PageUp
#define    KEY_NEXT                0x22    // 向下翻页键，就是PageDown
#define    KEY_END                 0x23    // 结尾键，就是End
#define    KEY_HOME                0x24    // 起始键，就是Home
#define    KEY_LEFT                0x25    // 左方向键，就是←
#define    KEY_UP                  0x26    // 上方向键，就是↑
#define    KEY_RIGHT               0x27    // 右方向键，就是→
#define    KEY_DOWN                0x28    // 下方向键，就是↓
#define    KEY_SELECT              0x29    // Select键
#define    KEY_PRINT               0x2A    // Print键
#define    KEY_EXE                 0x2B    // Excute键
#define    KEY_SNAPSHOT            0x2C    // 屏幕打印键，就是PrintScreen
#define    KEY_INSERT              0x2D    // 插入键，就是Insert
#define    KEY_DELETE              0x2E    // 删除键，就是Delete
#define    KEY_HELP                0x2F    // Help键
#define    KEY_LWIN                0x5B    // 左windows徽标键，就是一个窗口形状的那个键
#define    KEY_RWIN                0x5C    // 右windows徽标键，就是一个窗口形状的那个键
#define    KEY_APPS                0x5D    // 应用程序键，就是按一下弹出右键菜单的那个键
#define    KEY_SLEEP               0x5F    // 睡眠键，就是Sleep
#define    KEY_NUMPAD0             0x60    // 数字键盘0键
#define    KEY_NUMPAD1             0x61    // 数字键盘1键
#define    KEY_NUMPAD2             0x62    // 数字键盘2键
#define    KEY_NUMPAD3             0x63    // 数字键盘3键
#define    KEY_NUMPAD4             0x64    // 数字键盘4键
#define    KEY_NUMPAD5             0x65    // 数字键盘5键
#define    KEY_NUMPAD6             0x66    // 数字键盘6键
#define    KEY_NUMPAD7             0x67    // 数字键盘7键
#define    KEY_NUMPAD8             0x68    // 数字键盘8键
#define    KEY_NUMPAD9             0x69    // 数字键盘9键
#define    KEY_MULTIPLY            0x6A    // 乘法键，就是数字键盘*键
#define    KEY_ADD                 0x6B    // 加法键，就是数字键盘+键
#define    KEY_SEPARATOR           0x6C    // Separator键
#define    KEY_SUBTRACT            0x6D    // 减法键，就是数字键盘-键
#define    KEY_DECIMAL             0x6E    // 小数点键，就是数字键盘.键
#define    KEY_DIVIDE              0x6F    // 除法键，就是数字键盘/键
#define    KEY_F1                  0x70    // 功能1键，就是F1
#define    KEY_F2                  0x71    // 功能2键，就是F2
#define    KEY_F3                  0x72    // 功能3键，就是F3
#define    KEY_F4                  0x73    // 功能4键，就是F4
#define    KEY_F5                  0x74    // 功能5键，就是F5
#define    KEY_F6                  0x75    // 功能6键，就是F6
#define    KEY_F7                  0x76    // 功能7键，就是F7
#define    KEY_F8                  0x77    // 功能8键，就是F8
#define    KEY_F9                  0x78    // 功能9键，就是F9
#define    KEY_F10                 0x79    // 功能10键，就是F10
#define    KEY_F11                 0x7A    // 功能11键，就是F11
#define    KEY_F12                 0x7B    // 功能12键，就是F12
#define    KEY_F13                 0x7C    // 功能13键，就是F13
#define    KEY_F14                 0x7D    // 功能14键，就是F14
#define    KEY_F15                 0x7E    // 功能15键，就是F15
#define    KEY_F16                 0x7F    // 功能16键，就是F16
#define    KEY_F17                 0x80    // 功能17键，就是F17
#define    KEY_F18                 0x81    // 功能18键，就是F18
#define    KEY_F19                 0x82    // 功能19键，就是F19
#define    KEY_F20                 0x83    // 功能20键，就是F20
#define    KEY_F21                 0x84    // 功能21键，就是F21
#define    KEY_F22                 0x85    // 功能22键，就是F22
#define    KEY_F23                 0x86    // 功能23键，就是F23
#define    KEY_F24                 0x87    // 功能24键，就是F24
#define    KEY_NUMLOCK             0x90    // 数字键盘锁定键，就是NumLock
#define    KEY_SCROLL              0x91    // 滚动锁定键，就是ScrollLock
#define    KEY_OEM_NEC_EQUAL       0x92    // NECPC-9800键盘定义的数字键盘=键
#define    KEY_OEM_FJ_JISHO        0x92    // Fujitsu/OASYS键盘定义的'Dictionary'键
#define    KEY_OEM_FJ_MASSHOU      0x93    // Fujitsu/OASYS键盘定义的'Unregisterword'键
#define    KEY_OEM_FJ_TOUROKU      0x94    // Fujitsu/OASYS键盘定义的'Registerword'键
#define    KEY_OEM_FJ_LOYA         0x95    // Fujitsu/OASYS键盘定义的'LeftOYAYUBI'键
#define    KEY_OEM_FJ_ROYA         0x96    // Fujitsu/OASYS键盘定义的'RightOYAYUBI'键
#define    KEY_LSHIFT              0xA0    // 左上档键，就是Shift，控制台只使用KEY_SHIFT（控制台不使用）
#define    KEY_RSHIFT              0xA1    // 右上档键，就是Shift，控制台只使用KEY_SHIFT（控制台不使用）
#define    KEY_LCONTROL            0xA2    // 左控制键，就是Ctrl，控制台只是用KEY_CONTROL（控制台不使用）
#define    KEY_RCONTROL            0xA3    // 右控制键，就是Ctrl，控制台只是用KEY_CONTROL（控制台不使用）
#define    KEY_LMENU               0xA4    // 左换挡键，就是Alt，控制台只是用KEY_MENU（控制台不使用）
#define    KEY_RMENU               0xA5    // 右换挡键，就是Alt，控制台只是用KEY_MENU（控制台不使用）
#define    KEY_BROWSER_BACK        0xA6    // 浏览器后退键
#define    KEY_BROWSER_FORWARD     0xA7    // 浏览器前进键
#define    KEY_BROWSER_REFRESH     0xA8    // 浏览器刷新键
#define    KEY_BROWSER_STOP        0xA9    // 浏览器停止键
#define    KEY_BROWSER_SEARCH      0xAA    // 浏览器查找键
#define    KEY_BROWSER_FAVORITES   0xAB    // 浏览器收藏夹键
#define    KEY_BROWSER_HOME        0xAC    // 浏览器主页键
#define    KEY_VOLUME_MUTE         0xAD    // 音量静音键
#define    KEY_VOLUME_DOWN         0xAE    // 音量调低键
#define    KEY_VOLUME_UP           0xAF    // 音量调高键
#define    KEY_MEDIA_NEXT_TRACK    0xB0    // 媒体下一曲目键
#define    KEY_MEDIA_PREV_TRACK    0xB1    // 媒体上一曲目键
#define    KEY_MEDIA_STOP          0xB2    // 媒体停止键
#define    KEY_MEDIA_PLAY_PAUSE    0xB3    // 媒体播放/暂停键
#define    KEY_LAUNCH_MAIL         0xB4    // 启动邮件键
#define    KEY_LAUNCH_MEDIA_SELECT 0xB5    // 启动媒体选择键
#define    KEY_LAUNCH_APP1         0xB6    // 启动应用程序1键
#define    KEY_LAUNCH_APP2         0xB7    // 启动应用程序2键
#define    KEY_OEM_1               0xBA    // 符号';:'键
#define    KEY_OEM_PLUS            0xBB    // 符号'=+'键
#define    KEY_OEM_COMMA           0xBC    // 符号',<'键
#define    KEY_OEM_MINUS           0xBD    // 符号'-_'键
#define    KEY_OEM_PERIOD          0xBE    // 符号'.>'键
#define    KEY_OEM_2               0xBF    // 符号'/?'键
#define    KEY_OEM_3               0xC0    // 符号'`~'键
#define    KEY_OEM_4               0xDB    // 符号'[{'键
#define    KEY_OEM_5               0xDC    // 符号'|'键
#define    KEY_OEM_6               0xDD    // 符号']}'键
#define    KEY_OEM_7               0xDE    // 符号''"'键
#define    KEY_OEM_8               0xDF    // 用于其他字符，不同的键盘不一定一样
#define    KEY_OEM_AX              0xE1    // 日本AX键盘的'AX'键
#define    KEY_OEM_102             0xE2    // RT102-key键盘的"<>"或"|"键
#define    KEY_ICO_HELP            0xE3    // 帮助图标键
#define    KEY_ICO_00              0xE4    // 00图标键
#define    KEY_PROCESSKEY          0xE5    // IMEPROCESS键
#define    KEY_ICO_CLEAR           0xE6    // Clear图标键
#define    KEY_PACKET              0xE7    // 不太清楚是什么意思
#define    KEY_OEM_RESET           0xE9    // 诺基亚、爱立信使用的
#define    KEY_OEM_JUMP            0xEA    // 诺基亚、爱立信使用的
#define    KEY_OEM_PA1             0xEB    // 诺基亚、爱立信使用的
#define    KEY_OEM_PA2             0xEC    // 诺基亚、爱立信使用的
#define    KEY_OEM_PA3             0xED    // 诺基亚、爱立信使用的
#define    KEY_OEM_WSCTRL          0xEE    // 诺基亚、爱立信使用的
#define    KEY_OEM_CUSEL           0xEF    // 诺基亚、爱立信使用的
#define    KEY_OEM_ATTN            0xF0    // 诺基亚、爱立信使用的
#define    KEY_OEM_FINISH          0xF1    // 诺基亚、爱立信使用的
#define    KEY_OEM_COPY            0xF2    // 诺基亚、爱立信使用的
#define    KEY_OEM_AUTO            0xF3    // 诺基亚、爱立信使用的
#define    KEY_OEM_ENLW            0xF4    // 诺基亚、爱立信使用的
#define    KEY_OEM_BACKTAB         0xF5    // 诺基亚、爱立信使用的
#define    KEY_MOUSE_LBTN          0xF0    // 鼠标左键
#define    KEY_MOUSE_RBTN          0xF1    // 鼠标右键
#define    KEY_MOUSE_CBTN          0xF2    // 鼠标中键
#define    KEY_ATTN                0xF6    // Attn键
#define    KEY_CRSEL               0xF7    // CrSel键
#define    KEY_EXSEL               0xF8    // ExSel键
#define    KEY_EREOF               0xF9    // EraseEOF键
#define    KEY_PLAY                0xFA    // Play键
#define    KEY_ZOOM                0xFB    // Zoom键
#define    KEY_NONAME              0xFC    // 未用
#define    KEY_PA1                 0xFD    // PA1键
#define    KEY_OEM_CLEAR           0xFE    // Clear键

#endif
