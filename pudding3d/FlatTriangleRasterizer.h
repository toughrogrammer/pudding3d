
#ifndef _FLAT_TRIANGLE_RASTERIZER_H_
#define _FLAT_TRIANGLE_RASTERIZER_H_

#include "TriangleRasterizer.h"

class FlatTriangleRasterizer : public TriangleRasterizer
{
public:
	FlatTriangleRasterizer();
	~FlatTriangleRasterizer();

	virtual void drawTriangle( FrameBuffer* buffer, const Triangle& t );

private:
	void drawTriangleTopFlat( FrameBuffer* buffer, const Vertex v1, const Vertex v2, const Vertex v3 );
	void drawTriangleBottomFlat( FrameBuffer* buffer, const Vertex v1, const Vertex v2, const Vertex v3 );
	void drawLine( FrameBuffer* buffer, Vertex v1, Vertex v2 );
	bool ClipLine( FrameBuffer* buffer, Vector4& p1, Vector4& p2 );

};

#endif