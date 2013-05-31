
#ifndef _FRAME_BUFFER_H_
#define _FRAME_BUFFER_H_

#include <stdint.h>
#include "Color.h"

class FrameBuffer
{
public:
	FrameBuffer();
	FrameBuffer( int x, int y, int w, int h );
	~FrameBuffer();

	void Reset( int x, int y, int w, int h );
	void SetPixel( uint32_t x, uint32_t y, int32_t z, const Color& color );
	void Clear();

	uint32_t GetOriginX() { return _x; }
	uint32_t GetOriginY() { return _y; }
	uint32_t GetWidth() { return _width; }
	uint32_t GetHeight() { return _height; }
	uint32_t* Buffer() { return _buffer; }


private:
	uint32_t* _buffer;
	int32_t* _zbuffer;
	uint32_t _x, _y;
	uint32_t _width, _height;
};

#endif
