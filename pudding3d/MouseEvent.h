
#ifndef _Mouse_EVENT_
#define _Mouse_EVENT_

enum MOUSE_CODE
{
	MOUSE_LEFT_DOWN		= 0x1,
	MOUSE_LEFT_UP		= 0x2,
	MOUSE_RIGHT_DOWN	= 0x4,
	MOUSE_RIGHT_UP		= 0x8,
	MOUSE_MIDDLE_DOWN	= 0x10,
	MOUSE_MIDDLE_UP		= 0x20,
};

class MouseEvent
{
public:
	int _x, _y;
	unsigned _code;

	MouseEvent( int x = 0, int y = 0, unsigned long value = 0 );
	~MouseEvent();
	void SetCode( unsigned long value );

	bool isLeftDown()	{ return _code & MOUSE_LEFT_DOWN; }
	bool isLeftUp()		{ return _code & MOUSE_LEFT_UP; }
	bool isRightDown()	{ return _code & MOUSE_RIGHT_DOWN; }
	bool isRightUp()	{ return _code & MOUSE_RIGHT_UP; }
	bool isMiddleDown() { return _code & MOUSE_MIDDLE_DOWN; }
	bool isMiddleUp()	{ return _code & MOUSE_MIDDLE_UP; }

};

#endif