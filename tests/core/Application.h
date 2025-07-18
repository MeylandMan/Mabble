#pragma once
#include "Window.h"

#include <imgui.h>
#include <imgui_internal.h>


class Application
{
public:
	Application(int width, int height, const std::string& title);
	~Application();

	void Run();

public:
	void OnUpdate();
	void OnKey(int key, int scancode, int action, int mods);
	void OnMouseButton(int button, int action, int mods);
	void OnCursorPos(double xpos, double ypos);
	void OnWindowResize(int width, int height);
	void OnFramebufferResize(int width, int height);
	void OnWindowClose();

protected:
	void RegisterCallbacks();

	Window* m_Window;

	unsigned int m_ImageTexture = 0;
};