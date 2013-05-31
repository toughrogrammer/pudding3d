
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
	Vector3 camPos( 7.5, 7.5, -1.40 );
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

void Controller::HandleMessage( MouseEvent mouse, KeyboardEvent keyboard )
{
	Vector3 pos = _camera->GetPosition();

	switch( keyboard._code )
	{
	case KEY_W:
		pos.Set( pos.x, pos.y + 1, pos.z );
		break;
	case KEY_S:
		pos.Set( pos.x, pos.y - 1, pos.z );
		break;
	case KEY_A:
		pos.Set( pos.x - 1, pos.y, pos.z );
		break;
	case KEY_D:
		pos.Set( pos.x + 1, pos.y, pos.z );
		break;
	case KEY_Z:
		pos.Set( pos.x, pos.y, pos.z + 0.2 );
		break;
	case KEY_X:
		pos.Set( pos.x, pos.y, pos.z - 0.2 );
		break;
	}

	_camera->SetPosition( pos );
}