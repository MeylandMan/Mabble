#pragma once

#include "Window.h"
#include "events/ApplicationEvent.h"

#include <imgui.h>
#include <imgui_internal.h>


class Application
{
public:

	Application(int width, int height, const std::string& title);
	~Application() = default;

	void Run();

	void OnEvent(Event& e);
	void Close();
	Window& GetWindow() { return *m_Window; }
	static Application& Get() { return *s_Instance; }
	void SubmitToMainThread(const std::function<void()>& function);
public:
	bool m_Instance = true;

private:
	bool OnWindowClose(WindowCloseEvent& e);
	bool OnWindowResize(WindowResizeEvent& e);

	void ExecuteMainThreadQueue();
private:
	std::unique_ptr<Window> m_Window;

	bool m_Running = true;
	bool m_Minimized = false;
	float m_LastFrameTime = 0.0f;

	std::vector<std::function<void()>> m_MainThreadQueue;
	std::mutex m_MainThreadQueueMutex;
private:
	static Application* s_Instance;
};