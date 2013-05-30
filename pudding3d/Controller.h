
#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

class RenderManager;
class Camera;
class Viewport;
class Controller
{
private:
	static Controller* _instance;
	RenderManager* _renderManager;
	Camera* _camera;
	Viewport* _viewport;

	Controller();
	~Controller();


public:	
	void CreateViewport( int width, int height );
	void CreateRenderManager();

	static Controller* Self() { 
		if( !_instance )
			_instance = new Controller;
		return _instance;
	}
	static void SelfDtor() {
		if( _instance )
			delete _instance;
	}
	RenderManager* GetRenderManager() { return _renderManager; }
	Camera* GetCamera() { return _camera; }
	Viewport* GetViewport() { return _viewport; }

};

#endif