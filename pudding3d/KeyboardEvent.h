
#ifndef _KEYBOARD_EVENT_
#define _KEYBOARD_EVENT_

enum KEY_CODE
{
    KEY_NONE        = 0x00,
    // win32 keyboard codes (from the irrlicht)
    KEY_BACK        = 0x08,  // BACKSPACE key
    KEY_TAB         = 0x09,  // TAB key
    KEY_RETURN      = 0x0D,  // ENTER key
    KEY_ESCAPE      = 0x1B,  // ESC key
    KEY_SPACE       = 0x20,  // SPACEBAR
    KEY_LEFT        = 0x25,  // LEFT ARROW key
    KEY_UP          = 0x26,  // UP ARROW key
    KEY_RIGHT       = 0x27,  // RIGHT ARROW key
    KEY_DOWN        = 0x28,  // DOWN ARROW key
    KEY_0			= 0x30,  // 0 key
    KEY_1			= 0x31,  // 1 key
    KEY_2			= 0x32,  // 2 key
    KEY_3			= 0x33,  // 3 key
    KEY_4			= 0x34,  // 4 key
    KEY_5			= 0x35,  // 5 key
    KEY_6			= 0x36,  // 6 key
    KEY_7			= 0x37,  // 7 key
    KEY_8			= 0x38,  // 8 key
    KEY_9			= 0x39,  // 9 key
    KEY_A			= 0x41,  // A key
    KEY_B			= 0x42,  // B key
    KEY_C			= 0x43,  // C key
    KEY_D			= 0x44,  // D key
    KEY_E			= 0x45,  // E key
    KEY_F			= 0x46,  // F key
    KEY_G			= 0x47,  // G key
    KEY_H			= 0x48,  // H key
    KEY_I			= 0x49,  // I key
    KEY_J			= 0x4A,  // J key
    KEY_K			= 0x4B,  // K key
    KEY_L			= 0x4C,  // L key
    KEY_M			= 0x4D,  // M key
    KEY_N			= 0x4E,  // N key
    KEY_O			= 0x4F,  // O key
    KEY_P			= 0x50,  // P key
    KEY_Q			= 0x51,  // Q key
    KEY_R			= 0x52,  // R key
    KEY_S			= 0x53,  // S key
    KEY_T			= 0x54,  // T key
    KEY_U			= 0x55,  // U key
    KEY_V			= 0x56,  // V key
    KEY_W			= 0x57,  // W key
    KEY_X			= 0x58,  // X key
    KEY_Y			= 0x59,  // Y key
    KEY_Z			= 0x5A,  // Z key
    KEY_F1          = 0x70,  // F1 key
    KEY_F2          = 0x71,  // F2 key
    KEY_F3          = 0x72,  // F3 key
    KEY_F4          = 0x73,  // F4 key
    KEY_F5          = 0x74,  // F5 key
    KEY_F6          = 0x75,  // F6 key
    KEY_F7          = 0x76,  // F7 key
    KEY_F8          = 0x77,  // F8 key
    KEY_F9          = 0x78,  // F9 key
    KEY_F10         = 0x79,  // F10 key
    KEY_F11         = 0x7A,  // F11 key
    KEY_F12         = 0x7B   // F12 key
};

class KeyboardEvent
{
public:
	KEY_CODE _code;
		
	KeyboardEvent( unsigned long value );
	~KeyboardEvent();
	void SetCode( unsigned long value );
};

#endif