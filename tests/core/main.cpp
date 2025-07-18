#include "Application.h"

int main(int argc, char** argv) 
{
	Application* app = new Application(1280, 720, "Mabble");
	app->Run();
	delete app;

	return 0;
}