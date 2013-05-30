
#include "MouseEvent.h"

MouseEvent::MouseEvent( int x, int y, unsigned long value )
	:_x(x), _y(y)
{
	SetCode( value );
}

MouseEvent::~MouseEvent()
{

}

void MouseEvent::SetCode( unsigned long value )
{
	_code = (MOUSE_CODE)value;
}