
#ifndef _FRAME_BUFFER_H_
#define _FRAME_BUFFER_H_

#include <stdint.h>
#include "Color.h"

class FrameBuffer
{
public:
	FrameBuffer();
	FrameBuffer( int w, int h );
	~FrameBuffer();

	void Resize( int w, int h );
	void SetPixel( uint32_t x, uint32_t y, const Color& color );
	void Clear();

	uint32_t getWidth() { return width; }
	uint32_t getHeight() { return height; }
	uint32_t* Buffer() { return buffer; }


private:
	uint32_t* buffer;
	uint32_t width, height;
};

#endif
