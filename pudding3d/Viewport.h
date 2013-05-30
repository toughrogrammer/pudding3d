
#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include <Windows.h>

class FrameBuffer;
class Viewport
{
public:
	Viewport( int x, int y, int w, int h );
	~Viewport();

	void Initialize( HWND hWnd );
	void SetViewport( int x, int y, int w, int h );
	void Flush( FrameBuffer* buffer );


public:
	RECT windowRect;
	int _x, _y;
	int _width, _height;


private:
	HWND _hWnd;
	PAINTSTRUCT _ps;
	HDC _hScreenDC, _hBackDC;
	HBITMAP _hBitmap, _hOldBitmap;

	
};

#endif