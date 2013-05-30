
#include "Controller.h"
#include "RenderManager.h"
#include "Camera.h"
#include "Viewport.h"
#include "util.h"

Controller* Controller::_instance = 0;

Controller::Controller()
	:_viewport(NULL),
	_renderManager(NULL)
{
	Vector3 camPos( 2.5, 2.5, -5 );
	_camera = new Camera( camPos );
}

Controller::~Controller()
{
	if( _camera )
		delete _camera;

	if( _viewport )
		delete _viewport;

	if( _renderManager )
		delete _renderManager;
}

void Controller::CreateViewport( int width, int height )
{
	if( _viewport )
		delete _viewport;
	_viewport = new Viewport( 0, 0, width, height );

	
	CreateRenderManager();
}

void Controller::CreateRenderManager()
{
	if( _renderManager )
		delete _renderManager;
	_renderManager = new RenderManager( _camera, _viewport );

}