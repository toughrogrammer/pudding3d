
#include "Renderer.h"
#include "FrameBuffer.h"
#include "WireframeTriangleRasterizer.h"
#include "RenderList.h"
#include "Viewport.h"

Renderer::Renderer( int width, int height )
	:_buffer( new FrameBuffer( width, height ) ),
	_wireRasterizer( new WireframeTriangleRasterizer )
{

}

Renderer::~Renderer()
{

}

void Renderer::Init()
{

}

void Renderer::Begin()
{
	_buffer->Clear();
}

void Renderer::Render( RenderList* renderList )
{
	RenderList::Triangles triangles = renderList->triangles();

	for( auto t : triangles )
	{
		_wireRasterizer->drawTriangle( _buffer, t );
	}
}

void Renderer::End( Viewport* viewport )
{
	viewport->Flush( _buffer );
}