
#ifndef _Renderer_H_
#define _Renderer_H_

class FrameBuffer;
class WireframeTriangleRasterizer;
class FlatTriangleRasterizer;
class RenderList;
class Viewport;

enum RENDER_MODE {
	WIREFRAME = 0,
	FLAT,
};

class Renderer
{
public:
	Renderer( int width, int height );
	~Renderer();

	void Init( );
	void Begin();
	void Render( RenderList* renderList );
	void End( Viewport* viewport );

	void SetRenderMode( RENDER_MODE mode );

private:
	FrameBuffer* _buffer;
	WireframeTriangleRasterizer* _wireRasterizer;
	FlatTriangleRasterizer* _flatRasterizer;

	RENDER_MODE _mode;
	
};

#endif