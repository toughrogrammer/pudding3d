
#include "Viewport.h"
#include "FrameBuffer.h"

#include <stdio.h>
#include "Controller.h"
#include "Vector3.h"
#include "Camera.h"

Viewport::Viewport( int x, int y, int w, int h )
	:_x(x), _y(y), _width(w), _height(h)
{

}

Viewport::~Viewport()
{
	SelectObject( _hBackDC, _hOldBitmap );
	DeleteObject( _hBitmap );
	DeleteDC( _hBackDC );
	DeleteDC( _hScreenDC );
}

void Viewport::Initialize( HWND hWnd )
{
	_hWnd = hWnd;

	_hScreenDC = GetDC( hWnd );
	_hBackDC = CreateCompatibleDC( _hScreenDC );
	SetBkMode( _hBackDC, TRANSPARENT );
}

void Viewport::SetViewport( int x, int y, int w, int h )
{
	_x = x;
	_y = y;
	_width = w;
	_height = h;
}

void Viewport::Flush( FrameBuffer* buffer )
{
	if( !_hBackDC ) 
		return; 


	_hScreenDC = GetDC( _hWnd );
	_hOldBitmap = (HBITMAP)SelectObject( _hBackDC, _hBitmap );


	static BITMAPINFO bmi;
    memset(&bmi, 0, sizeof(bmi));

    bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth       = _width;
    bmi.bmiHeader.biHeight      = -_height; // Top to Bottom coordinate
    bmi.bmiHeader.biPlanes      = 1;
    bmi.bmiHeader.biBitCount    = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage   = 0;

    SetDIBitsToDevice(_hScreenDC,
        0, 0,
        _width, _height,
        0, 0,
        0, _height,
		buffer->Buffer(),
        &bmi,
        DIB_RGB_COLORS);

	Vector3 pos = Controller::Self()->GetCamera()->GetPosition();
	char str[64];
	sprintf( str, "Camere Position  x:%5.2f  y:%5.2f  z:%5.2f", pos.x, pos.y, pos.z );
	SetTextColor( _hScreenDC, RGB(0, 0, 0) );
	TextOut( _hScreenDC, 0, 0, str, strlen(str) );

	//BitBlt(_hScreenDC, 0, 0, _width, _height, _hBackDC, 0, 0, SRCCOPY);

	ReleaseDC( _hWnd, _hScreenDC );
	SelectObject( _hBackDC, _hOldBitmap );
}