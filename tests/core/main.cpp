#include "../mbtpch.h"
#include "Application.h"

int main(int argc, char** argv) 
{
	Logger::Init();
	LOGGER_INFO("Mabble version: undefined");

	Application* app = new Application(1280, 720, "Mabble");
	app->Run();
	delete app;

	return 0;
}