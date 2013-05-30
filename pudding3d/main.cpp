
#include "Application.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	Application *app = new Application;

	app->Create( hInstance, 
		nCmdShow,
		"Pudding3D", 
		200, 100, 
		960, 640 );

	return app->Run();
}