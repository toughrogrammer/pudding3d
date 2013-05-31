
#include "RenderManager.h"
#include "Renderer.h"
#include "Camera.h"
#include "Viewport.h"
#include "RenderList.h"

#include "Mesh.h"

RenderManager::RenderManager( Camera* camera, Viewport* viewport )
	:_camera(camera), _viewport(viewport)
{
	_renderer = new Renderer( viewport->_width, viewport->_height );

	_renderList = new RenderList;

	mesh = new Mesh("resource\\mymesh.txt");

	plane1 = new Mesh("resource\\plane1.txt");
	plane2 = new Mesh("resource\\plane2.txt");
}

RenderManager::~RenderManager()
{
	if( _renderer )
		delete _renderer;

	if( _renderList )
		delete _renderList;

	if( mesh )
		delete mesh;

	if( plane1 )
		delete plane1;

	if( plane2 )
		delete plane2;
}

void RenderManager::RenderFrame()
{
	_renderList->triangles().clear();
	for( auto& t : mesh->GetTriangles() )
	{
		_renderList->append( t );
	}
	for( auto& t : plane1->GetTriangles() )
	{
		_renderList->append( t );
	}
	for( auto& t : plane2->GetTriangles() )
	{
		_renderList->append( t );
	}


	_renderer->Begin();

	_camera->WorldToCamera( _renderList );
	_camera->CameraToScreen( _renderList, _viewport );
	
	_renderer->Render( _renderList );

	_renderer->End( _viewport );
}