#include "../mbtpch.h"
#include "Application.h"

int main(int argc, char** argv)
{
	Logger::Init();

	Application* app = new Application(1280, 720, "Mabble v" MABBLE_VERSION);
	app->Run();
	delete app;

	return 0;
}