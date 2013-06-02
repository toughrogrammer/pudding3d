
#include "Application.h"
#include "Controller.h"
#include "RenderManager.h"
#include "Viewport.h"

#include <time.h>
#include <stdlib.h>

Application::Application()
{

}

Application::~Application()
{

}

//
// Meesage processor
// **This method is not member method in Application!!
//
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	static MouseEvent mouse;
	static KeyboardEvent key(0);
	
	switch(iMessage) 
	{
	case WM_LBUTTONDOWN:
		mouse.SetCode( MOUSE_CODE::MOUSE_LEFT_DOWN );
		break;
	case WM_RBUTTONDOWN:
		mouse.SetCode( MOUSE_CODE::MOUSE_RIGHT_DOWN );
		break;
	case WM_KEYDOWN:
		key.SetCode( wParam );
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	Controller::Self()->HandleMessage( mouse, key );
	mouse.SetCode(0);
	key.SetCode(0);

	return DefWindowProc(hWnd,iMessage,wParam,lParam);
}

void Application::Create( HINSTANCE hInstance, int nCmdShow, const char* szName, int x, int y, int width, int height )
{
	srand( time(NULL) );

	AllocConsole();

	WNDCLASS WndClass;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = szName;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass( &WndClass );

	_hWnd = CreateWindow(szName, szName, WS_OVERLAPPEDWINDOW,
		x, y, width, height,
		NULL, (HMENU)NULL, hInstance, NULL);
	this->_nCmdShow = nCmdShow;

	GetClientRect( _hWnd, &_windowSize );

	controller = Controller::Self();
	controller->CreateViewport( width, height );
	controller->GetViewport()->Initialize( _hWnd );
}

bool Application::Run()
{
	ShowWindow( _hWnd, _nCmdShow );

	bool bDone = false;
	MSG msg;

	while(!bDone)
	{
		while(PeekMessage(&msg, NULL,  0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				bDone = true;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		controller->GetRenderManager()->RenderFrame();
	}

	Controller::SelfDtor();
	
	return false;
}