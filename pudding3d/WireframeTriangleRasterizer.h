
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
	bool ClipLine( FrameBuffer* buffer, Vector4& p1, Vector4& p2 );
};

#endif