
#include "Renderer.h"
#include "FrameBuffer.h"
#include "TriangleRasterizer.h"
#include "WireframeTriangleRasterizer.h"
#include "FlatTriangleRasterizer.h"
#include "RenderList.h"
#include "Viewport.h"

Renderer::Renderer( int width, int height )
	:_buffer( new FrameBuffer( 0, 0, width, height ) ),
	_wireRasterizer( new WireframeTriangleRasterizer ),
	_flatRasterizer( new FlatTriangleRasterizer ),
	_mode( RENDER_MODE::WIREFRAME )
{

}

Renderer::~Renderer()
{
	if( _buffer )
		delete _buffer;

	if( _wireRasterizer )
		delete _wireRasterizer;

	if( _flatRasterizer ) 
		delete _flatRasterizer;
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

	TriangleRasterizer* raster = NULL;
	switch( _mode )
	{
	case RENDER_MODE::WIREFRAME:
		raster = _wireRasterizer;
		break;
	case RENDER_MODE::FLAT:
		raster = _flatRasterizer;
		break;
	}

	for( auto& t : triangles )
	{
		if( t.IsClipped() ) 
			continue;

		if( raster )
			raster->drawTriangle( _buffer, t );
	}
}

void Renderer::End( Viewport* viewport )
{
	viewport->Flush( _buffer );
}

void Renderer::SetRenderMode( RENDER_MODE mode )
{
	_mode = mode;

	switch( _mode )
	{
	case RENDER_MODE::WIREFRAME:
		printf("Renderer : Now render mode is WIREFRAME.\n");
		break;
	case RENDER_MODE::FLAT:
		printf("Renderer : Now render mode is FLAT.\n");
		break;
	}
}