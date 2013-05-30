
#ifndef _Application_H_
#define _Application_H_

#include <Windows.h>

class Controller;
class Application
{
public:
	Application();
	~Application();

	void Create( HINSTANCE hInstance, int nCmdShow, const char* szName, int x, int y, int width, int height );
	bool Run();
	void Loop();

private:
	HWND _hWnd;
	int _nCmdShow;
	char* _szName;
	RECT _windowSize;

	Controller* controller;
};

#endif