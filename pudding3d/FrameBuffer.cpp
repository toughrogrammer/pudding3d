
#include "FrameBuffer.h"

FrameBuffer::FrameBuffer()
	:_buffer(0), _zbuffer(0)
{

}
FrameBuffer::FrameBuffer( int x, int y, int w, int h )
	:_x(x), _y(y), _width(w), _height(h)
{
	_buffer = new uint32_t[ _width * _height ];
	_zbuffer = new int32_t[ _width * _height ];
}

FrameBuffer::~FrameBuffer()
{
	if( _buffer )
		delete[] _buffer;

	if( _zbuffer )
		delete[] _zbuffer;
}

void FrameBuffer::Reset( int x, int y, int w, int h )
{
	_x = x;
	_y = y;
	_width = w;
	_height = h;

	if( _buffer )
		delete[] _buffer;
	_buffer = new uint32_t[ _width * _height ];

	if( _zbuffer )
		delete[] _zbuffer;
	_zbuffer = new int32_t[ _width * _height ];
}

void FrameBuffer::SetPixel( uint32_t x, uint32_t y, int32_t z, const Color& color)
{
	if( x >= _width || y >= _height )
		return;

	if( z > _zbuffer[ y * _width + x ] )
		return;

	_buffer[y * _width + x] = color.ToUInt32();
	_zbuffer[ y * _width + x ] = z;
}

void FrameBuffer::Clear()
{
	unsigned int i;
	for( i=0; i<_width * _height; i++ )
		_buffer[i] = 0;
	for( i=0; i<_width * _height; i++ )
		_zbuffer[i] = INT32_MAX;
}