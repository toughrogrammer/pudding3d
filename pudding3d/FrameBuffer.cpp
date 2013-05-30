
#include "FrameBuffer.h"

FrameBuffer::FrameBuffer()
	:buffer(0)
{

}
FrameBuffer::FrameBuffer( int w, int h )
	:width(w), height(h)
{
	this->width = width;
	this->height = height;

	buffer = new uint32_t[ width * height ];

}

FrameBuffer::~FrameBuffer()
{
	if( buffer )
		delete[] buffer;
}

void FrameBuffer::Resize( int w, int h )
{
	this->width = width;
	this->height = height;

	if( buffer )
		delete[] buffer;

	buffer = new uint32_t[ width * height ];
}

void FrameBuffer::SetPixel( uint32_t x, uint32_t y, const Color& color)
{
	if( x >= width || y >= height )
		return;

	buffer[y * width + x] = color.ToUInt32();
}

void FrameBuffer::Clear()
{
	int i;
	for( i=0; i<width*height; i++ )
		buffer[i] = 0;
}