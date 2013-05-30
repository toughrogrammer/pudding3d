
#ifndef _WIREFRAME_TIANGLE_RASTERIZER_H_
#define _WIREFRAME_TIANGLE_RASTERIZER_H_

#include "TriangleRasterizer.h"

class FrameBuffer;

class WireframeTriangleRasterizer : public TriangleRasterizer
{
public:
	WireframeTriangleRasterizer();
	~WireframeTriangleRasterizer();

	virtual void drawTriangle( FrameBuffer* buffer, const Triangle& t );


private:
	void drawLine( FrameBuffer* buffer, Vertex v1, Vertex v2 );
	void drawLine( FrameBuffer* buffer,
					const Color &color1, float x1, float y1, 
					const Color &color2, float x2, float y2 );
	bool ClipLine( FrameBuffer* buffer, float& x1, float& y1, float& x2, float& y2 );
};

#endif