
#ifndef _RENDER_MANAGER_H_
#define _RENDER_MANAGER_H_

class Renderer;
class Camera;
class Viewport;
class RenderList;
class Mesh;
class RenderManager 
{
public:
	RenderManager( Camera* camera, Viewport* viewport );
	~RenderManager();

	void RenderFrame();

	Renderer* GetRenderer() { return _renderer; }

private:
	Renderer* _renderer;
	Camera* _camera;
	Viewport* _viewport;
	RenderList* _renderList;

	Mesh* mesh;
	Mesh* plane1;
	Mesh* plane2;
};

#endif