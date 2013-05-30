
#include "KeyboardEvent.h"

KeyboardEvent::KeyboardEvent( unsigned long value )
{
	SetCode( value );
}

KeyboardEvent::~KeyboardEvent()
{

}

void KeyboardEvent::SetCode( unsigned long value )
{
	_code = (KEY_CODE)value;	
}