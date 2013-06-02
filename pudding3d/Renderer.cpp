
#include "Renderer.h"
#include "FrameBuffer.h"
#include "WireframeTriangleRasterizer.h"
#include "FlatTriangleRasterizer.h"
#include "RenderList.h"
#include "Viewport.h"

Renderer::Renderer( int width, int height )
	:_buffer( new FrameBuffer( 0, 0, width, height ) ),
	_wireRasterizer( new WireframeTriangleRasterizer ),
	_flatRasterizer( new FlatTriangleRasterizer )
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
	RenderList::Triangles& triangles = renderList->triangles();

	for( auto& t : triangles )
	{
		if( t.IsClipped() ) 
			continue;
		//_wireRasterizer->drawTriangle( _buffer, t );
		_flatRasterizer->drawTriangle( _buffer, t );
	}
}

void Renderer::End( Viewport* viewport )
{
	viewport->Flush( _buffer );
}