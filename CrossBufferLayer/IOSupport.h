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

#define    KEY_LBUTTON             0x01    // ������������̨��ʹ�ã�
#define    KEY_RBUTTON             0x02    // ����Ҽ�������̨��ʹ�ã�
#define    KEY_CANCEL              0x03    // �����жϼ�������Ctrl+PauseBreak������̨��ʹ�ã�
#define    KEY_MBUTTON             0x04    // ����м�������̨��ʹ�ã�
#define    KEY_XBUTTON1            0x05    // ���X1���������ĸ�������ʵ���������������̨��ʹ�ã�
#define    KEY_XBUTTON2            0x06    // ���X2���������ĸ�������ʵ���������������̨��ʹ�ã�
#define    KEY_BACK                0x08    // �˸��������Backspace
#define    KEY_TAB                 0x09    // �Ʊ��������Tab
#define    KEY_CLEAR               0x0C    // Clear����NumLock�ر�ʱ�����ּ���5
#define    KEY_RETURN              0x0D    // �س���������Enter
#define    KEY_SHIFT               0x10    // �ϵ���������Shift
#define    KEY_CONTROL             0x11    // ���Ƽ�������Ctrl
#define    KEY_MENU                0x12    // ������������Alt
#define    KEY_PAUSE               0x13    // �ж���ͣ��������PauseBreak
#define    KEY_CAPITAL             0x14    // ��Сд������������CapsLock
#define    KEY_KANA                0x15    // ���뷨�༭����InputMethodEditor���IME������ģʽ
#define    KEY_HANGEUL             0x15    // ���뷨�༭������ģʽ���������ˣ�Ϊ�˼�����
#define    KEY_HANGUL              0x15    // ���뷨�༭������ģʽ���������ˣ�Ϊ�˼�����
#define    KEY_JUNJA               0x17    // ���뷨�༭��junjaģʽ
#define    KEY_FINAL               0x18    // ���뷨�༭��finalģʽ
#define    KEY_HANJA               0x19    // ���뷨�༭������ģʽ
#define    KEY_KANJI               0x19    // ���뷨�༭������ģʽ
#define    KEY_ESCAPE              0x1B    // �˳���������Esc
#define    KEY_CONVERT             0x1C    // IMEconvert
#define    KEY_NONCONVERT          0x1D    // IMEnonconvert
#define    KEY_ACCEPT              0x1E    // IMEaccept
#define    KEY_MODECHANGE          0x1F    // IMEmodechangerequest
#define    KEY_SPACE               0x20    // �ո��������SpaceBar
#define    KEY_PRIOR               0x21    // ���Ϸ�ҳ��������PageUp
#define    KEY_NEXT                0x22    // ���·�ҳ��������PageDown
#define    KEY_END                 0x23    // ��β��������End
#define    KEY_HOME                0x24    // ��ʼ��������Home
#define    KEY_LEFT                0x25    // ����������ǡ�
#define    KEY_UP                  0x26    // �Ϸ���������ǡ�
#define    KEY_RIGHT               0x27    // �ҷ���������ǡ�
#define    KEY_DOWN                0x28    // �·���������ǡ�
#define    KEY_SELECT              0x29    // Select��
#define    KEY_PRINT               0x2A    // Print��
#define    KEY_EXE                 0x2B    // Excute��
#define    KEY_SNAPSHOT            0x2C    // ��Ļ��ӡ��������PrintScreen
#define    KEY_INSERT              0x2D    // �����������Insert
#define    KEY_DELETE              0x2E    // ɾ����������Delete
#define    KEY_HELP                0x2F    // Help��
#define    KEY_LWIN                0x5B    // ��windows�ձ��������һ��������״���Ǹ���
#define    KEY_RWIN                0x5C    // ��windows�ձ��������һ��������״���Ǹ���
#define    KEY_APPS                0x5D    // Ӧ�ó���������ǰ�һ�µ����Ҽ��˵����Ǹ���
#define    KEY_SLEEP               0x5F    // ˯�߼�������Sleep
#define    KEY_NUMPAD0             0x60    // ���ּ���0��
#define    KEY_NUMPAD1             0x61    // ���ּ���1��
#define    KEY_NUMPAD2             0x62    // ���ּ���2��
#define    KEY_NUMPAD3             0x63    // ���ּ���3��
#define    KEY_NUMPAD4             0x64    // ���ּ���4��
#define    KEY_NUMPAD5             0x65    // ���ּ���5��
#define    KEY_NUMPAD6             0x66    // ���ּ���6��
#define    KEY_NUMPAD7             0x67    // ���ּ���7��
#define    KEY_NUMPAD8             0x68    // ���ּ���8��
#define    KEY_NUMPAD9             0x69    // ���ּ���9��
#define    KEY_MULTIPLY            0x6A    // �˷������������ּ���*��
#define    KEY_ADD                 0x6B    // �ӷ������������ּ���+��
#define    KEY_SEPARATOR           0x6C    // Separator��
#define    KEY_SUBTRACT            0x6D    // ���������������ּ���-��
#define    KEY_DECIMAL             0x6E    // С��������������ּ���.��
#define    KEY_DIVIDE              0x6F    // ���������������ּ���/��
#define    KEY_F1                  0x70    // ����1��������F1
#define    KEY_F2                  0x71    // ����2��������F2
#define    KEY_F3                  0x72    // ����3��������F3
#define    KEY_F4                  0x73    // ����4��������F4
#define    KEY_F5                  0x74    // ����5��������F5
#define    KEY_F6                  0x75    // ����6��������F6
#define    KEY_F7                  0x76    // ����7��������F7
#define    KEY_F8                  0x77    // ����8��������F8
#define    KEY_F9                  0x78    // ����9��������F9
#define    KEY_F10                 0x79    // ����10��������F10
#define    KEY_F11                 0x7A    // ����11��������F11
#define    KEY_F12                 0x7B    // ����12��������F12
#define    KEY_F13                 0x7C    // ����13��������F13
#define    KEY_F14                 0x7D    // ����14��������F14
#define    KEY_F15                 0x7E    // ����15��������F15
#define    KEY_F16                 0x7F    // ����16��������F16
#define    KEY_F17                 0x80    // ����17��������F17
#define    KEY_F18                 0x81    // ����18��������F18
#define    KEY_F19                 0x82    // ����19��������F19
#define    KEY_F20                 0x83    // ����20��������F20
#define    KEY_F21                 0x84    // ����21��������F21
#define    KEY_F22                 0x85    // ����22��������F22
#define    KEY_F23                 0x86    // ����23��������F23
#define    KEY_F24                 0x87    // ����24��������F24
#define    KEY_NUMLOCK             0x90    // ���ּ���������������NumLock
#define    KEY_SCROLL              0x91    // ����������������ScrollLock
#define    KEY_OEM_NEC_EQUAL       0x92    // NECPC-9800���̶�������ּ���=��
#define    KEY_OEM_FJ_JISHO        0x92    // Fujitsu/OASYS���̶����'Dictionary'��
#define    KEY_OEM_FJ_MASSHOU      0x93    // Fujitsu/OASYS���̶����'Unregisterword'��
#define    KEY_OEM_FJ_TOUROKU      0x94    // Fujitsu/OASYS���̶����'Registerword'��
#define    KEY_OEM_FJ_LOYA         0x95    // Fujitsu/OASYS���̶����'LeftOYAYUBI'��
#define    KEY_OEM_FJ_ROYA         0x96    // Fujitsu/OASYS���̶����'RightOYAYUBI'��
#define    KEY_LSHIFT              0xA0    // ���ϵ���������Shift������ֻ̨ʹ��KEY_SHIFT������̨��ʹ�ã�
#define    KEY_RSHIFT              0xA1    // ���ϵ���������Shift������ֻ̨ʹ��KEY_SHIFT������̨��ʹ�ã�
#define    KEY_LCONTROL            0xA2    // ����Ƽ�������Ctrl������ֻ̨����KEY_CONTROL������̨��ʹ�ã�
#define    KEY_RCONTROL            0xA3    // �ҿ��Ƽ�������Ctrl������ֻ̨����KEY_CONTROL������̨��ʹ�ã�
#define    KEY_LMENU               0xA4    // �󻻵���������Alt������ֻ̨����KEY_MENU������̨��ʹ�ã�
#define    KEY_RMENU               0xA5    // �һ�����������Alt������ֻ̨����KEY_MENU������̨��ʹ�ã�
#define    KEY_BROWSER_BACK        0xA6    // ��������˼�
#define    KEY_BROWSER_FORWARD     0xA7    // �����ǰ����
#define    KEY_BROWSER_REFRESH     0xA8    // �����ˢ�¼�
#define    KEY_BROWSER_STOP        0xA9    // �����ֹͣ��
#define    KEY_BROWSER_SEARCH      0xAA    // ��������Ҽ�
#define    KEY_BROWSER_FAVORITES   0xAB    // ������ղؼм�
#define    KEY_BROWSER_HOME        0xAC    // �������ҳ��
#define    KEY_VOLUME_MUTE         0xAD    // ����������
#define    KEY_VOLUME_DOWN         0xAE    // �������ͼ�
#define    KEY_VOLUME_UP           0xAF    // �������߼�
#define    KEY_MEDIA_NEXT_TRACK    0xB0    // ý����һ��Ŀ��
#define    KEY_MEDIA_PREV_TRACK    0xB1    // ý����һ��Ŀ��
#define    KEY_MEDIA_STOP          0xB2    // ý��ֹͣ��
#define    KEY_MEDIA_PLAY_PAUSE    0xB3    // ý�岥��/��ͣ��
#define    KEY_LAUNCH_MAIL         0xB4    // �����ʼ���
#define    KEY_LAUNCH_MEDIA_SELECT 0xB5    // ����ý��ѡ���
#define    KEY_LAUNCH_APP1         0xB6    // ����Ӧ�ó���1��
#define    KEY_LAUNCH_APP2         0xB7    // ����Ӧ�ó���2��
#define    KEY_OEM_1               0xBA    // ����';:'��
#define    KEY_OEM_PLUS            0xBB    // ����'=+'��
#define    KEY_OEM_COMMA           0xBC    // ����',<'��
#define    KEY_OEM_MINUS           0xBD    // ����'-_'��
#define    KEY_OEM_PERIOD          0xBE    // ����'.>'��
#define    KEY_OEM_2               0xBF    // ����'/?'��
#define    KEY_OEM_3               0xC0    // ����'`~'��
#define    KEY_OEM_4               0xDB    // ����'[{'��
#define    KEY_OEM_5               0xDC    // ����'|'��
#define    KEY_OEM_6               0xDD    // ����']}'��
#define    KEY_OEM_7               0xDE    // ����''"'��
#define    KEY_OEM_8               0xDF    // ���������ַ�����ͬ�ļ��̲�һ��һ��
#define    KEY_OEM_AX              0xE1    // �ձ�AX���̵�'AX'��
#define    KEY_OEM_102             0xE2    // RT102-key���̵�"<>"��"|"��
#define    KEY_ICO_HELP            0xE3    // ����ͼ���
#define    KEY_ICO_00              0xE4    // 00ͼ���
#define    KEY_PROCESSKEY          0xE5    // IMEPROCESS��
#define    KEY_ICO_CLEAR           0xE6    // Clearͼ���
#define    KEY_PACKET              0xE7    // ��̫�����ʲô��˼
#define    KEY_OEM_RESET           0xE9    // ŵ���ǡ�������ʹ�õ�
#define    KEY_OEM_JUMP            0xEA    // ŵ���ǡ�������ʹ�õ�
#define    KEY_OEM_PA1             0xEB    // ŵ���ǡ�������ʹ�õ�
#define    KEY_OEM_PA2             0xEC    // ŵ���ǡ�������ʹ�õ�
#define    KEY_OEM_PA3             0xED    // ŵ���ǡ�������ʹ�õ�
#define    KEY_OEM_WSCTRL          0xEE    // ŵ���ǡ�������ʹ�õ�
#define    KEY_OEM_CUSEL           0xEF    // ŵ���ǡ�������ʹ�õ�
#define    KEY_OEM_ATTN            0xF0    // ŵ���ǡ�������ʹ�õ�
#define    KEY_OEM_FINISH          0xF1    // ŵ���ǡ�������ʹ�õ�
#define    KEY_OEM_COPY            0xF2    // ŵ���ǡ�������ʹ�õ�
#define    KEY_OEM_AUTO            0xF3    // ŵ���ǡ�������ʹ�õ�
#define    KEY_OEM_ENLW            0xF4    // ŵ���ǡ�������ʹ�õ�
#define    KEY_OEM_BACKTAB         0xF5    // ŵ���ǡ�������ʹ�õ�
#define    KEY_MOUSE_LBTN          0xF0    // ������
#define    KEY_MOUSE_RBTN          0xF1    // ����Ҽ�
#define    KEY_MOUSE_CBTN          0xF2    // ����м�
#define    KEY_ATTN                0xF6    // Attn��
#define    KEY_CRSEL               0xF7    // CrSel��
#define    KEY_EXSEL               0xF8    // ExSel��
#define    KEY_EREOF               0xF9    // EraseEOF��
#define    KEY_PLAY                0xFA    // Play��
#define    KEY_ZOOM                0xFB    // Zoom��
#define    KEY_NONAME              0xFC    // δ��
#define    KEY_PA1                 0xFD    // PA1��
#define    KEY_OEM_CLEAR           0xFE    // Clear��

#endif
